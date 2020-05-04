#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "basicStructures.h"

struct{
    unsigned int healthPoints;
    unsigned int attackPoints;
    Vector2D position;
} typedef Enemy;

#endif //_ENEMY_H_