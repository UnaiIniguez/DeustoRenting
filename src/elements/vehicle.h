#ifndef VEHICLE_H_
#define VEHICLE_H_

typedef struct{
	char registration_number[9];
	int num_doors;
	char *color;
	char *model;
	char *brand;
	int num_seats;
	float price;
}Vehicle;

#endif
