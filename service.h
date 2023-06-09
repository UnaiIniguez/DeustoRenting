#ifndef SERVICE_H_
#define SERVICE_H_

#include "sqlite3.h"
#include "string.h"
#include "user.h"
#include "stdin.h"
#include "stdout.h"
#include "contract.h"
#include "rwDocs.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int cod_Service;
	char *description;
	float price;
}Service;


void bookService(User* user);
unsigned short getSelectedServiceIndex(unsigned short optionMax);
Service showServices(void);
void printServicios(User user, sqlite3 *db) ;
unsigned short optionSelected(Service *services, int num_services);
Service * getServices(sqlite3* db, unsigned short* num_services);	//Devuelve todos los servicios de la base de datos
int insertService(sqlite3 *db, Service sr);	//Insertar Servicio
int deleteService(sqlite3 *db, int cod);	//Eliminar servicio
int insertServiceInContract(sqlite3 *db, User u, Service *service);	//Inserta en un contrato el servicio

#endif
