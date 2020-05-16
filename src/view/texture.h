#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#define MAX_TEXTURES 100
#define MAX_VIEWLISTS 1000

GLint textureIDs[MAX_TEXTURES];
GLint viewLists[MAX_VIEWLISTS];

unsigned short vlCount;
unsigned short texCount;

static const float defaultVertices[4][2] = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};
static const float rgb_white[3] = {1.0, 1.0, 1.0};

GLuint getTextureID(int position);
void newTextureID (char* filename);

GLuint getViewList(int position);

void generateViewList( int width, int height, int z, int ratio, const float rgb[3]);
void generateTextureViewList(GLuint id, int width, int height, int z, int ratio, const float vertices[4][2]);
void mapSpriteSheet(GLuint id, int spriteWidth, int spriteHeight, int sheetWidth, int sheetHeight, int ratio, int z);

#endif // _TEXTURE_H_