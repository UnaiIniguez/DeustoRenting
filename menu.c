#include "menu.h"

void showMenu(User* user){
	printLine();
	printf("\n");
	printfln("MENU PRINCIPAL");
	printLine();
	printfln("0. Cambiar Idioma\n"
			"1. Alquilar vehículo\n"
			"2. Devolver vehículo\n"
			"3. Ver contrato de alquiler\n"
			"4. Contratar servicio\n"
			"5. Administrar vehículos y servicios (Admin)\n"
			"6. Salir");

	unsigned short option = getAction();
	if(option == 0){

	}else if(option == 1){
		bookVehicle(user);
	}else if(option == 2){

	}else if(option == 3){

	}else if(option == 4){

	}else{

	}

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
		sscanf(input, "%hu", &option);
	}
	free(input); input=NULL;
	return option;
}
