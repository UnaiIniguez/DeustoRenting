#include "menu.h"

void showMenu(User* user){
	printLine();
	printfln("MENU PRINCIPAL");
	printLine();
	printfln("0. Alquilar vehículo\n"
			 "1. Devolver vehículo\n"
			 "2. Ver contrato de alquiler\n"
			 "3. Contratar servicio para mi contrato\n"
			 "4. Administrar vehículos y servicios (Admin)\n"
			 "5. Salir");

	unsigned short option = getAction();
	if(option == 0){
		bookVehicle(user);
	}else if(option == 1){
		returnContract(user);
	}else if(option == 2){
		showContract(user);
	}else if(option == 3){
		bookService(user);
	}else if(option == 4){
		isAdmin(user->dni);
	}else{
		exit(0);
	}
	showMenu(user);

}

unsigned short getAction(){
	unsigned short option = 7;
	char* input = calloc(3, sizeof(char));
	readLine(&input);
	sscanf(input, "%hu", &option);
	while(option > 6){
		free(input); input=NULL;
		input = calloc(3, sizeof(char));
		printfln("La opción '%d' no existe. Seleccione una opción válida", option);
		readLine(&input);
	}
	free(input); input=NULL;
	return option;
}
