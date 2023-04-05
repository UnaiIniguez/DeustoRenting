#include "user.h"

void getUser(User* user){
	if(getOption()){
		printf("\n");
		printfln("REGISTRARSE");
		printLine();
		getDNI(user);
		getName(user);
		getSurname1(user);
		getSurname2(user);
		getEmail(user);
		getPassword(user, "deseada");
		user->type = 0;
		insertUser(*user);
	}else{
		printf("\n");
		printfln("INICIAR SESIÓN");
		printLine();
		getDNI(user);
		getPassword(user, "");
		checkUser(user);
	}
}

void checkUser(User* user){
	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
		exit(1);
	}
	if(!userExist(db, user->dni, user->password)){
		printfln("El usuario con dni '%s' y contraseña '%s' no existe en la base de datos");
		sqlite3_close(db);
		getUser(user);
	}else{
		printfln("Sesión iniciada con éxito");
		sqlite3_close(db);
	}
}

void getName(User* user){
	printfln("Introduzca su nombre");
	char* input = calloc(10, sizeof(char));
	readLine(&input);
	user->name = calloc(strlen(input), sizeof(char));
	strcpy(user->name, input);
	free(input); input=NULL;
}

void getSurname1(User* user){
	printfln("Introduzca su primer apellido");
	char* input = calloc(10, sizeof(char));
	readLine(&input);
	user->surname1 = calloc(strlen(input), sizeof(char));
	strcpy(user->surname1, input);
	free(input); input=NULL;
}

void getSurname2(User* user){
	printfln("Introduzca su segundo apellido");
	char* input = calloc(10, sizeof(char));
	readLine(&input);
	user->surname2 = calloc(strlen(input), sizeof(char));
	strcpy(user->surname2, input);
	free(input); input=NULL;
}

void getEmail(User* user){
	printfln("Introduzca su dirección de email");
	char* input = calloc(13, sizeof(char));
	readLine(&input);
	while(strcmp(&input[strlen(input) - 10], "@gmail.com")){
		fprintf(stderr, "%s", input);
		printfln("Introduce una dirección que acabe en '@gmail.com'");
		free(input); input=NULL;
		input = calloc(13, sizeof(char));
		readLine(&input);
	}
	user->email = calloc(strlen(input), sizeof(char));
	strcpy(user->email, input);
	free(input); input=NULL;
}

void getDNI(User* user){
	printfln("Introduzca su DNI");
	char* input = calloc(10, sizeof(char));
	readLine(&input);
	while(strlen(input) != 9){
		printfln("El DNI debe tener 9 carácteres. Usted ha introducido %d", strlen(input));
		free(input); input=NULL;
		input = calloc(10, sizeof(char));
		readLine(&input);
	}
	user->dni = calloc(strlen(input), sizeof(char));
	strcpy(user->dni, input);
	free(input); input = NULL;
}

void getPassword(User* user, char* string){
	printfln("Introduzca su contraseña %s", string);
	char* input = NULL;
	int length = readLine(&input);
	user->password = calloc(length + 1, sizeof(char));
	if (user->password == NULL) {
		fprintf(stderr, "Error\n");
	}
	strcpy(user->password, input);
	free(input); input = NULL;
}

unsigned short getOption(void){
	unsigned short option = 2;
	printfln("¿Qué desea hacer?\n\t0. Inciar Sesión\n\t1. Registrarme");
	char* input = calloc(3, sizeof(char));
	readLine(&input);
	sscanf(input, "%hu", &option);
	while(option > 1){
		free(input); input=NULL;
		input = calloc(3, sizeof(char));
		printfln("La opción '%d' no existe. Seleccione una opción válida", option);
		readLine(&input);
		sscanf(input, "%hu", &option);
	}
	free(input); input=NULL;
	return option;
}


int insertUser(User u) {
	sqlite3* db;
	if(sqlite3_open("DeustoRenting.db", &db) != SQLITE_OK){
		fprintf(stderr, "Error al conectarse a la base de datos");
		exit(1);
	}
	sqlite3_stmt *stmt;
	char consulta[] =
			"insert into Usuarios(DNI, Nombre, Apellido1, Apellido2, Correo, Tipo, Contrasenya) values (?,?,?,?,?,?,?)  ; ";

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

	if (result != SQLITE_OK) {
		printf("Error with parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result = 0;
	}
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insert parameters\n");
		sqlite3_close(db);
		return result = 0;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result = 0;
	}

	logger("Usuario registrado");
	sqlite3_close(db);
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

int typeUser(sqlite3 *db, char *dni){
	sqlite3_stmt *stmt;
	char consulta[] = "SELECT Tipo FROM usuarios WHERE DNI = ? ;";
	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		fprintf(stderr, "Error en la preparación del statement: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		fprintf(stderr, "Error en la asignación de parámetros: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_ROW) {
		// Si la consulta devuelve un error
		printf("Error: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return 0;
	}

	int type = 0; // Inicializar como usuario normal
	if (sqlite3_column_count(stmt) > 0) { // Si hay alguna columna en la fila devuelta
		type = sqlite3_column_int(stmt, 0); // Extraer el valor de la primera columna como entero
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error ending prepared statement: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	return type;
}


int userExist(sqlite3 *db, char *DNI, char *password) {
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
		fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		fprintf(stderr, "Error ending prepared statement: %s\n",
				sqlite3_errmsg(db));
	}

	return 0;
}

char* getUserName(sqlite3 *db, char* dni){
	sqlite3_stmt *stmt;
	char consulta[] = "SELECT Nombre FROM usuarios WHERE DNI = ? ;";
	int result = sqlite3_prepare_v2(db, consulta, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		fprintf(stderr, "Error en la preparación del statement: %s\n", sqlite3_errmsg(db));
		return NULL;
	}

	result = sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		fprintf(stderr, "Error en la asignación de parámetros: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return NULL;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_ROW) {
		// Si la consulta devuelve un error
		printf("Error: %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		return NULL;
	}

	char* name = NULL;
	if (sqlite3_column_count(stmt) > 0) { // Si hay alguna columna en la fila devuelta
		name = strdup((char*)sqlite3_column_text(stmt, 0)); // Copiar el valor de la primera columna como cadena
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error ending prepared statement: %s\n", sqlite3_errmsg(db));
		free(name);
		return NULL;
	}

	return name;


}
