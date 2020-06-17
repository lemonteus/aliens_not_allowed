#ifndef _INTRO_H_
#define _INTRO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h"
#include "texture.h"

//void intro_initialize();
//void intro_updateStarrySky();
void intro_incrementOffset();
void intro_drawScene(enum basicStructures_screen *screenDef, bool *startNewGame);

//void intro_keyboardDownFunc(int key, int x, int y);
//void intro_keyboardUpFunc(int key, int x, int y);
//void intro_specialKeyDownFunc(int key, int x, int y);
//void intro_specialKeyUpFunc(int key, int x, int y);

#endif //_INTRO_H_