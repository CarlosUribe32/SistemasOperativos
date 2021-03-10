#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int p[2];
    pipe(p);
    return 0;
}