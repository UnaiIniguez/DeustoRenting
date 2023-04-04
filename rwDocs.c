#include "rwDocs.h"

void readFileTXT(char *archivo) {

	FILE *f = fopen(archivo, "r");

	char c;

	int num_lines = 0;

	while ((c = fgetc(f)) != EOF) {

		if (c == '\n') {
			num_lines++;
		}

		putchar(c);
	}

	fclose(f);

}

void writeFileTXT( Contract contract ,char *file) {

	//Cuando se añada la parte de la reserva añadir un array de reservas
	// a la entreda para poder extraer su informacion

	FILE *f = fopen(file, "w");

	fprintf(f, "Datos de su reserva\n");
	fprintf(f, "-------------------\n");

	fprintf(f, "DNI: %s\n", contract.dni_user);
	fprintf(f, "Numero de reserva: %s\n", contract.registration_number);
	fprintf(f, "Fecha de recojida: %s\n", contract.date_start);
	fprintf(f, "Fecha de entrega: %s\n", contract.date_end);

	logger("Factura guardada");

	fclose(f);

}

void writeRules(char *file) {

	FILE *f = fopen(file, "w");

	char *test = "Paco";

//	printf( "Funciona" );

	fprintf(f, "CONTRATO DE ACEPTACION DE LA NORMATIVA DE LA EMPRESA\n");

	fprintf(f, "----------------------------------------------------\n");

	fprintf(f, "(El texto con todas las normas)\n");

	fprintf(f, "Yo %s acepto la normativa", test);

	fclose(f);

}

void logger(char *msg){


	FILE *f = fopen("log.txt", "w");


	fprintf(f, msg);



}

