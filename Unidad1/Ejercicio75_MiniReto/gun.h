#ifndef _GUN_H
#define _GUN_H

typedef struct{
    char tipo[20];
    int bullets;
}gun_t;

gun_t * createG(char tipo[20]);
void destroyG(gun_t * this);
void rechargeG(gun_t * this, int bullets);
void shootG(gun_t * this);

#endif