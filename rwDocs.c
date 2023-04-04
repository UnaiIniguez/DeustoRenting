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

