#pragma once

#include "game.h"
#include "raylib.h"
#include "3drenderer.h"

#define PLAYER_SIZE_2D 10
#define PLAYER_DIR_SIZE 20

#define DEBUG true

// renders the game in 2d
void draw_2dgame(GameState* state, CameraPlane* camera, const int WIN_HEIGHT, const int WIN_WIDTH);

// draws debug information
void draw_debug(GameState* state, const int win_height);

// debug function to show raycasting directions
void draw_2d_rays(GameState* state, CameraPlane* camera, const int WIN_HEIGHT, const int WIN_WIDTH);