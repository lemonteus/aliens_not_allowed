#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./basicStructures.h";

#include "./view/intro.h"
#include "./view/game.h"
#include "./view/afterGame.h"

enum screen { intro, game, afterGame };


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
