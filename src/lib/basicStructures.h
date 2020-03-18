#pragma once

enum basicStructures_screen { 
    intro, 
    game, 
    afterGame
};

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
    int texture;
} Sprite;

typedef struct{
    Vector2D position;
    Vector2D dimensions;
    int texture;
    int currentFrame;
    int numberOfFrames; // created to use less than 30FPS sprites
    int framsSequesnce [30];
} AnimatedSprite;
