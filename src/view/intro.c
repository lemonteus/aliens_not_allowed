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

Button intro_buttons[4];

int starrySkyOffset = 0;

void intro_initialize(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glEnable(GL_BLEND); // enable support for texture transparency
    glEnable(GL_DEPTH_TEST); // enable depth buffer and z coordinate
    glEnable(GL_TEXTURE_2D); // enable texture support

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    
    //avoid ragged transitions by disabling linear texel filtering for mignification and using nearest instead                                                 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    intro_selectedButton = playButton;
    intro_currentState = stateMain;

    intro_reset = false;
}

void intro_incrementOffset(){
    starrySkyOffset++;
    
    if (starrySkyOffset == 4000)
		starrySkyOffset = 10; // reset starry sky bg
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

void intro_drawScene(enum basicStructures_screen *screenDef, bool *startNewGame){
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
        glVertex3f(- 0 ,  20,  4);
    glEnd();

    // game title
    glColor3f(1.0, 1.0, 1.0);
    drawTextCentralized_GLUT(GLUT_BITMAP_TIMES_ROMAN_24, "TP1 - Galaxian", 0, 200, 6);
}

//se a pagina for alterada: intro_reset = true;

//void intro_keyboardDownFunc(int key, int x, int y);
//void intro_keyboardUpFunc(int key, int x, int y);
//void intro_specialKeyDownFunc(int key, int x, int y);
//void intro_specialKeyUpFunc(int key, int x, int y);
