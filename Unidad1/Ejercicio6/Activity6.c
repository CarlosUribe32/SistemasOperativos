#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char *buffer;
    char *string1 = "Hola ";
    buffer = malloc(sizeof(char)*30);
    strcpy(buffer, string1);
    strcat(buffer, "Mundo");
    puts(buffer);
    free(buffer);
    return 0;
}