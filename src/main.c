#include <stdbool.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./lib/basicStructures.h"

#include "./view/intro.h"
#include "./view/game.h"
#include "./view/afterGame.h"

enum basicStructures_screen main_screenDef = intro;

void initialize();
void drawScene();
void reshape(int width, int height); // dimensions: 3:4
void pressedKey(unsigned char key, int x, int y); // verify current screen & call the pressedKey of the specific ".h"

int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowSize( 300, 400 );
    glutInitWindowPosition( 50, 50 );
    glutCreateWindow( "TP1: Galaxian – Pedro Vaz e Mateus Lemos" );

    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(pressedKey);

    initialize();

    glutMainLoop();

    return 0;
}

void initialize(){
    glClearColor(1, 1, 1, 1);
    main_screenDef = intro;
}

void drawScene(){
    switch (main_screenDef){
    case intro:
        intro_drawScene();
        break;
    case game:
        game_drawScene();
        break;
    case afterGame:
        afterGame_drawScene(game_finalStatus);
        break;
    default:
        break;
    }
    glutSwapBuffers();
}

void reshape(int width, int height){
    // (x, y, width, height)
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // (left, right, bottom, top, zNear, zFar)
    glOrtho(-(width/2), width/2, -(height/2), height/2, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void pressedKey(unsigned char key, int x, int y){
    switch (main_screenDef){
    case intro:
        intro_pressedKey(key, x, y);
        break;
    case game:
        game_pressedKey(key, x, y);
        break;
    case afterGame:
        afterGame_pressedKey(key, x, y);
        break;
    default:
        break;
    }
}