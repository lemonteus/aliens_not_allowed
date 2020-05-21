//Compilation code: gcc intro.c -o intro.o -c -lGL -lSOIL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h"
#include "texture.h"

#include "intro.h"

enum intro_selectedButton {playButton = 1, controlButton, highScoresButton, creditsButton};
enum intro_state {stateMain = 1, stateControl, stateHighScores, stateCredits};

enum intro_selectedButton intro_selectedButton = playButton;
enum intro_state intro_currentState = stateMain;

bool intro_reset = true;

Button intro_buttons[4];
GLuint idBackgroungTexture;

int starrySkyOffset = 0;

void intro_writeWordInCharArray(char *array, unsigned int arraySize, char* word, unsigned int wordSize){
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
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glEnable(GL_BLEND ); //enabling support for texture transparency
    glEnable(GL_DEPTH_TEST); // enabling depth buffer and z coordinate
    glEnable(GL_TEXTURE_2D); //enabling texture support

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    
    //avoid ragged transitions by disabling linear texel filtering for mignification and using nearest instead                                                 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //initialize intro's buttons
    for (int i = 0; i < 4; i++){
        intro_buttons[i].positionAndDimensions.dimensions.x = 70; //height
        intro_buttons[i].positionAndDimensions.dimensions.y = 1000; // width
        // set the bottom-left vertice of the rectangle/button
        intro_buttons[i].positionAndDimensions.position.x = -500;
        intro_buttons[i].positionAndDimensions.position.y = 280 - (i*70);
    }

    //assign text to each button
    int wordSizeArray[4] = {4, 7, 11, 7}; //{"PLAY", "CONTROL", "HIGH SCORES", "CREDITS"}
    for(int i = 0; i < 4; i++){
        intro_buttons[i].numberCharacters = wordSizeArray[i];

        char* array = &(intro_buttons[i].text[0]);

        if(i == 0)
            intro_writeWordInCharArray(array, buttonTextMaxSize, "PLAY", wordSizeArray[i]);
        if(i == 1)
            intro_writeWordInCharArray(array, buttonTextMaxSize, "CONTROL", wordSizeArray[i]);
        if(i == 2)
            intro_writeWordInCharArray(array, buttonTextMaxSize, "HIGH SCORES", wordSizeArray[i]);
        if(i == 3)
            intro_writeWordInCharArray(array, buttonTextMaxSize, "CREDITS", wordSizeArray[i]);    
    }

    intro_selectedButton = playButton;
    intro_currentState = stateMain;

    intro_reset = false;
}

void intro_incrementOffset()
{
    starrySkyOffset++;
    
    if (starrySkyOffset == 4000)
	{
		starrySkyOffset = 10; //reset starry sky bg
	}

}

void intro_updateStarrySky()
{
    glBindTexture(GL_TEXTURE_2D, getTextureID(5));

	glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f( -500 - starrySkyOffset, 500,  3);
		glTexCoord2f(1, 1); glVertex3f( 8000/2 - starrySkyOffset, 500,  3);
		glTexCoord2f(1, 0); glVertex3f( 8000/2 - starrySkyOffset, -500,  3);
		glTexCoord2f(0, 0); glVertex3f( -500 - starrySkyOffset, -500,  3);
	glEnd();

}

void intro_drawScene(enum basicStructures_screen *screenDef, bool *startNewGame)
{
    //if(intro_reset){
        intro_initialize();
    //}                            

    glEnable(GL_TEXTURE_2D);

    glCallList(getViewList(7));
    intro_updateStarrySky();
    glCallList(getViewList(8));
    glCallList(getViewList(9));
    
    //glCallList(getViewList(10));
            
    glFlush();
    glDisable(GL_TEXTURE_2D);

    //logo's triangle
    /*glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex3f(-400, 350,  -10);
        glVertex3f( 400, 350,  -10);
        glVertex3f(- 0 ,  20,  -10);
    glEnd();
    */

    //escrever tíulo
    //freetype.org ?
    //char title[14] = "TP1 - Galaxian";
    
    //desenhar e colorir botões
    /*glBegin(GL_POLYGON);


    glEnd();*/
}

//se a pagina for alterada: intro_reset = true;

//void intro_keyboardDownFunc(int key, int x, int y);
//void intro_keyboardUpFunc(int key, int x, int y);
//void intro_specialKeyDownFunc(int key, int x, int y);
//void intro_specialKeyUpFunc(int key, int x, int y);
