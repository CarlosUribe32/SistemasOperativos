#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t encXorFunction(uint8_t data) { return data ^ 0xFF; }

int main(int argc, char *argv[]) {
char input[50];
char inFile[20];
char outFile[20];
char function[10];
uint8_t (*encFuntion)(uint8_t) = NULL;

printf("Enter in_file out_file function\n");
fgets(input, sizeof(input), stdin);
sscanf(input, "%s %s %s", inFile, outFile, function);

FILE *fin = fopen(inFile, "r");
if (fin == NULL) {
    perror("Error: ");
    return EXIT_FAILURE;
}

if (strncmp("xor", function, 3) == 0) {
    encFuntion = &encXorFunction;
}

FILE *fout = fopen(outFile, "w");
if (fout == NULL) {
    perror("Error: ");
    return EXIT_FAILURE;
}

while ( fgets(input, sizeof(input), fin) != NULL) {

    int n = strlen(input);

    for (int i = 0; i < n; i++) {
    input[i] = (*encFuntion)(input[i]);
    }
    fputs(input, fout);
}

fclose(fin);
fclose(fout);
return EXIT_SUCCESS;
}