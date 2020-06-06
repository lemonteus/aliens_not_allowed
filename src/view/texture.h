#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#define MAX_TEXTURES 100
#define MAX_VIEWLISTS 1000

GLuint textureIDs[MAX_TEXTURES];
GLuint viewLists[MAX_VIEWLISTS];

unsigned short vlCount; // number of view lists being stored
unsigned short texCount;

static const float defaultVertices[4][2] = {{0.0, 0.0}, {0.0, 1.0}, {1.0, 1.0}, {1.0, 0.0}};
static const float rgb_white[3] = {1.0, 1.0, 1.0};

//create a new texture and store its ID @ texureIDs' array (line 12)
GLuint getTextureID(int position);

void newTextureID (char* filename);

GLuint getViewList(int position);

void generateViewList( int width, int height, int z, int ratio, const float rgb[3]);

void generateTextureViewList(GLuint id, int width, int height, int z, int ratio, const float vertices[4][2]);

/* mapSpriteSheet:
 * - receives a sprite sheet image as a parameter and the amount of sprites contained in it (w/ respective dimensions);
 * - generates a view list for them. 
 * 
 *   Obs.: ALL SPRITES IN A SPRITE SHEET MUST HAVE THE SAME DIMENSION.
 *   Inspiration: https://stackoverflow.com/questions/1568559/rendering-sprites-from-spritesheet-with-opengl
 */
void mapSpriteSheet(GLuint id, int spriteWidth, int spriteHeight, int sheetWidth, int sheetHeight, int ratio, int z);

#endif // _TEXTURE_H_