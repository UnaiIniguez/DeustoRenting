#include "administrador.h"



void isAdmin(sqlite3 *db,char * dni){

	int p = typeUser(db, dni);

	if(p == 1){

		showMenuAdmin(db);

	}else{
		printf( "No eres administrador");
	}

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
		insertNewVehicle(db);//*******************************************
	} else if (option == 1) {
		eliminateVehicle(db);
	} else if (option == 2) {
		viewVehicles(db);//***********************************************

	} else if (option == 3) {
		insertNewService(db);
	} else if (option == 4) {
		eliminateService(db);
	} else {
		//*******************************DEBE VOLVER AL MENÚ**************
	}

}

unsigned short getSelection(){
	unsigned short option = 5;
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




//************************************************************************
void eliminateVehicle(sqlite3 *db){

	printLine();
	printf("\n");
	printfln("ELIMINAR VEHICULO");
	printLine();
	printfln("Matricula del vehiculo que se desea eliminar:");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	input[strlen(input) - 1] = '\0';
	char registration[9];
	strcpy(registration, input);
	free(input);
	input = NULL;
	if(deleteVehicle(db, registration) == 1){
		printf("El vehiculo se ha eliminado adecuadamente");
	}else{
		printf("Ese vehiculo no existe");
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
	Vehicle * vehicle = vehicleReserved(db, &num_Vehicles);
	optionSelect(vehicle, num_Vehicles, db);






}


void insertNewVehicle(sqlite3 *db){

	printLine();
	printf("\n");
	printfln("INSERTAR VEHICULO");
	printLine();
	Vehicle * vehicle ;
	getMarca(vehicle);
	getModelo(vehicle);
	getColor(vehicle);
	getPlazas(vehicle);
	getMatricula(vehicle);
	getPrecioVehiculo(vehicle);
	getPuertas(vehicle);
	if(insertVehicle(db, *vehicle) == 1){
		printf("\nSe ha insertado correctamente\n");
	}else{
		printf("\nNo se ha insertado correctamente\n");
	}
}

void getMarca(Vehicle *vehicle){

	printfln("Marca del vehiculo:");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	input[strlen(input) - 1] = '\0';

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
	input[strlen(input) - 1] = '\0';
	strcpy(vehicle->model, input);
	free(input);
	input = NULL;

}

void getColor(Vehicle *vehicle){
	printfln("Color del vehiculo:");
	char *input = calloc(10, sizeof(char));
	readLine(&input);
	vehicle->color = calloc(strlen(input), sizeof(char));
	input[strlen(input) - 1] = '\0';
	strcpy(vehicle->color, input);
	free(input);
	input = NULL;

}

void getPlazas(Vehicle *vehicle){
	printf("Numero de plazas: ");
	int num_Plazas = 0;
	scanf("%d", &num_Plazas);
	vehicle->num_seats = num_Plazas;

}

void getMatricula(Vehicle *vehicle){

	printfln("Matricula del vehiculo:");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	input[strlen(input) - 1] = '\0';
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

void getPuertas(Vehicle *vehicle){
	printf("Numero de plazas: ");
	int num_Plazas = 0;
	scanf("%d", &num_Plazas);
	vehicle->num_seats = num_Plazas;

}

//************************************************************************
void insertNewService(sqlite3 *db){

	printLine();
	printf("\n");
	printfln("INSERTAR SERVICIO ADICIONAL");
	printLine();
	Service *service;
	getDescripcion(service);
	getPrecioServicio(service);
	if(insertService(db, *service) == 1){
		printf("\nSe ha insertado correctamente\n");
	}else{
		printf("\nNo se ha insertado correctamente\n");
	}




}

void getDescripcion(Service *service){

	printfln("Descripcion del servicio:");
	char *input = calloc(9, sizeof(char));
	readLine(&input);
	input[strlen(input) - 1] = '\0';
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








