#include <stdbool.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <SOIL/SOIL.h>

#include "./lib/basicStructures.h"
/*
// Scenes
#include "./view/intro.h"
#include "./view/game.h"
#include "./view/afterGame.h"
*/
#define min(x,y) ((x) < (y) ? (x) : (y))

//GLint viewList[10]; //temporary placeholder for texture view lists

enum basicStructures_screen main_screenDef = intro;
bool main_startNewGame = true;

void initialize(){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    main_screenDef = intro;
    main_startNewGame = false;
}

void reshape(int width, int height){

    // Set the game-square size as the bigger dimension (hight or width)
    int squareSize = min(width, height);

    /*
    The first two values are the coordenates of the bottom-left pixel inside the window.
    This formula sets, proportionally, the game-area to the window centre position

    Ex.: Window 800:400
            Biggest possible square: 400:400
                x = (800-400/2) = 200

    The last two values are the size of screen to be drawn. It needs to be the biggest square possible
    */
    glViewport((width-squareSize)/2, (height-squareSize)/2, squareSize, squareSize);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Screen ratio: 1:1 (1000:1000)
    glOrtho(-500, 500, -500, 500, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawScene(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // &main_screenDef as parameter to enable switch between scenes
    // &main_startNewGame as parameter to choose between create and continue games
    switch (main_screenDef){ 
    case intro:
        //intro_drawScene(&main_screenDef, &main_startNewGame); // start new game or close window
        break;
    case game:
        //game_drawScene(&main_screenDef, &main_startNewGame);
        break;
    case afterGame:
        //afterGame_drawScene(&main_screenDef, &main_startNewGame); // start new game or close window
        break;
    default:
        break;
    }
    glutSwapBuffers();
    
    /*
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
        // desenhando o maior quadrado BRANCO possivel
        glVertex3f(-1000, 1000, 0.0);
        glVertex3f(-1000, -1000, 0.0);
        glVertex3f(1000, -1000, 0.0);
        glVertex3f(1000, 1000, 0.0);
    glEnd();
    glFlush();
    */
}

void pressedKey(unsigned char key, int x, int y){
    switch (main_screenDef){
    case intro:
        //intro_pressedKey(key, x, y);
        break;
    case game:
        //game_pressedKey(key, x, y);
        break;
    case afterGame:
        //afterGame_pressedKey(key, x, y);
        break;
    default:
        break;
    }
}

void mouseGestures(int button, int state, int x, int y){
    switch (main_screenDef){
    case intro:
        //intro_mouseGestures(button, state, x, y);
        break;
    case game:
        //game_mouseGestures(button, state, x, y);
        break;
    case afterGame:
        //afterGame_mouseGestures(button, state, x, y);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitContextVersion(1, 1); 
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 400, 400 );
    glutInitWindowPosition( 50, 50 );

    glutCreateWindow( "TP1: Galaxian Pedro Vaz e Mateus Lemos" );

    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(pressedKey);
    glutMouseFunc(mouseGestures);

    initialize();

    glutMainLoop();

    return 0;
}