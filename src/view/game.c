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

void game_pressedKey(unsigned char key, int x, int y, Player* player)
{
    switch (key)
    {
        case 'A':
        case 'a':
        //printf("%d", player->sprite.position.x);
            player_modifyPositionX(player, -10);
            break;

        case 'D':
        case 'd':
            //printf("%d", player->sprite.position.x);
            player_modifyPositionX(player, +10);
            break;
    }
}