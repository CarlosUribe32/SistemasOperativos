#ifndef _PERSON_H
#define _PERSON_H
#include <stdio.h>
#include "gun.h"

typedef struct{
    char name[20];
    gun_t * gun;
}person_t;

#endif