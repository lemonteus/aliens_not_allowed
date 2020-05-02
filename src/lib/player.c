#include <stdbool.h>
#include <stdio.h>

#include "player.h"

#define PLAYER_INITIAL_Y_POS 0
#define PLAYER_INITIAL_X_POS 0
#define PLAYER_SPEED 10

int getPlayerPositionX(Player *player)
{
    return player->entity.position.x;
}

int getPlayerPositionY(Player *player)
{
    return player->entity.position.y;
}

int getPlayerInitialXPos()
{
    return PLAYER_INITIAL_X_POS;
}

int getPlayerInitialYPos()
{
    return PLAYER_INITIAL_Y_POS;
}

int getPlayerSpeed()
{
    return PLAYER_SPEED;
}

void player_modifyPositionX(Player *player, int amount)
{
    player->entity.position.x += amount;
}

void player_modifyPositionY(Player *player, int amount)
{
    player->entity.position.y += amount;
}

void player_initialize(Player *player, int positionX, int positionY, int viewListNumber)
{
    player->entity.position.x = positionX;
    player->entity.position.y = positionY;

    player->isMoving = false;
    player->speed = PLAYER_SPEED;

    player->textureID = viewListNumber;

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