#ifndef BD_H_
#define BD_H_
#include <stdio.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include "contract.h"
#include "service.h"
#include "vehicle.h"
#include "insurance.h"
#include "user.h"

int insertService(sqlite3 *db, Service sr);	//Insertar Servicio
int deleteService(sqlite3 *db, int cod);	//Eliminar servicio
//********************************************
Service * getServices(sqlite3 *db, int *num_services);	//Devuelve todos los servicios de la base de datos
//********************************************
int insertServiceInContract(sqlite3 *db, User  u, Service * service);	//Inserta en un contrato el servicio
int insertVehicle(sqlite3 *db, Vehicle ve);	//Insertar vehiculo
int deleteVehicle(sqlite3 *db, char registration_number[]);	//Eliminar vehiculo

int insertUser(sqlite3 *db, User u);	//Insertar nuevo usuario
int modifyUser(sqlite3 *db, char * password, User u);	//modificar contrasenya de usuario
int typeUser(sqlite3 *db, char *dni);	//Devuelve el tipo de usuario que es el user
int userExist(sqlite3 *db, char *DNI, char * password);	//Comprobar si el usuario existe

int insertContract(sqlite3 *db, Contract con);	//Insertar contrato
int deleteContract(sqlite3 *db, Contract con);	//Anular contrato
Contract* viewContract(sqlite3 *db,char *dni);

Vehicle* availableVehicles(sqlite3 *db, int *num_vehicles);	//Los vehiculos disponibles
Vehicle * usersVehicles(sqlite3 *db,char* dni);
int hasDNI(char* DNI);
int hasPassword(char* password);


#endif
