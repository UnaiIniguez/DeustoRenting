#include "vehicle.h"

#define VEHICLES "../../docs/vehicles.txt"
#define INFO "../../docs/info_vehicles.txt"


short showVechiles(void){
	printfln("ELIGE UN VEHÍCULO");
	printLine();
	FILE *f;
	char str[100];
	short count = 0;
	f = fopen(VEHICLES, "r");
	if (f == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return - 1;
	}
	while (fgets(str, 100, f) != NULL) {
		count++;
		printf("\t%d. %s", count, str);
	}
	fclose(f);
	return count;
}

void bookVehicle(User* user){
	short index = getVehicleIndex();
	fprintf(stderr, "Indice: %d", index);
}

short getVehicleIndex(void){
	short option = showVechiles();
	const short optionMAX = option - 1;
	if(option < 0) return - 1;
	char* input = calloc(3, sizeof(char));
	readLine(&input);
	sscanf(input, "%hu", &option);
	while(option > optionMAX){
		free(input); input=NULL;
		input = calloc(3, sizeof(char));
		printfln("La opción '%d' no existe. Seleccione una opción válida", option);
		readLine(&input);
		sscanf(input, "%hu", &option);
	}
	free(input); input=NULL;
	return option;
}
