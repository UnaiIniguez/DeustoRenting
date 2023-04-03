#ifndef CONTRACT_H_
#define CONTRACT_H_

#include "sqlite3.h"
#include "user.h"
#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char* registration_number;
	char* date_Start;
	char* date_end;
	char* description;
	int tank;
	int cancellation_Hours;
	char* dni_User;
	int cod_Service;
}Contract;

void initContract(Vehicle vehicle);
int insertContract(sqlite3* db, Contract con);	//Insertar contrato
int deleteContract(sqlite3* db, Contract con);	//Anular contrato
Contract* viewContract(sqlite3 *db,char *dni);

#endif
