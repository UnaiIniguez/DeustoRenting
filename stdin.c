#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFERSIZE 10

void readLine(char** string){

    printf("-->");

    size_t stringSize = strlen(*string);
    size_t charsRead = getline(string, &stringSize, stdin);
    if (charsRead == -1) {
        fprintf(stderr, "ERROR EN LA LECTURA\n");
        return;
    }
}
