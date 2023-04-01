/*
 * BD.h
 *
 *  Created on: 1 abr 2023
 *      Author: ihern
 */

#ifndef BD_H_
#define BD_H_

#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>

typedef struct{

	int cod_Service;
	char description[60];
	float price;
	int type;

}Service;

typedef struct{

	char registration_number[9];
	int num_doors;
	char *color;
	char *model;
	char *brand;
	int num_seats;
	float price;

}vehicle;

typedef struct{

	char dni[10];
	char * name;
	char * surname1;
	char * surname2;
	char * Email;
	int type;
	char * password;
	char * prefer_Language;

}User;

typedef struct{

	int cod_Insurance;
	float price;
	char * type;
	char  registration_number[9];
	char * date_Start;

}Insurance;

typedef struct{

	char registration_number[9];
	char * date_Start;
	char * date_end;
	char * description;
	int tank;
	int cancellation_Hours;
	char dni_User[10];

}Contract;




int insertService(sqlite3 *db, Service sr);
int deleteService(sqlite3 *db, int cod);
int insertVehicle(sqlite3 *db, vehicle ve);
int deleteVehicle(sqlite3 *db, char matricula[]);
int insertUser(sqlite3 *db, User u);
int modifyUser(sqlite3 *db, char * contrasenya, User u);
int insertContract(sqlite3 *db, Contract con);
int deleteContract(sqlite3 *db, Contract con);


#endif /* BD_H_ */
