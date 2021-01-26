#include <stdio.h>

int main(void)
{
    int a;
    printf("enter a number: ");
    while (scanf("%d", &a) != 1)
    {
        // input was not a number, ask again:
        printf("enter a number: ");
    }
    printf("You entered %d.\n", a);
}