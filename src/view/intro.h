#ifndef _INTRO_H_
#define _INTRO_H_

#include <string.h>
#include <stdbool.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h"
#include "texture.h"

void intro_incrementOffset();
void intro_drawScene();
void intro_specialKeyDownFunc(int key, int x, int y);
void intro_mousePassiveFunc(int x, int y, bool mouseInBounds);
void intro_mouseActiveFunc(int button, int state, int x, int y, bool mouseInBounds, enum basicStructures_screen *screenDef);
void intro_keyboardDownFunc(int key, int x, int y, enum basicStructures_screen *screenDef);

#endif //_INTRO_H_