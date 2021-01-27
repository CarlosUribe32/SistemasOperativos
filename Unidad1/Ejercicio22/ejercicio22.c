#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// const char INPUT_FILE[40];
// const char OUTPUT_FILE[40];

void encriptar(FILE *, FILE *);
void desencriptar(FILE *, FILE *);

int main(int argc, char *argv[]){
    int op;
    printf("Ingrese 1 si quiere encriptar, ingrese 2 si quiere desencriptar\n");
    scanf("%d[^\n]", &op);
    getc(stdin);

    // printf("Ingrese el archivo origen\n");
    // scanf("%s[^\n]", INPUT_FILE);
    // getc(stdin);
    // printf("Ingrese el archivo de salida\n");
    // scanf("%s[^\n]", OUTPUT_FILE);
    // getc(stdin);

    FILE *in_file = fopen(argv[1], "r");
    FILE *on_file = fopen(argv[2], "r+");

    if(in_file == NULL || on_file==NULL){
        printf("No se puede abrir %s o %s\n", INPUT_FILE, OUTPUT_FILE);
        exit(8);
    }

    if(op==1)
        encriptar(in_file, on_file);
    else if(op==2)
        desencriptar(in_file, on_file);
    
    fclose(in_file);
    fclose(on_file);
    return 0;
}

void encriptar(FILE * in_file, FILE * on_file){
    int ch;
    while(1){
        ch = fgetc(in_file);
        if(ch == EOF)
            break;
        ch*=2;
        fputc(ch, on_file);
    }
}
void desencriptar(FILE * in_file, FILE * on_file){
    int ch;
    while(1){
        ch = fgetc(in_file);
        if(ch == EOF)
            break;
        ch/=2;
        fputc(ch, on_file);
    }
}