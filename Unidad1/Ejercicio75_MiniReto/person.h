#ifndef _PERSON_H
#define _PERSON_H
#include "gun.h"

typedef struct{
    char name[20];
    gun_t * gun;
}person_t;

person_t * createP(char name[20]);
void destroyP(person_t * this);
void collectGun(person_t * this, gun_t * gun);
void shootGun(person_t * this);
void pullGun(person_t * this);
void rechargeP(person_t * this, int bullets);

#endif