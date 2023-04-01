
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
		printf("Error metiendo parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando parametros\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (INSERT)\n");


}

int deleteService(sqlite3 *db, int cod){
	sqlite3_stmt *stmt;
	char consulta[] =
			"delete from Servicios_Adicionales where Cod_Servicio = (?) ;";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	result = sqlite3_bind_int(stmt, cod, 1);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando parametros\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (DELETE)\n");


}

int insertVehicle(sqlite3 *db, vehicle ve) {

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

	result = sqlite3_bind_text(stmt, 5, ve.registration_number, strlen(ve.registration_number),
			SQLITE_STATIC);
	result = sqlite3_bind_double(stmt, 6, ve.price);
	result = sqlite3_bind_int(stmt, 7 , ve.num_doors);

	if (result != SQLITE_OK) {
		printf("Error metiendo parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando parametros\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (INSERT)\n");

}

int deleteVehicle(sqlite3 *db, char matricula[]){

	sqlite3_stmt *stmt;
		char consulta[] =
				"delete from Vehiculos where Matricula = (?) ;";

		int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
		result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula),
					SQLITE_STATIC);
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error eliminando parametros\n");
			return result;
		}
		result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (DELETE)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}

		printf("Prepared statement finalized (DELETE)\n");

}

int insertUser(sqlite3 *db, User u){

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
		result = sqlite3_bind_text(stmt, 5, u.Email, strlen(u.Email),
								SQLITE_STATIC);
		result = sqlite3_bind_int(stmt, 6, u.type);

		result = sqlite3_bind_text(stmt, 7, u.password, strlen(u.password),
								SQLITE_STATIC);
		result = sqlite3_bind_text(stmt, 8, u.prefer_Language, strlen(u.prefer_Language),
								SQLITE_STATIC);


		if (result != SQLITE_OK) {
			printf("Error metiendo parametros\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error insertando parametros\n");
			return result;
		}
		result = sqlite3_finalize(stmt);
		if (result != SQLITE_OK) {
			printf("Error finalizing statement (INSERT)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}

		printf("Prepared statement finalized (INSERT)\n");
}

int modifyUser(sqlite3 *db, char * password, User u){

	sqlite3_stmt *stmt;
			char consulta[] =
					"UPDATE Usuarios SET Contrasenya = (?) where DNI = (?) ;";


			int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
			result = sqlite3_bind_text(stmt, 1, password, strlen(password),
						SQLITE_STATIC);
			result = sqlite3_bind_text(stmt, 2, u.dni, strlen(u.dni),
									SQLITE_STATIC);

			result = sqlite3_step(stmt);
			if (result != SQLITE_DONE) {
				printf("Error insertando parametros\n");
				return result;
			}
			result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (MODIFY)\n");
				printf("%s\n", sqlite3_errmsg(db));
				return result;
			}

			printf("Prepared statement finalized (MODIFY)\n");


}

int insertContract(sqlite3 *db, Contract con){

	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Contratos(Matricula, Fecha_Inicio, Fecha_Fin, Descripcion, Entrega_Deposito, Horas_Cancelacion, Dni_Usuario) values (?,?,?,?,?,?,?)  ; ";

	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);

	result = sqlite3_bind_text(stmt, 1, con.registration_number, strlen(con.registration_number),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 2, con.date_Start, strlen(con.date_Start),
	SQLITE_STATIC);

	result = sqlite3_bind_text(stmt, 3, con.date_end, strlen(con.date_end),
	SQLITE_STATIC);
	result = sqlite3_bind_text(stmt, 4, con.description, strlen(con.description),
	SQLITE_STATIC);
	result = sqlite3_bind_int(stmt, 5, con.tank);
	result = sqlite3_bind_int(stmt, 6, con.cancellation_Hours);

	result = sqlite3_bind_text(stmt, 7, con.dni_User, strlen(con.dni_User),
	SQLITE_STATIC);

	if (result != SQLITE_OK) {
		printf("Error metiendo parametros\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando parametros\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (INSERT)\n");

}

int deleteContract(sqlite3 *db, Contract con){

	sqlite3_stmt *stmt;
			char consulta[] =
					"delete from Contratos where Matricula = (?) and Fecha_Inicio = (?) ;";

			int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
			result = sqlite3_bind_text(stmt, 1, con.registration_number, strlen(con.registration_number),
						SQLITE_STATIC);

			result = sqlite3_bind_text(stmt, 2, con.date_Start, strlen(con.date_Start),
									SQLITE_STATIC);
			result = sqlite3_step(stmt);
			if (result != SQLITE_DONE) {
				printf("Error eliminando parametros \n");
				return result;
			}
			result = sqlite3_finalize(stmt);
			if (result != SQLITE_OK) {
				printf("Error finalizing statement (DELETE)\n");
				printf("%s\n", sqlite3_errmsg(db));
				return result;
			}

			printf("Prepared statement finalized (DELETE)\n");

}



