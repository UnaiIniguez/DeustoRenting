#ifndef RWDOCS_H_
#define RWDOCS_H_

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


void readFileTXT(char *archivo);

int readConfigTXT();

void writeRules(char *archivo, char *nombre);

void logger(char *archivo);

#endif
