#include <stdio.h>
 #include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("argc =  %d\n",argc);
    for(int i = 0; i< argc; i++){
        printf("argv[%d] = %s\n", i,argv[i]);
    }
    exit(EXIT_SUCCESS); // exit(EXIT_FAILURE) en caso de error
}