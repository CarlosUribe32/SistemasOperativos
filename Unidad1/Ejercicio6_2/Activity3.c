#include <stdio.h>
struct point
{
    int x;
    int y;
};

struct rect{
    struct point pt1;
    struct point pt2;
};

int areaRectangulo(struct rect);
int main(void){
    struct rect a;
    printf("Ingrese el punto 1 (Coordenadas X, Y)\n");
    scanf("%d",&a.pt1.x);
    scanf("%d",&a.pt1.y);
    printf("Ingrese el punto 2 (Coordenadas X, Y)\n");
    scanf("%d",&a.pt2.x);
    scanf("%d",&a.pt2.y);
    int area = areaRectangulo(a);
    printf("El area del rectangulo: %d\n", area);
    return 0;
}

int areaRectangulo(struct rect a){
    int base = fabs(a.pt2.x - a.pt1.x);
    int altura = fabs(a.pt2.y - a.pt1.y);
    return base*altura;
}