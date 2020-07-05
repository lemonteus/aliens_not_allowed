#include <stdbool.h>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "../lib/basicStructures.h"
#include "../lib/fonts.h"
#include "texture.h"

#include "afterGame.h"

enum afterGame_selectedButton {retry = 1, menu, quit};
enum afterGame_selectedButton afterGame_selectedButton = menu;

bool afterGame_reset = true;
int afterGame_starrySkyOffset = 0;

Button afterGame_buttons[3];

void afterGame_internal_createButtons(){
    typedef struct{
        char content[buttonTextMaxSize]; // buttonTextMaxSize defined at basicStructures.h
    } buttonText;

    buttonText buttonTextArray[3];
    strcpy(buttonTextArray[0].content, "REJOGAR");
    strcpy(buttonTextArray[1].content, "MENU");
    strcpy(buttonTextArray[2].content, "SAIR");

    int buttonDimension = 200;

    for(int i = 0; i < 3; i++){
        afterGame_buttons[i].dimensions.x = buttonDimension; //width
        afterGame_buttons[i].dimensions.y = buttonDimension; //height

        afterGame_buttons[i].position.x = -300 + (buttonDimension * i);
        afterGame_buttons[i].position.y = 100;
        afterGame_buttons[i].position.z = 5;

        strcpy(afterGame_buttons[i].text, buttonTextArray[i].content);
    }

    //ASSINALAR ICONES AOS BOTÕES
}

void afterGame_internal_drawButtons(){
    int y = afterGame_buttons[0].position.y;
    int z = afterGame_buttons[0].position.z;

    int width  = afterGame_buttons[0].dimensions.x;
    int height = afterGame_buttons[0].dimensions.y;

    for(int i = 0; i < 3; i++){
        // Check which button is selected and change its color
        if(i == afterGame_selectedButton - 1)
            glColor4f(0.867, 0.627, 0.867, 1.0);
        else
            glColor4f(0.494, 0.424, 0.525, 0.5);

        int x = afterGame_buttons[i].position.x;

        glBegin(GL_POLYGON);
            glVertex3f(x,         y,          z); // top-left
            glVertex3f(x + width, y,          z); // top-right
            glVertex3f(x + width, y - height, z); // bottom-right
            glVertex3f(x        , y - height, z); // bottom-left
        glEnd();
    }

}

void afterGame_internal_initialize(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    afterGame_internal_createButtons();

    afterGame_selectedButton = menu;
    afterGame_reset = false;
}

void afterGame_incrementOffSet(){
    afterGame_starrySkyOffset++;
    if (afterGame_starrySkyOffset == 4000)
		afterGame_starrySkyOffset = 10; // reset starry sky background
}

void afterGame_updateStarrySky(){
    glBindTexture(GL_TEXTURE_2D, getTextureID(5));

	glBegin(GL_POLYGON);
		glTexCoord2f(0, 1);
        glVertex3f(  -500  - afterGame_starrySkyOffset,  500, 3);

		glTexCoord2f(1, 1);
        glVertex3f( 8000/2 - afterGame_starrySkyOffset,  500, 3);

		glTexCoord2f(1, 0);
        glVertex3f( 8000/2 - afterGame_starrySkyOffset, -500, 3);

		glTexCoord2f(0, 0);
        glVertex3f(  -500  - afterGame_starrySkyOffset, -500, 3);
	glEnd();
}

void afterGame_drawScene(bool playerWonTheGame){
    if(afterGame_reset)
        afterGame_internal_initialize();

    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);

    glCallList(getViewList(7));
    afterGame_updateStarrySky();
    glCallList(getViewList(8));
    glCallList(getViewList(9));

    glDisable(GL_TEXTURE_2D);  

    glColor3f(0.0, 0.0, 0.0);
    if (playerWonTheGame)
        drawTextCentralized_GLUT(GLUT_BITMAP_TIMES_ROMAN_24, "VITÓRIA!", 0, 140, 5);
    else
        drawTextCentralized_GLUT(GLUT_BITMAP_TIMES_ROMAN_24, "DERROTA!", 0, 140, 5);
    
    afterGame_internal_drawButtons();

    glColor3f(1.0, 1.0, 1.0);
    glFlush();
}

void afterGame_specialKeyDownFunc(int key, int x, int y){
    switch(key){
        case(GLUT_KEY_RIGHT):
            if(afterGame_selectedButton < 3)
                afterGame_selectedButton++;
        break;
        case(GLUT_KEY_LEFT):
            if(afterGame_selectedButton > 1)
                afterGame_selectedButton--;
        break;
    }

}

void afterGame_mousePassiveFunc(int x, int y, bool mouseInBounds){
    if(mouseInBounds){
        int buttonDimensions = afterGame_buttons[0].dimensions.x; // all widths and heights are the same

        for(int i = 0; i < 3; i++){
            int buttonY = afterGame_buttons[i].position.y;
            int buttonX = afterGame_buttons[i].position.x;

            if(x >= buttonX && x <= (buttonX + buttonDimensions)){
                if(y <= buttonY && y >= (buttonY - buttonDimensions))
                    afterGame_selectedButton = i+1;
            }
        }
    }
}

void afterGame_mouseActiveFunc(int button, int state, int x, int y, bool mouseInBounds, enum basicStructures_screen *screenDef);

void afterGame_keyboardDownFunc(int key, int x, int y, enum basicStructures_screen *screenDef){
    if(key == 13 || key == 32){ // Enter || Spacebar
        switch(afterGame_selectedButton){
            case(retry):
                *screenDef = game;
                afterGame_reset = true;
            break;
            case(menu):
                *screenDef = intro;
                afterGame_reset = true;
            break;
            case(quit):
                exit(0);
            break;
        }
    }
}