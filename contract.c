#include "contract.h"

int insertContract(sqlite3 *db, Contract con) {

	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Contratos(Matricula, Fecha_Inicio, Fecha_Fin, Descripcion, Entrega_Deposito, Horas_Cancelacion, Dni_Usuario, Cod_Servicio) values (?,?,?,?,?,?,?, ?)  ; ";

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

	result = sqlite3_bind_int(stmt, 8, con.cod_Service);


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

Contract* viewContract(sqlite3 *db,char dni[]){

	sqlite3_stmt *stmt;
	char consulta[] =
				"select co.Matricula, co.Fecha_Inicio, co.Fecha_Fin, co.Descripcion, co.Entrega_Deposito, co.Horas_Cancelacion, co.Dni_Usuario , co.Cod_Servicio FROM Usuarios u, Contratos co WHERE (?) = co.Dni_Usuario ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_text(stmt, 1, dni,strlen(dni),
				SQLITE_STATIC);

	if (result != SQLITE_OK) {
			fprintf(stderr, "Error preparing statement: %s\n", sqlite3_errmsg(db));
			return NULL;
		}

	int num_rows = 0;
	Contract *con1;
	con1 = NULL;
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		num_rows++;

		Contract *tmp = realloc(con1, num_rows * sizeof(Contract));
		if (!tmp) {
			fprintf(stderr, "Error allocating memory\n");
			free(con1);
			return NULL;
		}
		con1 = tmp;

		const char *regist = (const char*) sqlite3_column_text(stmt, 0);
		memcpy(con1[num_rows - 1].registration_number, regist, 9);


		con1[num_rows - 1].date_Start = strdup(
				(char*) sqlite3_column_text(stmt, 1));
		con1[num_rows - 1].date_end= strdup(
				(char*) sqlite3_column_text(stmt, 2));
		con1[num_rows - 1].description= strdup(
				(char*) sqlite3_column_text(stmt, 3));
		con1[num_rows - 1].tank = sqlite3_column_int(stmt, 4);

		con1[num_rows - 1].cancellation_Hours = sqlite3_column_int(stmt, 5);



		const char *dni = (const char*) sqlite3_column_text(stmt, 6);
		memcpy(con1[num_rows - 1].registration_number, dni, 10);

		con1[num_rows - 1].cod_Service = sqlite3_column_int(stmt, 7);

	}

	sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
	        printf("Error ending prepared statement: %s\n",
	                sqlite3_errmsg(db));
	}
	printf("Prepared statement finalized (SELECT)\n");

	return con1;

}
