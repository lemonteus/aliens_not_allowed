#pragma once
#include "../lib/player.h"
#include "../lib/basicStructures.h"

bool projectileHitTargetRectangle(Vector2D projectilePosition, Vector2D targetBottomRight, Vector2D targetDimensions);

void game_pressedKey(unsigned char key, int x, int y, Player *player);