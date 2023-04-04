#include "vehicle.h"

int showVechiles(Vehicle** vehicles){
	printfln("ELIGE UN VEHÍCULO");
	printLine();
	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
	}
	int count = 0;
	*vehicles = availableVehicles(db, &count);
	sqlite3_close(db);
	for(int i = 0; i < count; i++) {
		printfln("\t%d. %s %s: %.2f€ ", i, (*vehicles)[i].brand, (*vehicles)[i].model, (*vehicles)[i].price);
	}
	return count;
}

void showVehicle(Vehicle vehicle){
	printf("\n");
	printLine();
	printfln("CONTRATO DE ALQUILER");
	printLine();
	printfln("DATOS DEL VEHÍCULO SELECCIONADO:\n"
			"\tMatrícula: %s\n"
			"\tMarca: %s\n"
			"\tModelo: %s\n"
			"\tColor: %d\n"
			"\tNº de Plazas; %d\n"
			"\tNº de Puertas: %d\n"
			"\tPrecio: %.2f",
			vehicle.registration_number, vehicle.brand, vehicle.model, vehicle.color, vehicle.num_seats, vehicle.num_doors, vehicle.price);
}

int getVehicleIndex(Vehicle** vehicles){
	int count = showVechiles(vehicles);
	if(count < 0) return - 1;
	int optionMAX = count - 1;
	char* input = calloc(3, sizeof(char));
	readLine(&input);
	sscanf(input, "%d", &count);
	while(count > optionMAX){
		free(input); input=NULL;
		input = calloc(3, sizeof(char));
		printfln("La opción '%d' no existe. Seleccione una opción válida", count);
		readLine(&input);
		sscanf(input, "%d", &count);
	}
	free(input); input=NULL;
	return count;
}


int insertVehicle(sqlite3 *db, Vehicle ve) {

	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Vehiculos(Color, Modelo, Marca, Num_Plazas, Matricula, Precio, Num_Puerta) values (?,?,?,?,?,?,?)  ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

	result = sqlite3_bind_text(stmt, 1, ve.color, strlen(ve.color),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, ve.model, strlen(ve.model),
	SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 3, ve.brand, strlen(ve.brand),
	SQLITE_STATIC);
	result = sqlite3_bind_int(stmt, 4, ve.num_seats);

	result = sqlite3_bind_text(stmt, 5, ve.registration_number,
			strlen(ve.registration_number),
			SQLITE_STATIC);
	result = sqlite3_bind_double(stmt, 6, ve.price);
	result = sqlite3_bind_int(stmt, 7, ve.num_doors);

	if (result != SQLITE_OK) {
		printf("Error with parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insert parameters\n");
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}

	printf("Prepared statement finalized (INSERT)\n");
	return result = 1;
}

int deleteVehicle(sqlite3 *db, char matricula[]) {

	sqlite3_stmt *stmt;
	char consulta[] = "delete from Vehiculos where Matricula = (?) ;";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula),
	SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error removing parameters\n");
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}


	return result = 1;
}

Vehicle* availableVehicles(sqlite3 *db, int* num_Vehicles) {//*********************************************************************************************

	sqlite3_stmt *stmt;
	char consulta[] =
			"select ve.modelo, ve.marca, ve.color, ve.Num_Plazas, ve.Matricula, ve.precio, ve.Num_Puerta FROM Vehiculos ve WHERE ve.Matricula NOT IN (SELECT Matricula FROM Contratos);";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);


	if (result != SQLITE_OK) {
		fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
		return NULL;
	}

	int num_rows = 0;
	Vehicle *vehicles = NULL;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		num_rows++;

		Vehicle *tmp = realloc(vehicles, num_rows * sizeof(Vehicle));
		if (!tmp) {
			fprintf(stderr, "Error allocating memory\n");
			free(vehicles);
			return NULL;
		}
		vehicles = tmp;

		vehicles[num_rows - 1].model = strdup(
				(char*) sqlite3_column_text(stmt, 0));
		vehicles[num_rows - 1].brand = strdup(
				(char*) sqlite3_column_text(stmt, 1));
		vehicles[num_rows - 1].color = strdup(
				(char*) sqlite3_column_text(stmt, 2));
		vehicles[num_rows - 1].num_seats = sqlite3_column_int(stmt, 6);


		const char *regist = (const char*) sqlite3_column_text(stmt, 4);
		memcpy(vehicles[num_rows - 1].registration_number, regist, 9);


		vehicles[num_rows - 1].price = sqlite3_column_double(stmt, 5);

		vehicles[num_rows - 1].num_doors = sqlite3_column_int(stmt, 6);
	}

	*num_Vehicles = num_rows;

	sqlite3_finalize(stmt);
	return vehicles;
}

Vehicle *vehicleReserved(sqlite3 *db, int *num_Vehicles){

	 sqlite3_stmt *stmt;
	    char consulta[] =
	        "select ve.Color, ve.Modelo, ve.Marca, ve.Num_Plazas, ve.Matricula, ve.Precio, ve.Num_Puerta FROM Vehiculos ve, Contratos co WHERE ve.Matricula = co.Matricula ";

	    int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	    if (result != SQLITE_OK) {
	        fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
	        return NULL;
	    }


	    if (result != SQLITE_OK) {
	        fprintf(stderr, "Error binding parameter: %s\n", sqlite3_errmsg(db));
	        sqlite3_finalize(stmt);
	        return NULL;
	    }

	    int num_rows = 0;
	    Vehicle *vehicles = NULL;

	    while (sqlite3_step(stmt) == SQLITE_ROW) {
	        num_rows++;

	        Vehicle *tmp = realloc(vehicles, num_rows * sizeof(Vehicle));
	        if (!tmp) {
	            fprintf(stderr, "Error allocating memory\n");
	            free(vehicles);
	            sqlite3_finalize(stmt);
	            return NULL;
	        }
	        vehicles = tmp;

	        vehicles[num_rows - 1].color = strdup((char *)sqlite3_column_text(stmt, 0));
	        vehicles[num_rows - 1].model = strdup((char *)sqlite3_column_text(stmt, 1));
	        vehicles[num_rows - 1].brand = strdup((char *)sqlite3_column_text(stmt, 2));
	        vehicles[num_rows - 1].num_seats = sqlite3_column_int(stmt, 3);

	        const char *regist = (const char *)sqlite3_column_text(stmt, 4);
	        memcpy(vehicles[num_rows - 1].registration_number, regist, 9);

	        vehicles[num_rows - 1].price = sqlite3_column_double(stmt, 5);
	        vehicles[num_rows - 1].num_doors = sqlite3_column_int(stmt, 6);
	    }

	    *num_Vehicles= num_rows;
	    sqlite3_finalize(stmt);

	    return vehicles;

}

Vehicle *usersVehicle(sqlite3 *db, char *dni) {
    sqlite3_stmt *stmt;
    char consulta[] =
        "select ve.Color, ve.Modelo, ve.Marca, ve.Num_Plazas, ve.Matricula, ve.Precio, ve.Num_Puerta FROM Vehiculos ve, Usuarios us, Contratos co WHERE ve.Matricula = co.Matricula AND co.Dni_Usuario = us.DNI AND us.DNI = ?;";

    int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    result = sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Error binding parameter: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }

    int num_rows = 0;
    Vehicle *vehicles = NULL;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        num_rows++;

        Vehicle *tmp = realloc(vehicles, num_rows * sizeof(Vehicle));
        if (!tmp) {
            fprintf(stderr, "Error allocating memory\n");
            free(vehicles);
            sqlite3_finalize(stmt);
            return NULL;
        }
        vehicles = tmp;

        vehicles[num_rows - 1].color = strdup((char *)sqlite3_column_text(stmt, 0));
        vehicles[num_rows - 1].model = strdup((char *)sqlite3_column_text(stmt, 1));
        vehicles[num_rows - 1].brand = strdup((char *)sqlite3_column_text(stmt, 2));
        vehicles[num_rows - 1].num_seats = sqlite3_column_int(stmt, 3);

        const char *regist = (const char *)sqlite3_column_text(stmt, 4);
        memcpy(vehicles[num_rows - 1].registration_number, regist, 9);

        vehicles[num_rows - 1].price = sqlite3_column_double(stmt, 5);
        vehicles[num_rows - 1].num_doors = sqlite3_column_int(stmt, 6);
    }

    sqlite3_finalize(stmt);
    printf("Prepared statement finalized (SELECT)\n");
    return vehicles;
}
