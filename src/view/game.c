#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "../lib/player.h"
#include "../lib/basicStructures.h"

bool projectileHitTargetRectangle(Vector2D projectilePosition, Vector2D targetBottomRight, Vector2D targetDimensions){
    int widthStart = targetBottomRight.x;
    int widthEnd = targetBottomRight.x + targetDimensions.x;
    if( projectilePosition.x >= widthStart && projectilePosition.x <= widthEnd ){

        int heightStart = targetBottomRight.y;
        int heightEnd =targetBottomRight.y + targetDimensions.y;
        if( projectilePosition.y >= heightStart && projectilePosition.y <= heightEnd ){
            return true;
        }
    }
    return false;
}

void game_keyDown(unsigned char key, int x, int y, Player* player)
{
    switch (key)
    {
        case 'A':
        case 'a':
            player_moveLeft(player);
            break;

        case 'D':
        case 'd':
            player_moveRight(player);
            break;
            
    }
}

void game_keyUp(unsigned char key, int x, int y, Player* player)
{
    switch (key)
    {
        case 'A':
        case 'a':
        case 'D':
        case 'd':
            player_stopMoving(player);
            break;
    }
}


void game_specialKeyDown(int key, int x, int y, Player* player)
{
    switch (key)
    {
        case 102: //right
            player_moveRight(player);
            break;

        case 100: //left
            player_moveLeft(player);
            break;
    }
}

void game_specialKeyUp(int key, int x, int y, Player* player)
{
    switch (key)
    {
        case 102: //right
        case 100: //left
            player_stopMoving(player);
            break;
    }
}