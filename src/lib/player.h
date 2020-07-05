#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdbool.h>

#include "basicStructures.h"

enum playerState {idle, right, left, shooting};

struct{
    unsigned int healthPoints;
    unsigned int attackPoints;
    Entity entity;
    enum playerState state;
    int speed;
    unsigned int textureID;
} typedef Player;

int getPlayerDimensionX();
int getPlayerDimensionY();

int getPlayerPositionX();
int getPlayerPositionY();

int getPlayerInitialXPos();
int getPlayerInitialYPos();

int getPlayerSpeed();

int getPlayerState();

void player_modifyPositionX(Player *player, int amount);
void player_modifyPositionY(Player *player, int amount);

void player_initialize(Player *player, int positionX, int positionY, unsigned int id);

void player_moveLeft(Player* player);
void player_moveRight(Player* player);
void player_stopMoving(Player* player);

void player_modifyHP( int points, Player *player);

#endif //_PLAYER_H_