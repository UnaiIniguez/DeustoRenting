#include <stdio.h>
#include <stdlib.h>
#include "std/stdout.h"
#include "elements/user.h"
#include "elements/menu.h"


void config(void);
void start(void);

int main(int argc, char* argv[]){
	config();
	start();
}



void config(void){
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
}


void start(void){
	printfln("BIENVENIDO A DEUSTORENTING");
	printLine();
	User* user = calloc(1, sizeof(user));
	getUser(user);
	showMenu(user);
}
