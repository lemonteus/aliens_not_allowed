#ifndef _FONTS_C_
#define _FONTS_C_

#include <string.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

void drawText_GLUT(void * font , char *text, float x, float y, float z);
void drawTextCentralized_GLUT(void * font, char *text, float x, float y, float z);
void drawTextAlignRight_GLUT(void * font , char *text, float x, float y, float z);

#endif //_FONTS_C_