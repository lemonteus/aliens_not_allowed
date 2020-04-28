#pragma once

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
    Entity positionAndDimensions;
    GLuint textureID;
    char text[buttonTextMaxSize];
    unsigned int numberCharacters;
} Button;
