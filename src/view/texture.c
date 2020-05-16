#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include "texture.h"

#define MAX_TEXTURES 100
#define MAX_VIEWLISTS 1000

GLuint textureIDs[MAX_TEXTURES];
GLuint viewLists[MAX_VIEWLISTS];

unsigned short vlCount = 0; //keeping track of the amount of view lists being stored
unsigned short texCount = 0; 

GLuint getTextureID(int position){
    return textureIDs[position];
}

GLuint getViewList(int position)
{
    return viewLists[position];
}

//function to create new texture ID
void newTextureID (char* filename){
    GLuint id = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    if (id == 0)
        printf("\t\a\nError while loading texture: %s", SOIL_last_result());

    textureIDs[texCount] = (GLint) id;
    texCount = texCount + 1;      
}

void generateViewList( int width, int height, int z, int ratio, const float rgb[3])
{
    //glClearColor(rgb[0], rgb[1], rgb[2], 0.0);
    glColor3f(1, 1, 1);
    viewLists[vlCount] = glGenLists(1);
    glNewList(viewLists[vlCount], GL_COMPILE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
            
            glVertex3f(-width/(2 * ratio), -height/(2 * ratio), z);
            glVertex3f(width/(2 * ratio), -height/(2 * ratio),  z);
            glVertex3f(width/(2 * ratio), height/(2 * ratio),  z);
            glVertex3f(-width/(2 * ratio), height/(2 * ratio),  z);
        glEnd();
     glEndList();

    vlCount = vlCount + 1;

}

void generateTextureViewList(GLuint id, int width, int height, int z, int ratio, const float vertices[4][2])
{
    viewLists[vlCount] = glGenLists(1);
    glNewList(viewLists[vlCount], GL_COMPILE);
        glBindTexture(GL_TEXTURE_2D, id);
        glBegin(GL_POLYGON);
            glTexCoord2fv(vertices[0]); glVertex3f(-width/(2 * ratio), -height/(2 * ratio), z);
            glTexCoord2fv(vertices[1]); glVertex3f(width/(2 * ratio), -height/(2 * ratio),  z);
            glTexCoord2fv(vertices[2]); glVertex3f(width/(2 * ratio), height/(2 * ratio),  z);
            glTexCoord2fv(vertices[3]); glVertex3f(-width/(2 * ratio), height/(2 * ratio),  z);
        glEnd();
     glEndList();

    vlCount = vlCount + 1;

}

//mapSpriteSheet(): function that receives a sprite sheet image as a parameter, as well as the amount of sprites contained in it
//and their respective dimensions, and generates a view list for them. 
//ALL SPRITES IN A SPRITE SHEET MUST HAVE THE SAME DIMENSION.
//Got inspiration from here: https://stackoverflow.com/questions/1568559/rendering-sprites-from-spritesheet-with-opengl

/* id: texture ID for the spritesheet we want to map
   spriteWidth and spriteHeight: width and height of each sprite in the sheet
   sheetWidth and sheetHeight: self explanatory
   ratio: the ratio in which you want each sprite to be displayed (bigger value, smaller texture)
   z: z-coordinate [-10, 10]
*/  

void mapSpriteSheet(GLuint id, int spriteWidth, int spriteHeight, int sheetWidth, int sheetHeight, int ratio, int z)
{
    int numPerRow = sheetWidth/spriteWidth;
    int numPerColumn = sheetHeight/spriteHeight;

    int totalSprites = numPerRow * numPerColumn;

    int frameIndex = 1; //frame index starts at 1

    //visualizing spritesheets as [0,1] maps

    float tw = (float) spriteWidth/sheetWidth;
    float th = (float) spriteHeight/sheetHeight;

    for (frameIndex; frameIndex <= totalSprites; frameIndex++)
    {
        
        float tx = (float) ( (float) ((frameIndex-1) % numPerRow) / numPerRow); 
        /* tx: get modulo of the sprite index by number per row to identify the row index,
        then divide it by numberPerRow to scale it according to the size of the spritesheet.
        e.g. index = 6 -> (6-1)%4 = 1 (row index)/4 = 0.25 -> x coordinate of sprite with index 6 starts at 0.25.
        two type castings are necessary because both operations involve int variables. */  

        float ty = (float) ( (int) ((frameIndex-1) / numPerRow) * th);
        /* ty: divide sprite index by the amount of sprites per row, type-cast it to int so it's always truncated,
        then multiply by texture height in order to scale it
        e.g. index = 6 -> (6-1)/4 = 1 (row index)/4 = 0.25 -> x coordinate of sprite with index 6 starts at 0.25. */  
        
        const float vertices[4][2] = {
            {tx, ty},
            {tx + tw, ty},
            {tx + tw, ty + th},
            {tx, ty + th}
        };

        generateTextureViewList(id, spriteWidth, spriteHeight, z, ratio, vertices);

    }
}