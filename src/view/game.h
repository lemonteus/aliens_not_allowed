#ifndef _GAME_H_
#define _GAME_H_

#include "../lib/player.h"
#include "../lib/basicStructures.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

bool projectileHitTargetRectangle(Vector2D projectilePosition, Vector2D targetBottomRight, Vector2D targetDimensions);

void game_keyDown(unsigned char key, int x, int y, Player *player);
void game_keyUp(unsigned char key, int x, int y, Player *player);
void game_specialKeyDown(int key, int x, int y, Player *player);
void game_specialKeyUp(int key, int x, int y, Player *player);

#endif // _GAME_H_