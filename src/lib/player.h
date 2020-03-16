#pragma once

struct{
    unsigned int healthPoints;
    unsigned int attackPoints;
    Vector2D position;
} typedef Player;

void player_modifyHP( int points, Player *player);