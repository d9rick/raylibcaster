#pragma once

#include "raylib.h"
#include <stdlib.h>

typedef struct {
    Rectangle rect;
    Color color;
    char* text;
} Button;

// returns true if the button is being clicked
bool isButtonPressed(Button* button, Vector2 mousePos);

// draws the button to the screen
void drawButton(Button* button);

// creates a new button
Button* newButton(char* text, int x, int y, int width, int height, Color color);