#ifndef USER_H_
#define USER_H_

#include "sqlite3.h"
#include <stdlib.h>
#include <stdio.h>
#include "stdout.h"
#include "stdin.h"
#include "string.h"
#include "rwDocs.h"

typedef struct{
	char* dni;
	char* name;
	char* surname1;
	char* surname2;
	char* email;
	char* password;
	int type;
}User;


char* getUserName(sqlite3 *db, char* dni);
void checkUser(User* user);
void getUser(User* user);
unsigned short getOption(void);
void getName(User* user);
void getSurname1(User* user);
void getSurname2(User* user);
void getEmail(User* user);
void getPassword(User* user, char* string);
void getDNI(User* user);
int insertUser(User u);	//Insertar nuevo usuario
int modifyUser(sqlite3 *db, char * password, User u);	//modificar contrasenya de usuario
int typeUser(sqlite3 *db, char *dni);	//Devuelve el tipo de usuario que es el user
int userExist(sqlite3 *db, char *DNI, char * password);	//Comprobar si el usuario existe
#endif
