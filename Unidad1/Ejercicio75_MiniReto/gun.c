#include "gun.h"
#include <stdlib.h>

gun_t * createG(char tipo[20]){
    gun_t *g = malloc(sizeof(gun_t));
    strcpy(g->tipo, tipo);
    g->bullets = 0;
    return g;
}

void destroyG(gun_t *this){
    free(this);
}

void rechargeG(gun_t *this, int bullets){
    if(bullets<0){
        printf("No se puede recargar este numero de balas\n");
        return;
    }
    this->bullets = this->bullets + bullets;
}

void shootG(gun_t * this){
    if(this->bullets == 0){
        printf("Se acabaron las balas, recargue\n");
        return;
    }
    this->bullets = this->bullets - 1;
    printf("POW!, quedan %d balas\n", this->bullets);
}