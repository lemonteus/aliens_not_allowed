#include <stdbool.h>
#include <stdio.h>

#include "player.h"

#define PLAYER_DIMENSIONS_X 50
#define PLAYER_DIMENSIONS_Y 79
#define PLAYER_SPEED 10

int getPlayerDimensionX ()
{
    return PLAYER_DIMENSIONS_X;
}

int getPlayerDimensionY ()
{
    return PLAYER_DIMENSIONS_Y;
}

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

    player->sprite.dimensions.x = PLAYER_DIMENSIONS_X;
    player->sprite.dimensions.y = PLAYER_DIMENSIONS_Y;

    player->sprite.texture = viewListNumber;
    player->healthPoints = 5; //temporary
    player->attackPoints = 1; //temporary

}

void player_moveLeft(Player* player)
{
    /*if (!player->isMoving)
        player->isMoving = true;

    while(player->isMoving)
    */
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