#ifndef _AFTERGAME_H_
#define _AFTERGAME_H_

#include <stdbool.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h"
#include "texture.h"

void afterGame_incrementOffSet();
void afterGame_updateStarrySky();
void afterGame_drawScene(bool playerWonTheGame);
void afterGame_specialKeyDownFunc(int key, int x, int y);
void afterGame_mousePassiveFunc(int x, int y, bool mouseInBounds);
void afterGame_mouseActiveFunc(int button, int state, int x, int y, bool mouseInBounds, enum basicStructures_screen *screenDef);
void afterGame_keyboardDownFunc(int key, int x, int y, enum basicStructures_screen *screenDef);

#endif // _AFTERGAME_H_