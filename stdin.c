#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITIAL_SIZE 30

int readLine(char **input) {
	printf("-->");

    size_t size = INITIAL_SIZE;
    char* buffer = calloc(size, sizeof(char));
    int i = 0;
    char c = getchar();
    while (c != '\n' && c != EOF) {
        if (i < size - 1) {
            buffer[i++] = c;
        }else{
        	size *= 2;
        	buffer = realloc(buffer, size);
        	if(buffer == NULL){
        		fprintf(stderr, "Error en la asignacion de memoria");
        		return -1;
        	}
        }
        c = getchar();
    }
    buffer[i] = '\0';
    *input = calloc(i + 1, sizeof(char));
    if (*input == NULL) {
        return -1;
    }
    strcpy(*input, buffer);
    return i;
}

