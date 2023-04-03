#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "stdout.h"
#include "stdin.h"
#include <stdio.h>
#include <stdlib.h>
#include "user.h"

typedef struct{
	char registration_number[9];
	int num_doors;
	char *color;
	char *model;
	char *brand;
	int num_seats;
	float price;
}Vehicle;

void bookVehicle(User* user);
int showVechiles(void);
void bookVehicle(User* user);
short getVehicleIndex(void);

int insertVehicle(sqlite3 *db, Vehicle ve);	//Insertar vehiculo
Vehicle* availableVehicles(sqlite3 *db, int *num_vehicles);	//Los vehiculos disponibles
Vehicle * usersVehicles(sqlite3 *db,char* dni);
int deleteVehicle(sqlite3 *db, char registration_number[]);	//Eliminar vehiculo

#endif
