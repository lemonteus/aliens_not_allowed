#ifndef _GAME_H_
#define _GAME_H_

#include "../lib/player.h"
#include "../lib/basicStructures.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

bool projectileHitTargetRectangle(Vector2D projectilePosition, Vector2D targetBottomRight, Vector2D targetDimensions);

void game_drawScene(enum basicStructures_screen *screenDef, bool *startNewGame, Player *player);

void game_keyboardDownFunc(unsigned char key, int x, int y, Player *player);
void game_keyboardUpFunc(unsigned char key, int x, int y, Player *player);
void game_specialKeyDownFunc(int key, int x, int y, Player *player);
void game_specialKeyUpFunc(int key, int x, int y, Player *player);

#endif // _GAME_H_