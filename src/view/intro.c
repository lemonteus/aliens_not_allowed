#include <stdio.h>
#include <string.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h"
#include "../lib/fonts.h"
#include "texture.h"

#include "intro.h"

enum intro_state {stateMain = 1, stateControls, stateHighScores, stateCredits};
enum intro_selectedButton {playButton = 1, controlButton, highScoresButton, creditsButton};

enum intro_state intro_currentState = stateMain;
enum intro_selectedButton intro_selectedButton = playButton;

bool intro_reset = true;
int starrySkyOffset = 0;

Button intro_buttons[4];
Button intro_overlayReturnButton;

void intro_createButtons(){
    typedef struct{
        char content[buttonTextMaxSize]; // buttonTextMaxSize defined at basicStructures.h
    } buttonText;

    buttonText buttonTextArray[4];
    strcpy(buttonTextArray[0].content, "PLAY");
    strcpy(buttonTextArray[1].content, "CONTROL");
    strcpy(buttonTextArray[2].content, "HIGH SCORES");
    strcpy(buttonTextArray[3].content, "CREDITS");

    for(int i = 0; i < 4; i++){
        int height = 80;
        strcpy(intro_buttons[i].text, buttonTextArray[i].content);

        intro_buttons[i].dimensions.x = 1000;   // width
        intro_buttons[i].dimensions.y = height;
        
        //set the top-left vertice of the rectangle/button
        intro_buttons[i].position.x = -500;
        intro_buttons[i].position.y = -50 - (i * height);
        intro_buttons[i].position.z =  7;
    }

    //define intro_overlayReturnButton
    strcpy(intro_overlayReturnButton.text, "Return");

    intro_overlayReturnButton.position.x = -100;
    intro_overlayReturnButton.position.y = -400;
    intro_overlayReturnButton.position.z = 9;

    intro_overlayReturnButton.dimensions.x = 200;
    intro_overlayReturnButton.dimensions.y = 50;
}

void intro_drawButton(Button button, float color[4], void * font){
    glColor4f(color[0], color[1], color[2], color[3]);

    int x = button.position.x;
    int y = button.position.y;
    int z = button.position.z;

    int width  = button.dimensions.x;
    int height = button.dimensions.y;

    glBegin(GL_POLYGON);
        glVertex3f( x, y,          z); // top-left
        glVertex3f(-x, y,          z); // top-right
        glVertex3f(-x, y - height, z); // bottom-right
        glVertex3f( x, y - height, z); // bottom-left
    glEnd();

    x += width/2;
    y -= (height/2) + ( glutBitmapHeight(font) / 2 );
    z++;

    // write text above buttons' z-coordinate
    glColor4f(0.0, 0.0, 0.0, 1.0);
    drawTextCentralized_GLUT(font, button.text, x, y, z);
}

void intro_drawStateMainButtons(){
    for(int buttonIndex = 0; buttonIndex < 4; buttonIndex++){
        float color[4];
        if(intro_selectedButton - 1 == (int)buttonIndex){ //rgb(221, 160, 221)
            color[0] = 0.867;
            color[1] = 0.627;
            color[2] = 0.867;
            color[3] = 1.0;
        } else{ //rgb(126, 108, 134)
            color[0] = 0.494;
            color[1] = 0.424;
            color[2] = 0.525;
            color[3] = 0.5;
        }
        intro_drawButton(intro_buttons[buttonIndex], color, GLUT_BITMAP_HELVETICA_18);
    }
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

void intro_drawOverlays(){
    if(intro_currentState != stateMain){
        glColor4f(0.0, 0.0, 0.0, 0.8);
        glBegin(GL_POLYGON);
            glVertex3f( -500,  500, 8);
            glVertex3f(  500,  500, 8);
            glVertex3f(  500, -500, 8);
            glVertex3f( -500, -500, 8);
        glEnd();

        int x = -400;
        int y =  400;
        int z =  9;

        int lineSpacing = 40;

        glColor4f(1.0, 1.0, 1.0, 1.0);
        switch(intro_currentState){
            case(stateControls):
                drawText_GLUT(GLUT_BITMAP_HELVETICA_18, "CONTROLS", x, y, z);

                x += 10;
                y -= 50;
                drawText_GLUT(GLUT_BITMAP_HELVETICA_12, "Directional arrors :", x, y, z);
                drawTextAlignRight_GLUT(GLUT_BITMAP_HELVETICA_12, "move horizontally the spaceship", -x, y, z);

                y-= lineSpacing;
                drawText_GLUT(GLUT_BITMAP_HELVETICA_12, "P button :", x, y, z);
                drawTextAlignRight_GLUT(GLUT_BITMAP_HELVETICA_12, "pause/resume game", -x, y, z);

                y-= lineSpacing;
                drawText_GLUT(GLUT_BITMAP_HELVETICA_12, "R button :", x, y, z);
                drawTextAlignRight_GLUT(GLUT_BITMAP_HELVETICA_12, "restart game", -x, y, z);

                y-= lineSpacing;
                drawText_GLUT(GLUT_BITMAP_HELVETICA_12, "ESC :", x, y, z);
                drawTextAlignRight_GLUT(GLUT_BITMAP_HELVETICA_12, "quit game", -x, y, z);

            break;
            case(stateHighScores):
                drawText_GLUT(GLUT_BITMAP_HELVETICA_18, "HIGH SCORES", x, y, z);

                x += 10;
                y -= 50;

                //FILE *highScoresFilePtr = fopen("../../highScores.csv", 'r');
                FILE *highScoresFilePtr = NULL;
                if(highScoresFilePtr == NULL){
                    //fclose(highScoresFilePtr);
                    drawText_GLUT(GLUT_BITMAP_HELVETICA_12, "There is no data avaliable.", x, y, z);
                } else{
                    // ler csv (<nome>,<pontos>\n)
                    // imprimir placares
                }

            break;
            case(stateCredits):
               drawText_GLUT(GLUT_BITMAP_HELVETICA_18, "CREDITS", x, y, z);

                x += 10;
                y -= 50;
                drawText_GLUT(GLUT_BITMAP_HELVETICA_12, "Developers :", x, y, z);
                drawTextAlignRight_GLUT(GLUT_BITMAP_HELVETICA_12, "Pedro Vaz and Mateus Lemos", -x, y, z);

                y-= lineSpacing;
                drawText_GLUT(GLUT_BITMAP_HELVETICA_12, "Mentor :", x, y, z);
                drawTextAlignRight_GLUT(GLUT_BITMAP_HELVETICA_12, "Flavio Coutinho", -x, y, z);

                y-= lineSpacing;
                drawText_GLUT(GLUT_BITMAP_HELVETICA_12, "Source code :", x, y, z);
                drawTextAlignRight_GLUT(GLUT_BITMAP_HELVETICA_12, "github.com/HoloVaz/TP1-Galaxian", -x, y, z);

            break;
        }

        float overlayButtonColor[4] = {0.867, 0.627, 0.867, 1.0};
        intro_drawButton(intro_overlayReturnButton, overlayButtonColor, GLUT_BITMAP_HELVETICA_18);
    }
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
    drawTextCentralized_GLUT(GLUT_BITMAP_TIMES_ROMAN_24, "TP1 - GALAXIAN", 0, 200, 6);

    intro_drawStateMainButtons();
    intro_drawOverlays();
    
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
        if(intro_currentState == stateMain){
            int buttonHeight = intro_buttons[0].dimensions.y; // all heights have the same value

            for(int buttonCounter = 0; buttonCounter < 4;  buttonCounter++){
                int buttonPositionY = intro_buttons[buttonCounter].position.y;
                if (y <= buttonPositionY && y >= buttonPositionY - buttonHeight)
                    intro_selectedButton = buttonCounter + 1;
            }
        }
        // outros current states pra implementar
    }

}

void intro_mouseActiveFunc(int button, int state, int x, int y, bool mouseInBounds, enum basicStructures_screen *screenDef){
    if(mouseInBounds){
        if(intro_currentState == stateMain){
            int buttonHeight = intro_buttons[0].dimensions.y; // all heights have the same value

            for(int buttonCounter = 0; buttonCounter < 4;  buttonCounter++){
                int buttonPositionY = intro_buttons[buttonCounter].position.y;
                if (y <= buttonPositionY && y >= buttonPositionY - buttonHeight)
                    intro_selectedButton = buttonCounter + 1;

                    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
                        switch(intro_selectedButton){
                            case(playButton):
                                *screenDef = game;
                            break;
                            case(controlButton):
                                intro_currentState = stateControls;
                            break;
                            case(highScoresButton):
                                intro_currentState = stateHighScores;
                            break;
                            case(creditsButton):
                                intro_currentState = stateCredits;
                            break;
                        }
                    }
            }
        } else{ //check if the return button is clicked
            Vector2D position, dimensions;
            position.x = intro_overlayReturnButton.position.x;
            position.y = intro_overlayReturnButton.position.y;

            dimensions.x = intro_overlayReturnButton.dimensions.x;
            dimensions.y = intro_overlayReturnButton.dimensions.y;

            if(y <= position.y && y >= position.y - dimensions.y &&
               x >= position.x && x <= position.x + dimensions.x ){
                   intro_currentState = stateMain;
               }
            

        }
    }
}


//se a pagina for alterada: intro_reset = true;

//void intro_keyboardDownFunc(int key, int x, int y);
//void intro_keyboardUpFunc(int key, int x, int y);
