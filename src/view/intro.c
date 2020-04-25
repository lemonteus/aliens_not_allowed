// montar o ifndef

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h";

enum intro_selectedButton {play = 1, control = 2, highScores = 3, credits = 4};
enum intro_selectedButton intro_selectedButton = play;

enum intro_state {main = 1, control = 2, highScores = 3, credits = 4};
enum intro_state intro_currentState = main;

bool intro_reset = true;

typedef struct{
    Entity positionAndDimensions;
    char text[11];
    unsigned int numberCharacters;
} intro_button;
intro_button intro_buttons[4];

GLuint intro_loadTexture(const char* file){
    GLuint idTexture = SOIL_load_OGL_texture(file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(idTexture == 0)
        printf("\t\aError while loading texture: %s", SOIL_last_result());
    return idTexture;
}
GLuint idBackgroungTexture;

void intro_writeWordInCharArray(char* array, unsigned int arraySize, char* word, unsigned int wordSize){
    if(array != NULL && word != NULL){
        if(arraySize != 0 && wordSize != 0){
            if(arraySize >= wordSize){
                for(int i = 0; i < wordSize; i++){
                    *(array + i) = *(word + i);
                }
                return;
            }else{
                printf("\n\a\tError (intro_writeWordInCharArray): The word selected is too long!\n ");
                return;
            }
        } else{
            printf("\n\a\tError (intro_writeWordInCharArray): the array's size or the word's size is 0.\n ");
            return;
        }
    }else{
        printf("\n\a\tError (intro_writeWordInCharArray): null pointer!\n ");
        return;
    }
}

void intro_initialize(){
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    idBackgroungTexture = intro_loadTexture("../../assets/introBackground.png");

    for (int i = 0; i < 4; i++){
        intro_buttons[i].positionAndDimensions.dimensions.x = 70; //height
        intro_buttons[i].positionAndDimensions.dimensions.y = 1000; // width
        // set the bottom-left vertice of the rectangle/button
        intro_buttons[i].positionAndDimensions.position.x = -500;
        intro_buttons[i].positionAndDimensions.position.y = 280 - (i*70);
    }

    int wordSizeArray[4] = {4, 7, 11, 7}; //{"PLAY", "CONTROL", "HIGH SCORES", "CREDITS"}
    for(int i = 0; i < 0; i++){
        intro_buttons[i].numberCharacters = wordSizeArray[i];
        char* array = &intro_buttons[i].text;

        if(i == 0)
            intro_writeWordInCharArray(array, 11, "PLAY", wordSizeArray[i]);
        if(i == 1)
            intro_writeWordInCharArray(array, 11, "CONTROL", wordSizeArray[i]);
        if(i == 2)
            intro_writeWordInCharArray(array, 11, "HIGH SCORES", wordSizeArray[i]);
        if(i == 3)
            intro_writeWordInCharArray(array, 11, "CREDITS", wordSizeArray[i]);    
    }
    free(wordSizeArray);

    
    intro_selectedButton = play;
    intro_currentState = main;

    intro_reset = false;
}

void intro_drawScene(enum basicStructures_screen *screenDef, bool *startNewGame){
    if(intro_reset){
        intro_initialize();
    }
    glEnable(GL_TEXTURE_2D);

    //background image
    glBindTexture(GL_TEXTURE_2D, idBackgroungTexture);
    glBegin(GL_POLYGON);
        glTexCoord2f(0, 0);
        glVertex3f(-500, -500,  -10);

        glTexCoord2f(1, 0);
        glVertex3f( 500, -500,  -10);

        glTexCoord2f(1, 1);
        glVertex3f( 500,  500,  -10);

        glTexCoord2f(0, 1);
        glVertex3f(-500,  500,  -10);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //logo's triangle
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-400, 350,  -10);
        glVertex3f( 400, 350,  -10);
        glVertex3f(- 0 ,  20,  -10);
    GLEnd();

    //escrever tíulo
    //freetype.org ?
    //char title[14] = "TP1 - Galaxian";
    
    /*desenhar e colorir botões
    glBegin(GL_POLYGON);


    glEnd();*/
    glutSwapBuffers();
}

//se a pagina for alterada: intro_reset = true;

