#ifndef CONTRACT_H_
#define CONTRACT_H_

typedef struct{
	char* registration_number;
	char* date_Start;
	char* date_end;
	char* description;
	int tank;
	int cancellation_Hours;
	char* dni_User;
}Contract;

#endif
