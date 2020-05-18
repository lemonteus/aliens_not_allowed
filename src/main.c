#include <stdbool.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include "./lib/basicStructures.h"
#include "./lib/player.h"

// Scenes
#include "./view/intro.h"
#include "./view/game.h"
#include "./view/afterGame.h"

//Handling textures
#include "./view/texture.h"

//Handling keyboard events
#include "./lib/keyboard.h"

#define min(x,y) ((x) < (y) ? (x) : (y))
#define PLAYER_INITIAL_Y_POS 350

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

Player player;

enum basicStructures_screen main_screenDef = intro;
bool main_startNewGame = true;

void initialize(){
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glEnable(GL_BLEND ); //enabling support for texture transparency
    glEnable(GL_DEPTH_TEST); // enabling depth buffer and z coordinate
    glEnable(GL_TEXTURE_2D); //enabling texture support

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    
    //avoid ragged transitions by disabling linear texel filtering for mignification and using nearest instead                                                 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //newTextureID([TEXTURE PATH]) // TEXTURE ID GOES UP BY ONE EVERYTIME newTextureID IS CALLED

    newTextureID("../assets/player_spaceship.png"); //0
    newTextureID("../assets/purple_enemy.png"); //1
    newTextureID("../assets/intro_bg.png"); //2
    newTextureID("../assets/intro_mg1.png"); //3
    newTextureID("../assets/intro_mg2.png"); //4
    newTextureID("../assets/starry_sky.png"); //5

    generateViewList(2000, 2000, 0, 1, rgb_white); //white background
    mapSpriteSheet(getTextureID(0), 1600, 1600, 6400, 1600, 10, 5); //player spritesheet
    mapSpriteSheet(getTextureID(1), 1600, 1600, 3200, 1600, 10, 5); //enemy spritesheet
    /*generateTextureViewList(getTextureID(2), 1000, 1000, 0, 1, defaultVertices); //intro background
    generateTextureViewList(getTextureID(3), 1000, 1000, 4, 1, defaultVertices); //intro midground 1
    generateTextureViewList(getTextureID(4), 1000, 1000, 5, 1, defaultVertices); //intro midground 2
    generateTextureViewList(getTextureID(5), 5000, 1000, 3, 1, defaultVertices); //starry sky*/


   int offset = 10;

    viewLists[vlCount] = glGenLists(1);
    glNewList(viewLists[vlCount], GL_COMPILE);
     glBindTexture(GL_TEXTURE_2D, getTextureID(2));

	glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-500, 500,  0);
		glTexCoord2f(1, 1); glVertex3f( 500, 500,  0);
		glTexCoord2f(1, 0); glVertex3f( 500, -500,  0);
		glTexCoord2f(0, 0); glVertex3f( -500, -500,  0);
	glEnd();
		
	glBindTexture(GL_TEXTURE_2D, getTextureID(5));

	glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f( -500 - offset, 500,  3);
		glTexCoord2f(1, 1); glVertex3f( 8000/2 - offset, 500,  3);
		glTexCoord2f(1, 0); glVertex3f( 8000/2 - offset, -500,  3);
		glTexCoord2f(0, 0); glVertex3f( -500 - offset, -500,  3);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, getTextureID(4));

	glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-500, 500,  4);
		glTexCoord2f(1, 1); glVertex3f( 500, 500,  4);
		glTexCoord2f(1, 0); glVertex3f( 500, -500,  4);
		glTexCoord2f(0, 0); glVertex3f( -500, -500,  4);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, getTextureID(3));

	glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-500, 500,  5);
		glTexCoord2f(1, 1); glVertex3f( 500, 500,  5);
		glTexCoord2f(1, 0); glVertex3f( 500, -500,  5);
		glTexCoord2f(0, 0); glVertex3f( -500, -500,  5);
	glEnd();
    glEndList();

    vlCount = vlCount + 1;
    

    player_initialize(&player, 0, -PLAYER_INITIAL_Y_POS, getTextureID(1));

    main_screenDef = intro;

    main_startNewGame = false;
}

void reshape(int width, int height){

    // Set the game-square size as the bigger dimension (height or width)
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

void drawText(const char *text, int lenght, int x, int y, int z){
    double matrix[16];

    glMatrixMode(GL_PROJECTION);
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();

    glOrtho(-500, 500, -500, 500, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    glLoadIdentity();

    glRasterPos3i(x, y, z);
    for(int i = 0; i < lenght; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void drawScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
    
    // &main_screenDef as parameter to enable switch between scenes
    // &main_startNewGame as parameter to choose between create and continue games
    switch (main_screenDef){ 
    case intro:
        intro_drawScene(&main_screenDef, &main_startNewGame); // start new game or close window
        break;
    case game:
        game_drawScene(&main_screenDef, &main_startNewGame, &player);
        break;
    case afterGame:
        //afterGame_drawScene(&main_screenDef, &main_startNewGame); // start new game or close window
        break;
    default:
        break;
    }

    glutSwapBuffers();
}

void update(){
    glutPostRedisplay();
}

void keyDown (unsigned char key, int x, int y){
    keyState[key] = true;

    switch (main_screenDef){
    case intro:
        //intro_keyDown(key, x, y);
        break;
    case game:
        game_keyDown(key, x, y, &player);
        break;
    case afterGame:
        //afterGame_pressedKey(key, x, y);
        break;
    default:
        break;
    }

}

void keyUp (unsigned char key, int x, int y){
    keyState[key] = false;

    switch(main_screenDef){
        case game:
            game_keyUp(key, x, y, &player);
    }
}

void specialKeyDown (int key, int x, int y){
    switch(main_screenDef){
        case game:
            game_specialKeyDown(key, x, y, &player);
    }
}

void specialKeyUp (int key, int x, int y){
    switch(main_screenDef){
        case game:
            game_specialKeyUp(key, x, y, &player);
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

    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    glutInitWindowPosition( 50, 50 );

    glutCreateWindow( "TP1: Galaxian Pedro Vaz e Mateus Lemos" );

    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);

    glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_ON); //avoid successive calls to a function whenever a key is pressed and held

    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);
    glutMouseFunc(mouseGestures);
    glutIdleFunc(update);

    initialize();

    glutMainLoop();

    return 0;
}