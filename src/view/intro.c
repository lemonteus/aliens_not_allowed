// montar o ifndef

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdbool.h>

#include "../lib/basicStructures.h";

enum intro_selectedButton {play = 1, control = 2, highScores = 3, credits = 4};
enum intro_selectedButton intro_selectedButton = play;

enum intro_state {main = 1, control = 2, highScores = 3, credits = 4};
enum intro_state intro_currentState = main;

bool intro_reset = true;

typedef struct{
    Entity positionAndDimensions;
    char text[10];
} intro_button;
intro_button intro_buttons[4];

GLuint intro_loadTexture(const char* file){
    GLuint idTexture = SOIL_load_OGL_texture(file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(idTexture == 0)
        printf("\t\aError while loading texture: %s", SOIL_last_result());
    return idTexture;
}
GLuint idBackgroungTexture;


void intro_initialize(){
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    idBackgroungTexture = intro_loadTexture("../../assets/introBackground.png");

    for (int i = 0; i < 4; i++){
        intro_buttons[i].positionAndDimensions.dimensions.x = 70;
        intro_buttons[i].positionAndDimensions.dimensions.y = 1000;
        intro_buttons[i].positionAndDimensions.position.x = -500;
        intro_buttons[i].positionAndDimensions.position.y = 280 - (i*70);
    }

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

    //escrever "TP1 - GALAXIAN"

    //desenhar botões e aplicar transparência
    //colorir botão selecionado
    glutSwapBuffers();
}

//se a pagina for alterada: intro_reset = true;

