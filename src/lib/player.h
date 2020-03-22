#pragma once
#include "basicStructures.h"

struct{
    unsigned int healthPoints;
    unsigned int attackPoints;
    Sprite sprite;
} typedef Player;

void player_initialize(Player *player, int positionX, int positionY, int viewListNumber);

void player_modifyHP( int points, Player *player);