enum basicStructures_screen { 
    intro, 
    game, 
    afterGame 
};

struct{
    int x;
    int y;
} typedef Vector2D;

struct{
    int x;
    int y;
    int z;
} typedef Vector3D;

struct{
    Vector2D position;
    Vector2D dimensions;
    int texture;
} typedef Sprite;

struct{
    Vector2D position;
    Vector2D dimensions;
    int texture;
    int currentFrame;
    int numberOfFrames; // created to use less than 30FPS sprites
    int framsSequesnce [30];
} typedef AnimatedSprite;
