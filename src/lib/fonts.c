#include <string.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "fonts.h"
    
void drawText(void * font , char *text, float x, float y, float z) {
    glRasterPos3f(x, y, z);

    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

void drawTextCentralized(void * font, char *text, float x, float y, float z){
    int textWidth = 0;    

    for (int i = 0; i < strlen(text); i++){
        textWidth += glutBitmapWidth(font, text[i]);
    }
    
    glRasterPos3f( (x - (textWidth/2)), y, z);

    for (int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(font, text[i]);
    }
}
