#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// const char INPUT_FILE[40];
// const char OUTPUT_FILE[40];

void xor(FILE *, FILE *);
void not(FILE *, FILE *);

int main(int argc, char *argv[]){
    // int op;
    // printf("Ingrese 1 si quiere encriptar, ingrese 2 si quiere desencriptar\n");
    // scanf("%d[^\n]", &op);
    // getc(stdin);

    // printf("Ingrese el archivo origen\n");
    // scanf("%s[^\n]", INPUT_FILE);
    // getc(stdin);
    // printf("Ingrese el archivo de salida\n");
    // scanf("%s[^\n]", OUTPUT_FILE);
    // getc(stdin);

    FILE *in_file = fopen(argv[1], "r");
    FILE *on_file = fopen(argv[2], "r+");

    if(in_file == NULL || on_file==NULL){
        printf("No se puede abrir %s o %s\n", argv[1], argv[2]);
        exit(8);
    }
    
    
    if(strncmp("xor", argv[3], 3) == 0)
        xor(in_file, on_file);
    else if(strncmp("not", argv[3], 3) == 0)
        not(in_file, on_file);
    
    fclose(in_file);
    fclose(on_file);
    return 0;
}

void xor(FILE * in_file, FILE * on_file){
    int ch;
    while(1){
        ch = fgetc(in_file);
        if(ch == EOF)
            break;
        ch=ch^0xFF;
        fputc(ch, on_file);
    }
}
void not(FILE * in_file, FILE * on_file){
    int ch;
    while(1){
        ch = fgetc(in_file);
        if(ch == EOF)
            break;
        ch = ~ch;
        fputc(ch, on_file);
    }
}