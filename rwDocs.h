#ifndef RWDOCS_H_
#define RWDOCS_H_

#include <stdio.h>
#include "contract.h"

void readFileTXT(char *archivo);

void writeFileTXT(Contract contract, char *archivo);

void writeRules(char *archivo);

void logger(char *archivo);

#endif
