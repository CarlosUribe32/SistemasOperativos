#include <stdio.h>
#include <stdint.h>

uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize);


int main (void){
    int32_t arr1Size;
    int32_t arr2Size;

    printf("Ingrese el tamaño del primer vector\n");
    scanf("%d[^\n]", &arr1Size);
    getc(stdin);
    int32_t arr1[arr1Size];
    printf("Ingrese los elementos del vector:\n");
    for (int32_t i = 0; i < arr1Size; i++){
        scanf("%d[^\n]", (arr1+i));
        getc(stdin);
    }

    printf("Ingrese el tamaño del segundo vector\n");
    scanf("%d[^\n]", &arr2Size);
    getc(stdin);
    int32_t arr2[arr2Size];
    printf("Ingrese los elementos del vector:\n");
    for (int32_t i = 0; i < arr2Size; i++){
        scanf("%d[^\n]", (arr2+i));
        getc(stdin);
    }

    int32_t arrResSize;
    if (arr1Size<arr2Size)
        arrResSize = arr1Size;
    else
        arrResSize = arr2Size;
    int32_t arrRes [arrResSize];
    uint8_t comun = arrayCommon(arr1, arr1Size,arr2,arr2Size,arrRes, arrResSize);
    printf("Se encontraron: %d elementos en comun\n", comun);
    for (uint8_t i = 0; i < comun; i++){
        printf("%d ", *(arrRes+i));
    }
    printf("\n");
    return 0;
}

uint8_t arrayCommon(int32_t* arr1, int32_t arr1Size,int32_t* arr2, int32_t arr2Size, int32_t* arrRes, int32_t arrResSize){
    uint8_t comun=0;
    int a;
    for (int32_t i = 0; i < arr1Size; i++){
        a = 0;
        for (int32_t j = 0; j < arr2Size; j++){
            if(*(arr1+i)==*(arr2+j)){
                a = 1;
                break;
            }
        }
        if(a==1){
            for (int32_t j = 0; j < arrResSize; j++){
                if(*(arr1+i)==*(arrRes+j)){
                    a == 0;
                    break;
                }
            }
            if(a==1){
                int32_t* parr = arrRes;
                parr += comun;
                *parr = *(arr1+i);
                comun++;
            }
        }   
    }
    return comun;
}