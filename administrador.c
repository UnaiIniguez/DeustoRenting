#include "administrador.h"



void isAdmin(char * dni){
	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
		exit(1);
	}
	if(typeUser(db, dni)){
		showMenuAdmin(db);
	}else{
		printfln("No eres administrador");
	}
	sqlite3_close(db);
}

void showMenuAdmin(sqlite3 *db){

	printLine();
	printf("\n");
	printfln("MENU ADMINISTRADOR");
	printLine();
	printfln("0. Insertar nuevo vehiculo\n"
			"1. Eliminar vehiculo \n"
			"2. Visualizar coches alquilados \n"
			"3. Incorporar servicio \n"
			"4. Eliminar servicio\n"
			"5. Salir");
	unsigned short option = getSelection();

	if (option == 0) {
		insertNewVehicle(db);
	}else if (option == 1) {
		eliminateVehicle(db);
	}else if (option == 2) {
		viewVehicles(db);
	}else if (option == 3) {
		insertNewService(db);
	}else if (option == 4)  {
		eliminateService(db);
	}else{
		exit(0);
	}

}

unsigned short getSelection(){
	unsigned short option = 6;
	char* input = calloc(3, sizeof(char));
	readLine(&input);
	sscanf(input, "%hu", &option);
	while(option > 5){
		free(input);
		input=NULL;
		input = calloc(3, sizeof(char));
		printfln("La opción '%d' no existe. Seleccione una opción válida", option);
		readLine(&input);
		sscanf(input, "%hu", &option);
	}
	free(input); input=NULL;
	return option;
}

void eliminateVehicle(sqlite3 *db){

	printLine();
	printf("\n");
	printfln("ELIMINAR VEHICULO");
	printLine();
	printfln("Matricula del vehiculo que se desea eliminar:");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	char registration[9];
	strcpy(registration, input);
	free(input);
	input = NULL;
	if(deleteVehicle(db, registration) == 1){
		printf("El vehiculo se ha eliminado adecuadamente");
	}else{
		printf("No existe ningún vehículo con matrícula %s", input);
	}

}

void optionSelect(Vehicle *vehicles, int num_vehicles,sqlite3 *db ) {



	if (vehicles != NULL) {

		int i;

		for (i = 0; i < num_vehicles; i++) {
			printf("\n\t%i. %s - %s - %s - %i(asientos) = %.2f", i, vehicles[i].brand, vehicles[i].model,vehicles[i].color,
					vehicles[i].num_seats, vehicles[i].price );


		}
		printf("\n\n\tPara volver pulsa b ");
		printf("\n-->");
		char input[2];
		fgets(input, sizeof(input), stdin); // Lee una línea completa incluyendo el salto de línea
		input[strcspn(input, "\n")] = '\0'; // Elimina el salto de línea

		while (toupper(input[0]) != 'B') {
			printf("\nLetra incorrecta");
			printf("\n-->");
			fgets(input, sizeof(input), stdin);
			input[strcspn(input, "\n")] = '\0';
		}
		showMenuAdmin(db);

	}
}




void viewVehicles(sqlite3 *db){//******************************************

	printLine();
	printf("\n");
	printfln("VEHICULOS ALQUILADOS");
	printLine();
	int num_Vehicles;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
	}
	optionSelect(vehicleReserved(db, &num_Vehicles), num_Vehicles, db);
	sqlite3_close(db);
}


void insertNewVehicle(sqlite3 *db){

	printLine();
	printf("\n");
	printfln("INSERTAR VEHICULO");
	printLine();
	Vehicle vehicle;
	getMarca(&vehicle);
	getModelo(&vehicle);
	getColor(&vehicle);
	getPlazas(&vehicle);
	getMatricula(&vehicle);
	getPrecioVehiculo(&vehicle);
	if(insertVehicle(db, vehicle) == 1){
		printfln("\nEl vehículo se ha insertado correctamente");
	}else{
		printfln("\nEl vehículo no se ha insertado correctamente");
	}
}

void getMarca(Vehicle *vehicle){
	printfln("Marca del vehiculo:");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	vehicle->brand = calloc(strlen(input), sizeof(char));
	strcpy(vehicle->brand, input);
	free(input);
	input = NULL;
}

void getModelo(Vehicle *vehicle){

	printfln("Modelo del vehiculo:");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	vehicle->model = calloc(strlen(input), sizeof(char));
	strcpy(vehicle->model, input);
	free(input);
	input = NULL;

}

void getColor(Vehicle *vehicle){
	printfln("Color del vehiculo:");
	char *input = calloc(10, sizeof(char));
	readLine(&input);
	vehicle->color = calloc(strlen(input), sizeof(char));
	strcpy(vehicle->color, input);
	free(input);
	input = NULL;

}

void getPlazas(Vehicle *vehicle){
	printfln("Número de plazas: ");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	sscanf(input, "%d", &vehicle->num_seats);
	free(input);
	input = NULL;
}

void getMatricula(Vehicle *vehicle){
	printfln("Matricula del vehículo");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	vehicle->registration_number = calloc(strlen(input) + 1, sizeof(char));
	strcpy(vehicle->registration_number, input);
	free(input);
	input = NULL;
}

void getPrecioVehiculo(Vehicle *vehicle){
	printf("Precio por día: ");
	float precio = 0;
	scanf("%f", &precio);
	vehicle->price = precio;
}

void insertNewService(sqlite3 *db){

	printLine();
	printf("\n");
	printfln("INSERTAR SERVICIO ADICIONAL");
	printLine();
	Service service;
	getDescripcion(&service);
	getPrecioServicio(&service);
	if(insertService(db, service) == 1){
		printfln("\nSe ha insertado correctamente");
	}else{
		printfln("\nNo se ha insertado correctamente");
	}

}

void getDescripcion(Service *service){
	printfln("Descripcion del servicio:");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	service->description = calloc(strlen(input),sizeof(char) );
	strcpy(service->description, input);
	free(input);
	input = NULL;
}

void getPrecioServicio(Service *service){

	printf("Precio por servicio: ");
	float precio = 0;
	printf("\n-->");
	scanf("%f", &precio);
	service->price = precio;

}

void eliminateService(sqlite3 *db){

	printLine();
	printf("\n");
	printfln("ELIMINAR SERVICIO");
	printLine();
	printf("Codigo del servicio que se desea eliminar: ");
	printf("\n-->");
	int cod = 0;
	scanf("%i", &cod);

	if (deleteService(db, cod) == 1) {
		printf("\nEl servicio se ha eliminado adecuadamente");
	} else {
		printf("El servicio no existe");
	}
}
