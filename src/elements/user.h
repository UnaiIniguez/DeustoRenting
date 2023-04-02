#ifndef USER_H_
#define USER_H_

typedef struct{
	char* dni;
	char* name;
	char* surname1;
	char* surname2;
	char* email;
	char* password;
	char* prefer_Language;
	int type;
}User;

void getUser(User* user);
unsigned short getOption(void);
void checkDNI(User* user);
void checkPassword(User* user);
void getName(User* user);
void getSurname1(User* user);
void getSurname2(User* user);
void getEmail(User* user);
void getPassword(User* user, char* string);
void getDNI(User* user);

#endif
