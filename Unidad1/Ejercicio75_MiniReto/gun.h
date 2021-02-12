#ifndef _GUN_H
#define _GUN_H

typedef struct{
    char tipo[20];
    int bullets;
}gun_t;

gun_t * create(char tipo[20]);
void destroy(gun_t * this);
void recharge(gun_t * this, int bullets);
void shoot(gun_t * this);

#endif