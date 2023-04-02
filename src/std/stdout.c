#include <stdio.h>
#include <stdarg.h>

#define N 30

int printfln(const char *format, ...){
    va_list argptr;
    int result;
    va_start(argptr, format);
    result = vprintf(format, argptr);
    va_end(argptr);
    putchar('\n');
    return result;
}

void printLine(void){
	for(int i = 0; i < N; i++) printf("-");
	printf("\n");
}
