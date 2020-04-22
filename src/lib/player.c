#include <stdbool.h>
#include <stdio.h>

#include "player.h"

#define PLAYER_SPEED 10

int getPlayerPositionX(Player *player)
{
    return player->sprite.position.x;
}

int getPlayerPositionY(Player *player)
{
    return player->sprite.position.y;
}

void player_modifyPositionX(Player *player, int amount)
{
    player->sprite.position.x += amount;
}

void player_modifyPositionY(Player *player, int amount)
{
    player->sprite.position.y += amount;
}

void player_initialize(Player *player, int positionX, int positionY, int viewListNumber)
{
    player->sprite.position.x = positionX;
    player->sprite.position.y = positionY;

    player->isMoving = false;
    player->speed = PLAYER_SPEED;

    player->sprite.texture = viewListNumber;

}

void player_moveLeft(Player* player)
{
    player_modifyPositionX(player, -player->speed);
}

void player_moveRight(Player* player)
{
    player_modifyPositionX(player, player->speed);
}

void player_stopMoving (Player* player)
{
    player->isMoving = false;
}


void player_modifyHP(int points, Player *player)
{
    //amount of points are ADDED to/SUBTRACTED from the current player HP value
    player->healthPoints = player->healthPoints + points;
}