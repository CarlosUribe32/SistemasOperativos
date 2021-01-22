#include <stdio.h>

int main(void){
    int A[6]={2,3,1,0,9,6};
    int *ptr1;
    int *ptr2 = &A[5];
    ptr1 = A;
    ptr1+=2;
    *ptr1=5;
    ptr2--;
    *(ptr2)=*ptr1+*(ptr2-1)+*(ptr2+1);
    printf("%d-%d-%d-%d-%d-%d", A[0], A[1], A[2], A[3], A[4], A[5]);
}