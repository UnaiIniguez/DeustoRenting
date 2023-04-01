/*
 * ficheros.c
 *
 *  Created on: 1 abr 2023
 *      Author: banit
 */

#include "ficheros.h"

void leerFicheroTXT(char *archivo) {

	FILE* f = fopen(archivo, "r");

	char c;

	int num_lines = 0;

	while ((c = fgetc(f)) != EOF) {
		if (c == '\n'){
			num_lines++;
		}

		putchar(c);
	}

	fclose(f);

}

void escribirFicheroTXT( char *archivo ){

	//Cuando se añada la parte de la reserva añadir un array de reservas
	// a la entreda para poder extraer su informacion


}

void escribirNormas( char *archivo ){

	FILE* f = fopen(archivo, "w");

	char* test = "Paco";

//	printf( "Funciona" );

	fprintf( f, "CONTRATO DE ACEPTACION DE LA NORMATIVA DE LA EMPRESA\n" );

	fprintf( f, "----------------------------------------------------\n" );

	fprintf( f, "(El texto con todas las normas)\n" );

	fprintf( f, "Yo %s acepto la normativa", test );

	fclose(f);

}

