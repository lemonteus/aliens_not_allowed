#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "basicStructures.h"

typedef struct{
    unsigned short int enemyID; // A unique identification to the enemy
    unsigned short int healthPoints;
    unsigned short int attackPoints;
    Vector2D dimensions;
    Vector2D position;
} Enemy;


void enemy_update();

// To be used in order update the player's health points
Vector2D* enemy_getProjectiles();

// To be called whenever an enemy got hit
void enemy_gotHit(unsigned int enemyID, unsigned int attackPoints);
Enemy* enemy_getEnemies();


#endif //_ENEMY_H_