#include <stdio.h>

typedef struct estudiante_t
{
    char nombre[40];
    int numEstudiante;
    int agnoMatricula;
    float nota;
}estudiante;
void actualizar(estudiante *);
int main(void){
    estudiante estudi1 ={"Jose", 4, 2009, 4.5};
    estudiante *pEstudiante;
    pEstudiante = &estudi1;
    printf("La nota de %s es %2.f, su agno de matricula es: %d de numero %d\n",pEstudiante ->nombre ,pEstudiante->nota, pEstudiante ->agnoMatricula, pEstudiante ->numEstudiante);
    printf("Presione r si quiere actualizar los datos del estudiante\n");
    char op;
    scanf("%c", &op);
    if(op=='r'){
        actualizar(pEstudiante);
        printf("La nota de %s es %2.f, su agno de matricula es: %d de numero %d\n",pEstudiante ->nombre ,pEstudiante->nota, pEstudiante ->agnoMatricula, pEstudiante ->numEstudiante);
    }
    return 0;
}

void actualizar(estudiante *pEstudiante){
    printf("Ingrese el nombre del estudiante, numero, agno y nota:\n");
    scanf("%s %d %d %f", pEstudiante->nombre, &pEstudiante->numEstudiante, &pEstudiante->agnoMatricula, &pEstudiante->nota);
}
