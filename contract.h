#ifndef CONTRACT_H_
#define CONTRACT_H_

#include "sqlite3.h"
#include "user.h"
#include "vehicle.h"
#include "service.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
	char* registration_number;
	char* date_start;
	char* date_end;
	int tank;
	int cancellation_hours;
	char* dni_user;
	int cod_service;
}Contract;

void returnContract(User* user);
void printContract(Contract contract);
void showContract(User* user);
void showOptions(void);
unsigned short getServiceOption(void);
void bookVehicle(User* user);
void initContract(Vehicle vehicle, char* dni);
int insertContract(sqlite3* db, Contract con);	//Insertar contrato
int deleteContract(sqlite3* db, Contract con);	//Anular contrato
Contract* getContract(sqlite3 *db, char* dni);
void generateContract(char* dni, char* registration_number, int cod_service);
int randomInt(int min, int max);
char* getDateStart();
char* getDateEnd();
void writeContractTXT(Contract contract, char *archivo);

#endif
