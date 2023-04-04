#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include "stdout.h"
#include "stdin.h"
#include "service.h"
#include "vehicle.h"
#include "Menu.h"
#include "ctype.h"

void isAdmin(sqlite3 *db,char * dni);
void showMenuAdmin(sqlite3 *db);
unsigned short getSelection();
void eliminateVehicle(sqlite3 *db);
void viewVehicles(sqlite3 * db);
void insertNewVehicle(sqlite3 *db);
void getMarca(Vehicle *vehicle);
void getModelo(Vehicle *vehicle);
void getColor(Vehicle *vehicle);
void getPlazas(Vehicle *vehicle);
void getMatricula(Vehicle *vehicle);
void getPrecioVehiculo(Vehicle *vehicle);
void getPuertas(Vehicle *vehicle);


void insertNewService(sqlite3 *db);
void getDescripcion(Service *service);
void getPrecioServicio(Service *service);
void eliminateService(sqlite3 *db);


#endif /* ADMINISTRADOR_H_ */
