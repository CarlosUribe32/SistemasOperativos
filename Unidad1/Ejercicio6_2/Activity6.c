#include <stdio.h>
#include <stdlib.h>

const char INPUT_FILE[40];
const char OUTPUT_FILE[40];

int main(){
    printf("Ingrese el archivo origen\n");
    scanf("%s", INPUT_FILE);
    printf("Ingrese el archivo de salida\n");
    scanf("%s", OUTPUT_FILE);

    int ch;
    FILE *in_file = fopen(INPUT_FILE, "r");
    FILE *on_file = fopen(OUTPUT_FILE, "r+");
    if(in_file == NULL || on_file==NULL){
        printf("No se puede abrir %s o %s\n", INPUT_FILE, OUTPUT_FILE);
        exit(8);
    }
    while(1){
        ch = fgetc(in_file);
        if(ch == EOF)
            break;
        fputc(ch, on_file);
    }
    fclose(in_file);
    fclose(on_file);
    return 0;
}