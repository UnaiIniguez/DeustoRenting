#include "BD.h"

int insertService(sqlite3 *db, Service sr) {
	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Servicios_Adicionales(Cod_Servicio, Tipo, Descripcion, Precio) values (NULL,?,?,?)  ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

	result = sqlite3_bind_int(stmt, sr.type, 1);
	result = sqlite3_bind_text(stmt, 2, sr.description, strlen(sr.description),
	SQLITE_STATIC);
	result = sqlite3_bind_double(stmt, 3, sr.price);

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

int deleteService(sqlite3 *db, int cod) {
	sqlite3_stmt *stmt;
	char consulta[] =
			"delete from Servicios_Adicionales where Cod_Servicio = (?) ;";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_int(stmt, cod, 1);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insert parameters\n");
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}

	printf("Prepared statement finalized (DELETE)\n");
	return result = 1;

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

	printf("Prepared statement finalized (DELETE)\n");
	return result = 1;
}

Vehicle* availableVehicles(sqlite3 *db) {

	sqlite3_stmt *stmt;
	char consulta[] =
			"select ve.modelo, ve.marca, ve.color , ve.Num_Plazas, ve.Matricula, ve.precio, ve.Num_Puertas FROM Vehiculos ve, Contratos co WHERE ve.Matricula = co.Matricula  ; ";

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

	sqlite3_finalize(stmt);
	printf("Prepared statement finalized (SELECT)\n");
	return vehicles;
}






int insertUser(sqlite3 *db, User u) {

	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Usuarios(DNI, Nombre, Apellido1, Apellido2, Correo, Tipo, Contrasenya, Idioma_Preferido) values (?,?,?,?,?,?,?, ?)  ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

	result = sqlite3_bind_text(stmt, 1, u.dni, strlen(u.dni),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, u.name, strlen(u.name),
	SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 3, u.surname1, strlen(u.surname1),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, u.surname2, strlen(u.surname2),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 5, u.email, strlen(u.email),
	SQLITE_STATIC);
	result = sqlite3_bind_int(stmt, 6, u.type);

	result = sqlite3_bind_text(stmt, 7, u.password, strlen(u.password),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 8, u.prefer_Language,
			strlen(u.prefer_Language),
			SQLITE_STATIC);

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

int modifyUser(sqlite3 *db, char *password, User u) {

	sqlite3_stmt *stmt;
	char consulta[] = "UPDATE Usuarios SET Contrasenya = (?) where DNI = (?) ;";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_text(stmt, 1, password, strlen(password),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, u.dni, strlen(u.dni),
	SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insert parameters\n");
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (MODIFY)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}

	printf("Prepared statement finalized (MODIFY)\n");
	return result = 1;

}
int userExist(sqlite3 *db, char DNI[], char *password) {
    sqlite3_stmt *stmt;
    char consulta[] = "SELECT * FROM Usuarios WHERE DNI = ? AND Contrasenya = ?;";
    int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

    result = sqlite3_bind_text(stmt, 1, DNI, strlen(DNI), SQLITE_STATIC);
    result = sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        // Si la consulta devuelve una fila, el valor existe en la base de datos
        sqlite3_finalize(stmt);
        return 1;
    } else if (result != SQLITE_DONE) {
        // Si la consulta devuelve un error
        printf("Error: %s\n", sqlite3_errmsg(db));
    }

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) {
        printf("Error ending prepared statement: %s\n",
                sqlite3_errmsg(db));
    }

    return 0;
}




int insertContract(sqlite3 *db, Contract con) {

	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Contratos(Matricula, Fecha_Inicio, Fecha_Fin, Descripcion, Entrega_Deposito, Horas_Cancelacion, Dni_Usuario) values (?,?,?,?,?,?,?)  ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

	result = sqlite3_bind_text(stmt, 1, con.registration_number,
			strlen(con.registration_number),
			SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, con.date_Start, strlen(con.date_Start),
	SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 3, con.date_end, strlen(con.date_end),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, con.description,
			strlen(con.description),
			SQLITE_STATIC);
	result = sqlite3_bind_int(stmt, 5, con.tank);
	result = sqlite3_bind_int(stmt, 6, con.cancellation_Hours);

	result = sqlite3_bind_text(stmt, 7, con.dni_User, strlen(con.dni_User),
	SQLITE_STATIC);

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

int deleteContract(sqlite3 *db, Contract con) {

	sqlite3_stmt *stmt;
	char consulta[] =
			"delete from Contratos where Matricula = (?) and Fecha_Inicio = (?) ;";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_text(stmt, 1, con.registration_number,
			strlen(con.registration_number),
			SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 2, con.date_Start, strlen(con.date_Start),
	SQLITE_STATIC);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error removing parameters \n");
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result = 0;
	}

	printf("Prepared statement finalized (DELETE)\n");
	return result = 1;

}

int hasDNI(char* DNI){
	return 0;
}

int hasPassword(char* password){
	return 0;
}
