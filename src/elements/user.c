#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "../std/stdout.h"
#include "../std/stdin.h"
#include "string.h"
#include "../dataBase/BD.h"

void getUser(User* user){
	if(getOption()){
		printf("\n");
		printfln("REGISTRARSE");
		printLine();
		getDNI(user);
		getName(user);
		getSurname1(user);
		getSurname2(user);
		getEmail(user);
		getPassword(user, "deseada");
	}else{
		printf("\n");
		printfln("INICIAR SESIÓN");
		printLine();
		getDNI(user);
		checkDNI(user);
		getPassword(user, "");
		checkPassword(user);
	}
}

void checkDNI(User* user){
	while(hasDNI(user->dni)){
		printf("El DNI introducido ya está registrado\n");
		getDNI(user);
	}
}

void checkPassword(User* user){
	while(hasDNI(user->password)){
		printf("El DNI introducido ya está registrado\n");
		getPassword(user, "");
	}
}

void getName(User* user){
	printfln("Introduzca su nombre");
	char* input = calloc(10, sizeof(char));
	readLine(&input);
	user->name = calloc(strlen(input), sizeof(char));
	input[strlen(input) - 1] = '\0';
	strcpy(user->name, input);
	free(input); input=NULL;
}

void getSurname1(User* user){
	printfln("Introduzca su primer apellido");
	char* input = calloc(10, sizeof(char));
	readLine(&input);
	user->surname1 = calloc(strlen(input), sizeof(char));
	input[strlen(input) - 1] = '\0';
	strcpy(user->surname1, input);
	free(input); input=NULL;
}

void getSurname2(User* user){
	printfln("Introduzca su segundo apellido");
	char* input = calloc(10, sizeof(char));
	readLine(&input);
	user->surname2 = calloc(strlen(input), sizeof(char));
	input[strlen(input) - 1] = '\0';
	strcpy(user->surname2, input);
	free(input); input=NULL;
}

void getEmail(User* user){
	printfln("Introduzca su dirección de email");
	char* input = calloc(13, sizeof(char));
	readLine(&input);
	while(strcmp(&input[strlen(input) - 11], "@gmail.com\n")){
		printfln("Introduce una dirección que acabe en '@gmail.com'");
		free(input); input=NULL;
		input = calloc(13, sizeof(char));
		readLine(&input);
	}
	user->email = calloc(strlen(input), sizeof(char));
	input[strlen(input) - 1] = '\0';
	strcpy(user->email, input);
	free(input); input=NULL;
}

void getPassword(User* user, char* string){
	printfln("Introduzca su contraseña %s", string);
	char* input = calloc(10, sizeof(char));
	readLine(&input);
	user->password = calloc(strlen(input), sizeof(char));
	input[strlen(input) - 1] = '\0';
	strcpy(user->password, input);
	free(input); input=NULL;
}

void getDNI(User* user){
    printfln("Introduzca su DNI");
    char* input = calloc(10, sizeof(char));
    readLine(&input);
    while(strlen(input) != 10){
        printfln("El DNI debe tener 9 carácteres. Usted ha introducido %lu", strlen(input) - 1);
        free(input); input=NULL;
        input = calloc(10, sizeof(char));
        readLine(&input);
    }
    input[strlen(input) - 1] = '\0';
    user->dni = calloc(strlen(input), sizeof(char));
    strcpy(user->dni, input);
    free(input); input = NULL;
}


unsigned short getOption(void){
	unsigned short option = 2;
	printfln("¿Qué desea hacer?\n\t0. Inciar Sesión\n\t1. Registrarme");
	char* input = calloc(3, sizeof(char));
	readLine(&input);
	sscanf(input, "%hu", &option);
	while(option > 1){
		free(input); input=NULL;
		input = calloc(5, sizeof(char));
		printfln("La opción '%d' no existe. Seleccione una opción válida", option);
		readLine(&input);
		sscanf(input, "%hu", &option);
	}
	free(input); input=NULL;
	return option;
}
