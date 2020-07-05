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

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
            player_moveLeft(player);
            break;

        case 'D':
        case 'd':
            player_moveRight(player);
            break;
            
    }
}

void game_keyboardUpFunc(unsigned char key, int x, int y, Player* player)
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


void game_specialKeyDownFunc(int key, int x, int y, Player* player)
{
    switch (key)
    {
        case (GLUT_KEY_RIGHT):
            player->state = right;
            //printf("%d", getPlayerPositionX());
            break;

        case (GLUT_KEY_LEFT): 
            player->state = left;
            break;
    }
    //glutPostRedisplay();
}

void game_specialKeyUpFunc(int key, int x, int y, Player* player)
{
    switch (key)
    {
        case (GLUT_KEY_RIGHT):
        case (GLUT_KEY_LEFT): 
            player->state = idle;
            break;
    }
}