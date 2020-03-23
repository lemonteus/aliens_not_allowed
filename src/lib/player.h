#pragma once
#include "basicStructures.h"

struct{
    unsigned int healthPoints;
    unsigned int attackPoints;
    Sprite sprite;
} typedef Player;

int getPlayerDimensionX ();
int getPlayerDimensionY ();

int getPlayerPositionX();
int getPlayerPositionY();

void player_modifyPositionX(Player *player, int amount);
void player_modifyPositionY(Player *player, int amount);

void player_initialize(Player *player, int positionX, int positionY, int viewListNumber);

void player_modifyHP( int points, Player *player);