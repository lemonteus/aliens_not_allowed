#include "player.h"

void player_initialize(Player *player, int positionX, int positionY, int viewListNumber)
{
    player->sprite.position.x = positionX;
    player->sprite.position.y = positionY;

    player->sprite.texture = viewListNumber;
    player->healthPoints = 5; //temporary
    player->attackPoints = 1; //temporary

}

void player_modifyHP(int points, Player *player)
{
    //amount of points are ADDED to/SUBTRACTED from the current player HP value
    player->healthPoints = player->healthPoints + points;
}