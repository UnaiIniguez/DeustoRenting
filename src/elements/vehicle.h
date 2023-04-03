#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "vehicle.h"
#include "../std/stdout.h"
#include "../std/stdin.h"
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
short showVechiles(void);
void bookVehicle(User* user);
short getVehicleIndex(void);

#endif
