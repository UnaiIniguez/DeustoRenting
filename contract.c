#include "contract.h"

#define DIRCONTRACT "contract.txt"

void initContract(Vehicle vehicle, char* dni){
	showVehicle(vehicle);
	showOptions();
	if(getServiceOption() == 0){
		Service service = showServices();
		printfln("Servicio añadido con éxito");
		generateContract(dni, vehicle.registration_number, service.cod_Service);
	}else{
		generateContract(dni, vehicle.registration_number, -1);
	}
}

void bookVehicle(User* user){
	Vehicle* vehicles = NULL;
	int option = getVehicleIndex(&vehicles);
	if(option < 0){
		fprintf(stderr, "No se consta de vehículos disponibles\n");
		return;
	}
	initContract(vehicles[option], user->dni);
}

int randomInt(int min, int max) {
	srand(time(NULL));
	return rand() % (max - min + 1) + min;
}

char* getDateStart() {
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	t->tm_mday += 1; // increment by 1 to avoid the same day
	t->tm_hour = 0;
	t->tm_min = 0;
	t->tm_sec = 0;
	mktime(t);
	char* date_start = malloc(sizeof(char) * 11);
	sprintf(date_start, "%02d/%02d/%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
	return date_start;
}

char* getDateEnd() {
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	t->tm_mday += 1; // increment by 1 to avoid the same day
	t->tm_hour = 0;
	t->tm_min = 0;
	t->tm_sec = 0;
	t->tm_mon += 1; // add one month
	mktime(t);
	char* date_end = malloc(sizeof(char) * 11);
	sprintf(date_end, "%02d/%02d/%04d", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
	return date_end;
}


void generateContract(char* dni, char* registration_number, int cod_service) {
	Contract contract;

	contract.registration_number = registration_number;
	contract.cancellation_hours = -1;
	contract.dni_user = dni;
	contract.cod_service = cod_service;

	contract.tank = randomInt(0, 1);
	contract.date_start = getDateStart();
	contract.date_end = getDateEnd();
	contract.cancellation_hours = randomInt(1, 3) * 24;

	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
	}

	Contract* actualContract = getContract(db, dni);
	if(actualContract != NULL){
		deleteContract(db, *actualContract);
	}
	if(!insertContract(db, contract)){
		fprintf(stderr,"\nError guardando el contrato");
		exit(1);
	}
	writeContractTXT(contract , DIRCONTRACT);
	printfln("Se ha generado tu contrato en la dirección %s", DIRCONTRACT);

	sqlite3_close(db);
}


void showOptions(void){
	printfln("0. Añadir Servicio\n"
			"1.Alquilar Vehículo");
}

unsigned short getServiceOption(void){
	char* input = calloc(13, sizeof(char));
	readLine(&input);
	unsigned short option = 2;
	sscanf(input, "%hu", &option);
	while(option > 1){
		printfln("'%hu' no es una opción válida. Escoge entre 0 y 1");
		free(input); input=NULL;
		input = calloc(13, sizeof(char));
		readLine(&input);
	}
	free(input); input=NULL;
	return option;
}

int insertContract(sqlite3 *db, Contract con) {

	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Contratos(Matricula, Fecha_Inicio, Fecha_Fin, Descripcion, Entrega_Deposito, Horas_Cancelacion, Dni_Usuario, Cod_Servicio) values (?,?,?,?,?,?,?,?)  ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

	result = sqlite3_bind_text(stmt, 1, con.registration_number,
			strlen(con.registration_number),
			SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, con.date_start, strlen(con.date_start),
			SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 3, con.date_end, strlen(con.date_end),
			SQLITE_STATIC);
	result = sqlite3_bind_int(stmt, 5, con.tank);
	result = sqlite3_bind_int(stmt, 6, con.cancellation_hours);

	result = sqlite3_bind_text(stmt, 7, con.dni_user, strlen(con.dni_user),
			SQLITE_STATIC);

	result = sqlite3_bind_int(stmt, 8, con.cod_service);


	if (result != SQLITE_OK) {
		printf("Error with parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insert parameters\n");
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}

	printf("Prepared statement finalized (INSERT)\n");
	return result = 1;

}

int deleteContract(sqlite3 *db, Contract con) {

	sqlite3_stmt *stmt;
	char consulta[] =
			"delete from Contratos where Matricula = (?) and Fecha_Inicio = (?) ;";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_text(stmt, 1, con.registration_number,
			strlen(con.registration_number),
			SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 2, con.date_start, strlen(con.date_start),
			SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error removing parameters \n");
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}

	printf("Prepared statement finalized (DELETE)\n");
	return result = 1;

}

void returnContract(User* user){
	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
	}
	Contract* contract = getContract(db, user->dni);
	if(contract == NULL){
		printfln("Usted no dispone de ningún vehículo para devolver");
	}else{
		printfln("¿Está seguro de que quiere renunciar al siguiente contrato?");
		printContract(*contract);
		deleteContract(db, *contract);
	}
	free(contract);
	sqlite3_close(db);
}

void showContract(User* user){
	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
		exit(1);
	}
	Contract* contract = getContract(db, user->dni);
	sqlite3_close(db);
	if(contract == NULL){
		printfln("Usted no cuenta con ningún contrato con nuestra compañía");
	}else{
		printContract(*contract);
	}
	free(contract);
}

Contract* getContract(sqlite3 *db, char* dni){

	sqlite3_stmt *stmt;
	char consulta[] =
			"select co.Matricula, co.Fecha_Inicio, co.Fecha_Fin, co.Descripcion, co.Entrega_Deposito, co.Horas_Cancelacion, co.Dni_Usuario , co.Cod_Servicio FROM Usuarios u, Contratos co WHERE (?) = co.Dni_Usuario ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_text(stmt, 1, dni,strlen(dni),
			SQLITE_STATIC);

	if (result != SQLITE_OK) {
		fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
		return NULL;
	}

	int num_rows = 0;
	Contract *con1;
	con1 = NULL;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		num_rows++;

		Contract *tmp = realloc(con1, num_rows * sizeof(Contract));
		if (!tmp) {
			fprintf(stderr, "Error allocating memory\n");
			free(con1);
			return NULL;
		}
		con1 = tmp;

		const char *regist = (const char*) sqlite3_column_text(stmt, 0);
		memcpy(con1[num_rows - 1].registration_number, regist, 9);


		con1[num_rows - 1].date_start = strdup(
				(char*) sqlite3_column_text(stmt, 1));
		con1[num_rows - 1].date_end= strdup(
				(char*) sqlite3_column_text(stmt, 2));
		con1[num_rows - 1].tank = sqlite3_column_int(stmt, 4);

		con1[num_rows - 1].cancellation_hours = sqlite3_column_int(stmt, 5);



		const char *dni = (const char*) sqlite3_column_text(stmt, 6);
		memcpy(con1[num_rows - 1].registration_number, dni, 10);

		con1[num_rows - 1].cod_service = sqlite3_column_int(stmt, 7);

	}

	sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error ending prepared statement: %s\n",
				sqlite3_errmsg(db));
	}
	return con1;

}

void printContract(Contract contract){
	printf("Datos de su contrato:\n");
	printf("\tMatrícula: %s\n", contract.registration_number);
	printf("\tFecha inicio: %s\n", contract.date_start);
	printf("\tFecha fin: %s\n", contract.date_end);
	printf("\tEntrega del vehículo con el tanque lleno: %d\n", contract.tank);
	printf("\tHoras de cancelación: %d\n", contract.cancellation_hours);
	printf("\tDNI del usuario: %s\n", contract.dni_user);
	printf("\tCódigo del servicio contratado: %d\n", contract.cod_service);
}

void writeContractTXT(Contract contract ,char *file) {

	//Cuando se añada la parte de la reserva añadir un array de reservas
	// a la entreda para poder extraer su informacion

	FILE *f = fopen(file, "w");

	fprintf(f, "\tDatos de su contrato\n");
	fprintf(f, "\t-------------------\n");

	fprintf(f, "\tDNI: %s\n", contract.dni_user);
	fprintf(f, "\tMatricula: %s\n", contract.registration_number);
	fprintf(f, "\tFecha de recojida: %s\n", contract.date_start);
	fprintf(f, "\tFecha de entrega: %s\n", contract.date_end);
	fprintf(f, "\tEntrega del vehículo con el tanque lleno: %d\n", contract.tank);
	fprintf(f, "\tHoras de cancelación: %d\n", contract.cancellation_hours);
	if (contract.cod_service == -1) {
		fprintf(f, "\tEl contrato no consta de ningún servicio\n");
	}else{
		fprintf(f, "\tCódigo del servicio contratado: %d\n", contract.cod_service);
	}

	//	logger("Factura guardada");

	fclose(f);

}
