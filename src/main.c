#include <stdbool.h>
#include <stdio.h> //eu inclui apenas pra fazer testes

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "./lib/basicStructures.h"

#include "./view/intro.h"
#include "./view/game.h"
#include "./view/afterGame.h"

//usei aquela definicao que voce deu pra gente na aula pra pegar o menor entre dois valores, coutinho. achei foda :)
#define min(x,y) ((x) < (y) ? (x) : (y))

enum basicStructures_screen main_screenDef = intro;

//void initialize();
//void drawScene();
//void reshape (int width, int height);
void pressedKey(unsigned char key, int x, int y); // verify current screen & call the pressedKey of the specific ".h"


void initialize(){
    
    // define qual é a cor do fundo
    glClearColor(1.0, 1.0, 1.0, 0.0); // branco

    // desenho preenchido vs. contorno
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    main_screenDef = intro;
}

void drawScene(){
/*    switch (main_screenDef){
    case intro:
        //intro_drawScene();
        break;
    case game:
        //game_drawScene();
        break;
    case afterGame:
        //afterGame_drawScene(game_finalStatus);
        break;
    default:
        break;
    }
    glutSwapBuffers();
    */
    glClearColor(0, 0, 0, 0); //fundo da tela sempre preto
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TRIANGLE_FAN);
        // desenhando o maior quadrado BRANCO possivel
        glVertex3f(-1000, 1000, 0.0);
        glVertex3f(-1000, -1000, 0.0);
        glVertex3f(1000, -1000, 0.0);
        glVertex3f(1000, 1000, 0.0);
    glEnd();

    glFlush();

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

void reshape(int width, int height){

    int squareSize = min(width, height);
    //o tamanho da tela sempre eh um quadrado cujo tamanho do lado eh a menor dimensao dentre a largura e a altura

    /*
    os dois primeiros valores são as coordenadas do pixel que esta mais a esquerda e mais embaixo da janela.
    essas formulas servem para deslocar proporcionalmente a regiao da tela a ser desenhada para o centro da janela.
    ex: janela de 800x400 -> maior quadrado possivel: 400x400 -> logo, tela precisa ser desenhada a partir do pixel de valor x = (800-400/2) = 200.

    os dois ultimos valores sao o tamanho da tela a ser desenhada, e obviamente, precisam ser do tamanho do maior quadrado possivel.
    */

    glViewport((width-squareSize)/2, (height-squareSize)/2, squareSize, squareSize);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // escala sempre continua sendo a mesma
    glOrtho(-1000,  1000, -1000, 1000, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    //glutKeyboardFunc(pressedKey);

    initialize();

    glutMainLoop();

    return 0;
}