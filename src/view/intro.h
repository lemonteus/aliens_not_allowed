// montar o ifndef

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h"

enum intro_selectedButton {play = 1, control = 2, highScores = 3, credits = 4};
enum intro_selectedButton intro_selectedButton = play;

enum intro_state {main = 1, control = 2, highScores = 3, credits = 4};
enum intro_state intro_currentState = main;

bool intro_reset = true;

Button intro_buttons[4];

GLuint intro_loadTexture(const char* file);
GLuint idBackgroungTexture;

void intro_writeWordInCharArray(char* array, unsigned int arraySize, char* word, unsigned int wordSize);

void intro_initialize();

void intro_drawScene(enum basicStructures_screen *screenDef, bool *startNewGame);

//void intro_keyDown(unsigned char key, int x, int y);

//void intro_specialKeyDown(unsigned char key, int x, int y);





//se a pagina for alterada: intro_reset = true;