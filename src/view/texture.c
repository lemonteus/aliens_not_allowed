#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include "texture.h"

#define MAX_TEXTURES 100
#define MAX_VIEWLISTS 1000

GLuint textureIDs[MAX_TEXTURES];
GLuint viewLists[MAX_VIEWLISTS];

unsigned short vlCount = 0; // number of view lists being stored
unsigned short texCount = 0; 

GLuint getTextureID(int position){
    return textureIDs[position];
}

GLuint getViewList(int position){
    return viewLists[position];
}

//create a new texture and store its ID @ texureIDs' array (line 12)
void newTextureID (char* filename){
    GLuint id = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    
    if (id == 0)
        printf("\t\a\nError while loading texture: %s", SOIL_last_result());

    textureIDs[texCount] = (GLint) id;
    texCount++;      
}

void generateViewList(int width, int height, int z, int ratio, const float rgb[3]){
    //glClearColor(rgb[0], rgb[1], rgb[2], 0.0);
    glColor3f(1, 1, 1);

    //generate a contiguous empty display list
    viewLists[vlCount] = glGenLists(1); 

    //Creates a new display list, compile it and stores at viewLists[vlCount]
    glNewList(viewLists[vlCount], GL_COMPILE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_POLYGON);
            glVertex3f(-width/(2 * ratio),-height/(2 * ratio), z);
            glVertex3f(-width/(2 * ratio), height/(2 * ratio), z);
            glVertex3f( width/(2 * ratio), height/(2 * ratio), z);
            glVertex3f( width/(2 * ratio),-height/(2 * ratio), z);
        glEnd();
    glEndList();

    vlCount++;
}

void generateTextureViewList(GLuint id, int width, int height, int z, int ratio, const float vertices[4][2]){
    viewLists[vlCount] = glGenLists(1);

    //Create a new display list and compile it
    glNewList(viewLists[vlCount], GL_COMPILE);
        glBindTexture(GL_TEXTURE_2D, id);
        glBegin(GL_POLYGON);
            glTexCoord2fv(vertices[0]); 
            glVertex3f(-width/(2 * ratio), -height/(2 * ratio), z);

            glTexCoord2fv(vertices[1]); 
            glVertex3f(-width/(2 * ratio),  height/(2 * ratio), z);

            glTexCoord2fv(vertices[2]); 
            glVertex3f( width/(2 * ratio),  height/(2 * ratio), z);

            glTexCoord2fv(vertices[3]); 
            glVertex3f( width/(2 * ratio), -height/(2 * ratio), z);
        glEnd();
    glEndList();

    vlCount++;
}

/* mapSpriteSheet:
 * - receives a sprite sheet image as a parameter and the amount of sprites contained in it (w/ respective dimensions);
 * - generates a view list for them. 
 * 
 *   Obs.: ALL SPRITES IN A SPRITE SHEET MUST HAVE THE SAME DIMENSION.
 *   Inspiration: https://stackoverflow.com/questions/1568559/rendering-sprites-from-spritesheet-with-opengl
 */
void mapSpriteSheet(GLuint id, int spriteWidth, int spriteHeight, int sheetWidth, int sheetHeight, int ratio, int z){
    /* Variables meanings:
     *   id: texture's id to the sprite sheet to be mapped
     *   spriteWidth & spriteHeight: width & height for each sprite
     *   sheetWidth  & sheetHeight : width & height of the sprite sheet
     *   ratio: the ratio in which each sprite is going to be displayed. Bigger the value, smaller the texture.
     *   z: the z-coordinate [-10, 10]
     */

    int numPerRow = sheetWidth/spriteWidth;
    int numPerColumn = sheetHeight/spriteHeight;

    int totalSprites = numPerRow * numPerColumn;

    // frame index starts at 1
    int frameIndex = 1;

    //visualizing spritesheets as [0,1] maps

    float tw = (float) spriteWidth/sheetWidth;   // "tw" stands for "Texture Width"
    float th = (float) spriteHeight/sheetHeight; // "th" stands for "Texture Height"

    for(frameIndex; frameIndex <= totalSprites; frameIndex++){
        /* "tx" stands for "Texture X"
         *
         * It gets the integer rest of the division between sprite index and number per row. It identifies the row index,
         * then divide it by numberPerRow to scale it according to the size of the spritesheet.
         * 
         * e.g.: index = 6 -> (6-1) % 4 = 1 (row index)/4 = 0.25 -> x coordinate of sprite with index 6 starts at 0.25.
         * 
         * Obs.: two type castings are necessary because both operations involve int variables. 
         */  
        float tx = (float) ( (float) ((frameIndex-1) % numPerRow) / numPerRow); 
        
        /* "ty" stands for "Texture Y"
         *
         * It recieves the result of the division of the sprite intex by the amount of spriter per row
         *   ( it's casted to int to pick up the whole number and separete from decimals )
         * then multiply it by texture height (th) in order to scale it
         * 
         * e.g.: index = 6 -> (6-1)/4 = 1 (row index)/4 = 0.25 -> x coordinate of sprite with index 6 starts at 0.25. 
         */  
        float ty = (float) ( (int) ((frameIndex-1) / numPerRow) * th);
        
        const float vertices[4][2] = {
            { tx  ,  ty  },
            { tx  , ty+th},
            {tx+tw, ty+th},
            {tx+tw,  ty  }
        };

        generateTextureViewList(id, spriteWidth, spriteHeight, z, ratio, vertices);
    }
}