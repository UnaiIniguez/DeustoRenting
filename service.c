#include "service.h"

Service showServices(void){
	unsigned short numServices = 0;
	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
		exit(1);
	}
	Service* services = getServices(db, &numServices);
	sqlite3_close(db);
	printfln("");
	printLine();
	printfln("LISTA DE SERVICIOS A ELEGIR:");
	printLine();
	for(int i = 0; i < numServices; i++){
		printf("%d. %s: %.2f€\n", i, services[i].description, services[i].price);
	}
	Service service = services[getSelectedServiceIndex(numServices)];
	free(services);
	return service;
}

void bookService(User* user){
	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
		exit(1);
	}

	Contract* contract = getContract(db, user->dni);
	if(contract == NULL){
		printfln("Usted no consta de ningún contrato con nuestra compañía.");
	}else{
		if(contract->cod_service == -1){
			Vehicle* vehicle = getUsersVehicle(db, user->dni);
			Service service = showServices();
			printfln("Servicio añadido con éxito");
			generateContract(user->dni, vehicle->registration_number, service.cod_Service);
			freeVehicle(vehicle);
		}else{
			printfln("Su contrato ya consta de un servicio. El número máximo de servicios por contrato es 1");
		}
	}
	sqlite3_close(db);
	freeContract(contract);
}


unsigned short getSelectedServiceIndex(unsigned short optionMax){
	char* input = calloc(13, sizeof(char));
	readLine(&input);
	unsigned short option = optionMax;
	sscanf(input, "%hu", &option);
	while(option > optionMax - 1){
		printfln("Introduce una opción entre 0 y %hu", optionMax - 1);
		free(input); input=NULL;
		input = calloc(13, sizeof(char));
		readLine(&input);
	}
	free(input); input=NULL;
	return option;
}

int insertService(sqlite3 *db, Service sr) {
	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Servicios_Adicionales(Cod_Servicio, Descripcion, Precio) values (NULL,?,?)  ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);


	result = sqlite3_bind_text(stmt, 1, sr.description, strlen(sr.description),
	SQLITE_STATIC);
	result = sqlite3_bind_double(stmt, 2, sr.price);

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
	return result = 1;

}

int deleteService(sqlite3 *db, int cod) {
	sqlite3_stmt *stmt;
	char consulta[] =
			"delete from Servicios_Adicionales where Cod_Servicio = (?) ;";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_int(stmt, 1, cod);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insert parameters\n");
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}


	return result = 1;

}

Service* getServices(sqlite3* db, unsigned short* num_services){
	sqlite3_stmt *stmt;
	char consulta[] =
			"select * FROM Servicios_Adicionales ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

	if (result != SQLITE_OK) {
		fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
		return NULL;
	}

	unsigned short num_rows = 0;
	Service *servicios = NULL;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		num_rows++;

		Service *tmp = realloc(servicios, num_rows * sizeof(Service));
		if (!tmp) {
			fprintf(stderr, "Error allocating memory\n");
			free(servicios);
			return NULL;
		}
		servicios = tmp;

		servicios[num_rows - 1].cod_Service = sqlite3_column_int(stmt, 0);
		servicios[num_rows - 1].description = strdup(
				(char*) sqlite3_column_text(stmt, 1));
		servicios[num_rows - 1].price = sqlite3_column_double(stmt, 2);

	}


	sqlite3_finalize(stmt);
	*num_services = num_rows;
	return servicios;
}

int insertServiceInContract(sqlite3 *db, User u, Service *service) {

	sqlite3_stmt *stmt;
	char consulta[] =
			" UPDATE Contratos SET Cod_Servicio = (?) where Dni_Usuario = (?) ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

	result = sqlite3_bind_int(stmt, 1, service->cod_Service);


	result = sqlite3_bind_text(stmt, 2, u.dni, strlen(u.dni),
	SQLITE_STATIC);


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


	return result = 1;

}
