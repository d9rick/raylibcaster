#pragma once
#include "game.h"

// describes the camera plane
typedef struct {
    double planeX;
    double planeY;
} CameraPlane;

// renders the game in 3d
void draw_3dgame(GameState* state, CameraPlane* camera, const int WIN_HEIGHT, const int WIN_WIDTH);
