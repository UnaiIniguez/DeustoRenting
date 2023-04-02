#include <stdio.h>
#include <stdlib.h>
#include "std/stdout.h"
#include "elements/user.h"


void initBuffers(void);
void start(void);

int main(int argc, char* argv[]){
	initBuffers();
	start();
}



// Inicializa los buffers de salida a NULL
void initBuffers(void){
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
}


void start(void){
	printfln("BIENVENIDO A DEUSTORENTING");
	printLine();
	User* user = calloc(1, sizeof(user));
	getUser(user);
}
