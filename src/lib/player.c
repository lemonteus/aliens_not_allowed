#include <stdbool.h>
#include <stdio.h>

#include "player.h"

#define PLAYER_INITIAL_Y_POS 0
#define PLAYER_INITIAL_X_POS 0

#define PLAYER_DIMENSION_X 50
#define PLAYER_DIMENSION_Y 50

#define PLAYER_SPEED 5

int getPlayerPositionX(Player *player)
{
    return player->entity.position.x;
}

int getPlayerPositionY(Player *player)
{
    return player->entity.position.y;
}

int getPlayerDimensionX(Player *player)
{
    return PLAYER_DIMENSION_X;
}

int getPlayerDimensionY(Player *player)
{
    return PLAYER_DIMENSION_Y;
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

int getPlayerState(Player *player)
{
    return player->state;
}

void player_modifyPositionX(Player *player, int amount)
{
    player->entity.position.x += amount;
}

void player_modifyPositionY(Player *player, int amount)
{
    player->entity.position.y += amount;
}

void player_initialize(Player *player, int positionX, int positionY, unsigned int id)
{
    player->entity.position.x = positionX;
    player->entity.position.y = positionY;

    player->state = idle;
    player->speed = PLAYER_SPEED;

    player->textureID = id;

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
    player->state = idle;
}


void player_modifyHP(int points, Player *player)
{
    //amount of points are ADDED to/SUBTRACTED from the current player HP value
    player->healthPoints = player->healthPoints + points;
}