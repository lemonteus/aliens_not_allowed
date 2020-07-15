#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "texture.h"

#include "../lib/keyboard.h"
#include "../lib/player.h"
#include "../lib/basicStructures.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

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

void game_drawScene(enum basicStructures_screen *screenDef, bool *startNewGame, Player *player)
{

    glCallList(getViewList(0)); //white background

    //player
    glEnable(GL_TEXTURE_2D);
    glCallList(getViewList(1));  //player spaceship

    glDisable(GL_TEXTURE_2D);
}

void game_keyboardDownFunc(unsigned char key, int x, int y, Player* player)
{
    switch (key)
    {
        case 'A':
        case 'a':
            player->state = left;
            break;

        case 'D':
        case 'd':
            player->state = right;
            break;
            
    }
}

void game_keyboardUpFunc(unsigned char key, int x, int y, Player* player)
{
    switch (key)
    {
        case 'A':
        case 'a':
            if (keyState['D']||keyState['d'])
                player->state = right;
            else
                player->state = idle;
            
            break;
        case 'D':
        case 'd':
            if (keyState['A']||keyState['a'])
                player->state = left;
            else
                player->state = idle;
            break;
    }
}


void game_specialKeyDownFunc(int key, int x, int y, Player* player)
{

    switch (key)
    {
        case (GLUT_KEY_RIGHT):
            player->state = right;
            break;

        case (GLUT_KEY_LEFT): 
            player->state = left;
            break;
    }
}

void game_specialKeyUpFunc(int key, int x, int y, Player* player)
{
   
    switch (key)
    {
        case (GLUT_KEY_RIGHT):
            if (specialKeyState[GLUT_KEY_LEFT])
                player->state = left;
            else
                player->state = idle;
            break;

        case (GLUT_KEY_LEFT):
            if (specialKeyState[GLUT_KEY_RIGHT])
                player->state = right;
            else
                player->state = idle;
            break;
    }
}