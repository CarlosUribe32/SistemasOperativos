#include <stdio.h>
#include "gun.h"
#include "person.h"

int main(int argc, char** argv){
    person_t * p = createP("Carlos");
    gun_t * g = createG("Calibre .50");
    collectGun(p, g);
    rechargeP(p, 6);

    shootGun(p);
    shootGun(p);
    shootGun(p);
    shootGun(p);
    shootGun(p);
    shootGun(p);
    shootGun(p);
    shootGun(p);

    rechargeP(p, 6);
    shootGun(p);
    rechargeP(p, 6);

    pullGun(p);
    destroyP(p);
}