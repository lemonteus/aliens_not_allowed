#ifndef _PLAYER_H_
#define _PLAYER _H_

#include <stdbool.h>

#include "basicStructures.h"

struct{
    unsigned int healthPoints;
    unsigned int attackPoints;
    Sprite sprite;
    bool isMoving;
    int speed;
} typedef Player;

int getPlayerDimensionX ();
int getPlayerDimensionY ();

int getPlayerPositionX();
int getPlayerPositionY();

void player_modifyPositionX(Player *player, int amount);
void player_modifyPositionY(Player *player, int amount);

void player_initialize(Player *player, int positionX, int positionY, int viewListNumber);

void player_moveLeft(Player* player);
void player_moveRight(Player* player);
void player_stopMoving(Player* player);

void player_modifyHP( int points, Player *player);

#endif //_PLAYER_H_