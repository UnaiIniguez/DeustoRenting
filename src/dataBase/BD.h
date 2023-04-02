#ifndef BD_H_
#define BD_H_
#include <stdio.h>
#include "../../lib/sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include "../elements/contract.h"
#include "../elements/service.h"
#include "../elements/vehicle.h"
#include "../elements/insurance.h"
#include "../elements/user.h"

int insertService(sqlite3 *db, Service sr);
int deleteService(sqlite3 *db, int cod);
int insertVehicle(sqlite3 *db, Vehicle ve);
int deleteVehicle(sqlite3 *db, char registration_number[]);
int insertUser(sqlite3 *db, User u);
int modifyUser(sqlite3 *db, char * password, User u);
int insertContract(sqlite3 *db, Contract con);
int deleteContract(sqlite3 *db, Contract con);
int hasDNI(char* DNI);
int hasPassword(char* password);


#endif
