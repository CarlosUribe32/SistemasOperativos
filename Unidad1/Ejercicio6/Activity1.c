#include <stdio.h>

int main(void){
    int a, b=3, c=8, d;
    int *p1 = &a, *p2, *p3 = &c;
    *p1 = 2;
    p2 = p3;
    *p2 = *p1-b;
    d = (*p2)*(*p1);
    p3 = &d;
    b = a + b + c;
    printf("%d\n", b);
    return 0;
}