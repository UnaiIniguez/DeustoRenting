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

int readConfigTXT() {

	int lines;

	FILE *f = fopen("config.txt", "r");

	if (f == NULL) {
		printf("No se pudo abrir el archivo\n");
	}

	char line[100];
	while (fgets(line, sizeof(line), f)) {
		char *clave = strtok(line, "=");
		char *valor = strtok(NULL, "\n");

		if (strcmp(clave, "line") == 0) {
			lines = atoi(valor);
		}
	}

	fclose(f);

	return lines;

}

void writeRules(char *file, char *nombre) {

	FILE *f = fopen(file, "w");

//	printf( "Funciona" );

	fprintf(f, "CONTRATO DE ACEPTACION DE LA NORMATIVA DE LA EMPRESA\n");

	fprintf(f, "----------------------------------------------------\n");

	fprintf(f, "(El texto con todas las normas)\n");

	fprintf(f, "Yo %s acepto la normativa", nombre);

	fclose(f);

}

void logger(char *msg) {

	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	char fecha[50];
	char hora[50];

	strftime(fecha, sizeof(fecha), "%Y-%m-%d", t);
	strftime(hora, sizeof(hora), "%H:%M:%S", t);

	FILE *f = fopen("log.txt", "w");

	if (f == NULL) {
		printf("No se pudo abrir el archivo\n");
	}

	fprintf(f, "<%s:%s>;%s", fecha, hora, msg);

	fclose(f);

}

