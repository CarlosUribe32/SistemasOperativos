#include <stdio.h>

int main(void){
    float x = 333.123456;
    double y = 333.1234567890123456;
    char lett = 'w';

    printf("%f\n", x);
    printf("%.1f\n", x);
    printf("%20.3f\n", x);
    printf("%-20.3f%c\n", x, lett);
    printf("%020.3f\n", x);
    printf("%.9f\n", y);
    printf("%.20f\n", y);
    printf("%20.4f\n", y);
    return(0);
}