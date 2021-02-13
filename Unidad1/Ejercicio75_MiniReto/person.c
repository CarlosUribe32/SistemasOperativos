#include "person.h"
#include <stdlib.h>

person_t * createP(char name[20]){
    person_t *p = malloc(sizeof(person_t));
    strcpy(p->name, name);
    printf("Hola %s\n", p->name);
    return p;
}

void destroyP(person_t *this){
    free(this);
}

void collectGun(person_t * this, gun_t * gun){
    this->gun = gun;
    printf("Tu arma es una %s\n", this->gun->tipo);
}

void shootGun(person_t * this){
    shootG(this->gun);
}

void pullGun(person_t * this){
    destroyG(this->gun);
    printf("Ya no tienes arma xD\n");
}

void rechargeP(person_t * this, int bullets){
    rechargeG(this->gun, bullets);
    printf("Ahora tu arma tiene %d balas\n", this->gun->bullets);
}