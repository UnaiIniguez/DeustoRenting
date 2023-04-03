#ifndef SERVICE_H_
#define SERVICE_H_

#include "../../lib/sqlite3.h"
#include "string.h"
#include "../elements/user.h"
#include "../std/stdin.h"
#include "../std/stdout.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct{

	int cod_Service;
	char *description;
	float price;
	int type;

}Service;

unsigned short optionSelected(Service *services, int num_services);
void printServicios(User user, sqlite3 *db);

#endif
