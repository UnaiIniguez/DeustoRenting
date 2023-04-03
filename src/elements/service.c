#include "service.h"



unsigned short optionSelected(Service *services, int num_services) {

	unsigned short option = 2;

	if (services != NULL) {

		int i;

		for (i = 0; i < num_services; i++) {
			printf("\n\t%i. %s", i, services[i].description);
			printf("(Precio: %.2f)", services[i].price);
		}
		printf("\n\t%d. Volver", i);
		free(services);
		char *input = calloc(5, sizeof(char));
		readLine(&input);
		sscanf(input, "%hu", &option);
		while (option > num_services + 1) {
			free(input);
			char *input = calloc(5, sizeof(char));
			printfln("La opción '%d' no existe. Seleccione una opción válida",option);
			readLine(&input);
			sscanf(input, "%hu", &option);
		}
		return option;
	} else {
		return 0;
	}
}

void printServicios(User user, sqlite3 *db) {

	printf("\n");
	printfln("SERVICIOS ADICIONALES:");
	printLine();
	int num_services = 0;

	Service *services = getServices(db, &num_services);

	int p = optionSelected(services, num_services);	//Te devuelve la opcion que quiere almacenar

	int j = insertServiceInContract(db, user, services[p]);

	if(j = 1){
		printf("Se ha introducido adecuadamente");
	}
	else{
		printf("Ha habido un error");
	}


}




