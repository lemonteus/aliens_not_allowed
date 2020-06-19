#include <string.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h"
#include "../lib/fonts.h"
#include "texture.h"

#include "intro.h"

enum intro_state {stateMain = 1, stateControl, stateHighScores, stateCredits};
enum intro_selectedButton {playButton = 1, controlButton, highScoresButton, creditsButton};

enum intro_state intro_currentState = stateMain;
enum intro_selectedButton intro_selectedButton = playButton;

bool intro_reset = true;
int starrySkyOffset = 0;

Button intro_buttons[4];

void intro_createButtons(){
    typedef struct{
        char content[buttonTextMaxSize]; // buttonTextMaxSize defined at basicStructures.h
        unsigned int numberOfCharacter;
    } buttonText;

    buttonText buttonTextArray[4];

    strcpy(buttonTextArray[0].content, "PLAY");
    buttonTextArray[0].numberOfCharacter = strlen(buttonTextArray[0].content);

    strcpy(buttonTextArray[1].content, "CONTROL");
    buttonTextArray[1].numberOfCharacter = strlen(buttonTextArray[1].content);

    strcpy(buttonTextArray[2].content, "HIGH SCORES");
    buttonTextArray[2].numberOfCharacter = strlen(buttonTextArray[2].content);

    strcpy(buttonTextArray[3].content, "CREDITS");
    buttonTextArray[3].numberOfCharacter = strlen(buttonTextArray[3].content);

    for(int i = 0; i < 4; i++){
        strcpy(intro_buttons[i].text, buttonTextArray[i].content);
        intro_buttons[i].numberCharacters = buttonTextArray[i].numberOfCharacter;

        int height = 80;

        intro_buttons[i].dimensions.x = 1000;   // width
        intro_buttons[i].dimensions.y = height;
        
        //set the top-left vertice of the rectangle/button
        intro_buttons[i].position.x = -500;
        intro_buttons[i].position.y = -50 - (i * height);
    }
}

void intro_drawButton(unsigned int buttonIndex){
    if(intro_selectedButton - 1 == (int)buttonIndex)
        glColor4f(0.867, 0.627, 0.867, 1.0); //rgb(221, 160, 221)
    else
        glColor4f(0.494, 0.424, 0.525, 0.5); //rgb(126, 108, 134)

    int x = intro_buttons[(int)buttonIndex].position.x;
    int y = intro_buttons[(int)buttonIndex].position.y;
    int z = 7;

    int width  = intro_buttons[(int)buttonIndex].dimensions.x;
    int height = intro_buttons[(int)buttonIndex].dimensions.y;
    
    glBegin(GL_POLYGON);
        glVertex3f( x, y,          z); // top-left
        glVertex3f(-x, y,          z); // top-right
        glVertex3f(-x, y - height, z); // bottom-right
        glVertex3f( x, y - height, z); // bottom-left
    glEnd();

    y -= (height/2) + ( glutBitmapHeight(GLUT_BITMAP_HELVETICA_18) / 2 );
    z += 1;

    // write text above buttons
    glColor4f(0.0, 0.0, 0.0, 1.0);
    drawTextCentralized_GLUT(GLUT_BITMAP_HELVETICA_18, intro_buttons[(int)buttonIndex].text, 0, y, z);
}

void intro_initialize(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glEnable(GL_BLEND); // enable support for texture transparency
    glEnable(GL_DEPTH_TEST); // enable depth buffer and z-coordinate
    glEnable(GL_TEXTURE_2D); // enable texture support

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    
    // avoid ragged transitions by disabling linear texel filtering for mignification and using nearest instead                                                 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    intro_createButtons();

    intro_selectedButton = playButton;
    intro_currentState = stateMain;

    intro_reset = false;
}

void intro_incrementOffset(){
    starrySkyOffset++;
    
    if (starrySkyOffset == 4000)
		starrySkyOffset = 10; // reset starry sky background
}

void intro_updateStarrySky(){
    glBindTexture(GL_TEXTURE_2D, getTextureID(5));

	glBegin(GL_POLYGON);
		glTexCoord2f(0, 1);
        glVertex3f(  -500  - starrySkyOffset,  500, 3);

		glTexCoord2f(1, 1);
        glVertex3f( 8000/2 - starrySkyOffset,  500, 3);

		glTexCoord2f(1, 0);
        glVertex3f( 8000/2 - starrySkyOffset, -500, 3);

		glTexCoord2f(0, 0);
        glVertex3f(  -500  - starrySkyOffset, -500, 3);
	glEnd();
}

void intro_drawScene(){
    if(intro_reset)
        intro_initialize();

    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);

    glCallList(getViewList(7));
    intro_updateStarrySky();
    glCallList(getViewList(8));
    glCallList(getViewList(9));

    //glCallList(getViewList(10));
    glDisable(GL_TEXTURE_2D);  
    glFlush();
    
    // logo's triangle
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex3f(-400, 350,  4);
        glVertex3f( 400, 350,  4);
        glVertex3f(  0 ,  20,  4);
    glEnd();

    // game title on screen
    glColor3f(1.0, 1.0, 1.0);
    drawTextCentralized_GLUT(GLUT_BITMAP_TIMES_ROMAN_24, "TP1 Galaxian", 0, 200, 6);

    // draw buttons
    for(int buttonIndex = 0; buttonIndex < 4; buttonIndex++){
        intro_drawButton(buttonIndex);
    }
    
    glColor3f(1.0, 1.0, 1.0);
}

void intro_specialKeyDownFunc(int key, int x, int y){
    switch(key){
        case(GLUT_KEY_UP):
        case(GLUT_KEY_PAGE_UP):
            if(intro_selectedButton > 1)
                intro_selectedButton--;
            break;
        case(GLUT_KEY_DOWN):
        case(GLUT_KEY_PAGE_DOWN):
            if(intro_selectedButton < 4)
                intro_selectedButton++;
            break;
    }
}

void intro_mousePassiveFunc(int x, int y, bool mouseInBounds){

    if(mouseInBounds){
        int buttonHeight = intro_buttons[0].dimensions.y; // all heights have the same value

        for(int buttonCounter = 0; buttonCounter < 4;  buttonCounter++){
            int buttonPositionY = intro_buttons[buttonCounter].position.y;
            if (y <= buttonPositionY && y >= buttonPositionY - buttonHeight)
                intro_selectedButton = buttonCounter +1;
        }
    }

}


//se a pagina for alterada: intro_reset = true;

//void intro_keyboardDownFunc(int key, int x, int y);
//void intro_keyboardUpFunc(int key, int x, int y);

