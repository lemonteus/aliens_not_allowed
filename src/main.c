#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include "./lib/basicStructures.h"
#include "./lib/player.h"

// Scenes
#include "./view/intro.h"
#include "./view/game.h"
#include "./view/afterGame.h"

//Handle textures
#include "./view/texture.h"

//Handle keyboard events
#include "./lib/keyboard.h"

#define min(x,y) ((x) < (y) ? (x) : (y))
#define PLAYER_INITIAL_Y_POS 350

bool mouseInBounds = false;

Player player;

enum basicStructures_screen main_screenDef = intro; // { intro, game, afterGame }
bool main_startNewGame = true;

void initialize(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    glEnable(GL_BLEND ); // enable support for texture transparency
    glEnable(GL_DEPTH_TEST); // enable depth buffer and z coordinate
    glEnable(GL_TEXTURE_2D); //enable texture support

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    
    //avoid ragged transitions by disabling linear texel filtering for mignification and using nearest instead                                                 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //newTextureID([TEXTURE PATH]) // TEXTURE ID GOES UP BY ONE EVERYTIME newTextureID IS CALLED

    newTextureID("../assets/player_spaceship.png"); // 0
    newTextureID("../assets/purple_enemy.png"); // 1
    newTextureID("../assets/intro_bg.png");  // 2
    newTextureID("../assets/intro_mg1.png"); // 3
    newTextureID("../assets/intro_mg2.png"); // 4
    newTextureID("../assets/starry_sky.png"); // 5

    generateViewList(2000, 2000, 0, 1, rgb_white); //white background

    mapSpriteSheet(getTextureID(0), 1600, 1600, 6400, 1600, 10, 5); //player spritesheet
    mapSpriteSheet(getTextureID(1), 1600, 1600, 3200, 1600, 10, 5); //enemy spritesheet

    generateTextureViewList(getTextureID(2), 1000, 1000, 0, 1, defaultVertices); // intro background
    generateTextureViewList(getTextureID(3), 1000, 1000, 1, 1, defaultVertices); // intro midground 1
    generateTextureViewList(getTextureID(4), 1000, 1000, 2, 1, defaultVertices); // intro midground 2

    player_initialize(&player, 0, -PLAYER_INITIAL_Y_POS, getTextureID(0));

    main_screenDef = intro;
    main_startNewGame = false;
}

Vector2D coordinatesTranslator(int x, int y){
    int currentWidth  = glutGet(GLUT_WINDOW_WIDTH);
    int currentHeight = glutGet(GLUT_WINDOW_HEIGHT);

    int smallestSizeValue = min(currentWidth, currentHeight);

    Vector2D windowCenter;
    windowCenter.x = currentWidth/2;
    windowCenter.y = currentHeight/2;

    Vector2D translatedCoordinates;

    if (x <= windowCenter.x + smallestSizeValue/2 &&
        x >= windowCenter.x - smallestSizeValue/2 &&
        y <= windowCenter.y + smallestSizeValue/2 &&
        y >= windowCenter.y - smallestSizeValue/2){
            mouseInBounds = true;
    } else{
        mouseInBounds = false;
        return translatedCoordinates;
    }
    // The in bounds area is a square whith 1000 unitis for each side
    double relativeValue = (double)1000/smallestSizeValue;

    translatedCoordinates.x = round( (double)(x - windowCenter.x) * relativeValue );
    translatedCoordinates.y = round( (-1) * (double)(y - windowCenter.y) * relativeValue);

    return translatedCoordinates;
}

void reshape_callback(int width, int height){
    // Set the game-square size as the bigger dimension (height or width)
    int squareSize = min(width, height);

    /*
     * The first two values are the coordenates of the bottom-left pixel inside the window.
     * This formula sets, proportionally, the game-area to the window centre position
     * 
     *  e.g.: Window 800:400
     *       Biggest possible square: 400:400
     *          x = (800-400/2) = 200
     * 
     * The last two values are the size of screen to be drawn. It needs to be the biggest square possible
     */
    glViewport((width-squareSize)/2, (height-squareSize)/2, squareSize, squareSize);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Screen ratio: 1:1 (1000:1000)
    glOrtho(-500, 500, -500, 500, -10, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawScene_callback(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	
    
    // &main_screenDef as parameter to enable switch between scenes
    // &main_startNewGame as parameter to choose between create and continue games
    switch (main_screenDef){ 
    case intro:
        intro_drawScene();
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

void update_callback(){
    glutPostRedisplay();
}

void keyDown_callback(unsigned char key, int x, int y){
    keyState[key] = true;

    switch (main_screenDef){
    case(intro):
        intro_keyboardDownFunc(key, x, y, &main_screenDef);
        break;
    case(game):
        game_keyDown(key, x, y, &player);
        break;
    case(afterGame):
        //afterGame_pressedKey(key, x, y);
        break;
    default:
        break;
    }
}

void keyUp_callback(unsigned char key, int x, int y){
    keyState[key] = false;

    switch(main_screenDef){
        case(game):
            game_keyUp(key, x, y, &player);
            break;
    }
}

void specialKeyDown_callback(int key, int x, int y){
    switch(main_screenDef){
        case(intro):
            intro_specialKeyDownFunc(key, x, y);
            break;
        case(game):
            game_specialKeyDown(key, x, y, &player);
            break;
    }
}

void specialKeyUp_callback(int key, int x, int y){
    switch(main_screenDef){
        case(game):
            game_specialKeyUp(key, x, y, &player);
            break;
    }
}

void mousePassiveFunc_callback(int x, int y){
    Vector2D translatedCoordinates = coordinatesTranslator(x, y);

    switch (main_screenDef){
    case intro:
        intro_mousePassiveFunc(translatedCoordinates.x, translatedCoordinates.y, mouseInBounds);
        break;
    case game:
        //game_mousePassiveFunc(translatedCoordinates.x, translatedCoordinates.y, mouseInBounds);
        break;
    case afterGame:
        //afterGame_mousePassiveFunc(translatedCoordinates.x, translatedCoordinates.y, mouseInBounds);
        break;
    default:
        break;
    }
}

void mouseActiveFunc_callback(int button, int state, int x, int y){
    Vector2D translatedCoordinates = coordinatesTranslator(x, y);

    switch (main_screenDef){
    case intro:
        intro_mouseActiveFunc(button, state, translatedCoordinates.x, translatedCoordinates.y, mouseInBounds, &main_screenDef);
        break;
    case game:
        //game_mouseActiveFunc(button, state, translatedCoordinates.x, translatedCoordinates.y, mouseInBounds, &main_startNewGame);;
        break;
    case afterGame:
        //afterGame_mouseActiveFunc(button, state, translatedCoordinates.x, translatedCoordinates.y, mouseInBounds, &main_startNewGame);;
        break;
    default:
        break;
    }
}

void timerFunc(int value){
	intro_incrementOffset();

	glutTimerFunc(100, timerFunc, 1); //call timerFunc recursively so it's forever looping
}

int main(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitContextVersion(1, 1); 
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 50, 50 );

    glutCreateWindow( "TP1 - Galaxian: Pedro Vaz e Mateus Lemos" );

    glutDisplayFunc(drawScene_callback);
    glutReshapeFunc(reshape_callback);

    glutIgnoreKeyRepeat(GLUT_KEY_REPEAT_ON); //avoid successive calls to a function whenever a key is pressed and held

    glutKeyboardFunc(keyDown_callback);
    glutKeyboardUpFunc(keyUp_callback);
    glutSpecialFunc(specialKeyDown_callback);
    glutSpecialUpFunc(specialKeyUp_callback);

    glutMouseFunc(mouseActiveFunc_callback);
    glutPassiveMotionFunc(mousePassiveFunc_callback);

    glutIdleFunc(update_callback);
    glutTimerFunc(100, timerFunc, 1); //update every 0.1 second

    initialize();

    glutMainLoop();

    return 0;
}