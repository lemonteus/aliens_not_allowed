#ifndef _BASICSTRUCTURES_H_
#define _BASICSTRUCTURES_H_

#define buttonTextMaxSize 50

enum basicStructures_screen { intro, game, afterGame };

typedef struct{
    int x;
    int y;
} Vector2D;

typedef struct{
    int x;
    int y;
    int z;
} Vector3D;

typedef struct{
    Vector2D position;
    Vector2D dimensions;
} Entity;

typedef struct{
    char text[buttonTextMaxSize];
    unsigned int numberCharacters;
    Entity positionAndDimensions; // top-left vertex position
    unsigned int textureID;
} Button;

#endif //_BASICSTRUCTURES_H_