#pragma once

// Victory = true;
// Defeat = false;
bool game_finalStatus = false;

void game_drawScene();
void game_pressedKey(unsigned char key, int x, int y);
bool game_gameOver();

