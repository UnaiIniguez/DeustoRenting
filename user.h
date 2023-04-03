#ifndef USER_H_
#define USER_H_

#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
#include "stdout.h"
#include "stdin.h"
#include "string.h"

typedef struct{
	char* dni;
	char* name;
	char* surname1;
	char* surname2;
	char* email;
	char* password;
	char* prefer_Language;
	int type;
}User;

void getUser(User* user);
unsigned short getOption(void);
void checkDNI(User* user);
void checkPassword(User* user);
void getName(User* user);
void getSurname1(User* user);
void getSurname2(User* user);
void getEmail(User* user);
void getPassword(User* user, char* string);
void getDNI(User* user);
int insertUser(sqlite3 *db, User u);	//Insertar nuevo usuario
int modifyUser(sqlite3 *db, char * password, User u);	//modificar contrasenya de usuario
int typeUser(sqlite3 *db, char *dni);	//Devuelve el tipo de usuario que es el user
int userExist(sqlite3 *db, char *DNI, char * password);	//Comprobar si el usuario existe
#endif
