#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#define MAX_TEXTURES 100

GLint viewList[MAX_TEXTURES];
unsigned short vlCount;

GLint getViewList(int position);
void newViewListID (char* filename);
GLuint loadTexture(const char* file);