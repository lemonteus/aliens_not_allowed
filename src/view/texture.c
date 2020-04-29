#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include "texture.h"

#define MAX_TEXTURES 100

GLint viewList[MAX_TEXTURES];
unsigned short vlCount = 0; //keeping track of the amount of view lists being stored

GLint getViewList(int position){
    if (viewList[position] != 0)
        return viewList[position];
    else
        return (GLint) -1;
}

//function to allocate a viewlist number for a certain texture to the viewList vector given its path
void newViewListID (char* filename){
    GLuint idTexture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    if (idTexture == 0)
        idTexture = -1;

    viewList[vlCount] = idTexture;
    vlCount = vlCount + 1;      
}

GLuint loadTexture(const char* file){
    GLuint idTexture = SOIL_load_OGL_texture(file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(idTexture == 0){
        printf("\t\aError while loading texture: %s", SOIL_last_result());
        return;
    }
    return idTexture;
}