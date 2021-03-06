#include <string.h>
#include <math.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "fonts.h"
   
void drawText_GLUT(void * font , char *text, float x, float y, float z) {
    glRasterPos3f(x, y, z);
    for (int i = 0; i < strlen(text); i++)
        glutBitmapCharacter(font, text[i]);
}

void drawTextCentralized_GLUT(void * font, char *text, float x, float y, float z){
    int textWidth = glutBitmapLength(font, text);

    glRasterPos3f( (x - (textWidth/2)), y, z);
    for (int i = 0; i < strlen(text); i++)
        glutBitmapCharacter(font, text[i]);
}

void drawTextAlignRight_GLUT(void * font , char *text, float x, float y, float z){
    int textWidth = glutBitmapLength(font, text);

    glRasterPos3f( (x - textWidth), y, z);
    for (int i = 0; i < strlen(text); i++)
        glutBitmapCharacter(font, text[i]);
}