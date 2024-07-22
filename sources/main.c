#include "raylib.h"
#include "game.h"
#include "2drenderer.h"
#include "button.h"
#include "3drenderer.h"
#include <string.h>

#define SCREEN_WIDTH  (1200)
#define SCREEN_HEIGHT (900)
#define FOV_DEGREES (120)
#define FOV (FOV_DEGREES * (PI / 180))

#define WINDOW_TITLE "raylibCaster"

// handles the user input as the game is running
void processInput(GameState* state, Button** buttons, float delta);

int main(void)
{
    // raylib initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // 2d renderer initialization
    const int WIN_HEIGHT_2D = SCREEN_WIDTH / 3;
    const int WIN_WIDTH_2D = SCREEN_WIDTH / 3;

    // game state initialization
    GameState* state;
    size_t grid_height = 10;
    size_t grid_width = 10;
    state = game_init(grid_height, grid_width, WIN_HEIGHT_2D);

    // initialize camera for 3d render
    CameraPlane camera;
    camera.planeX = cos(FOV / 2.0); // Adjust based on the new FOV
    camera.planeY = sin(FOV / 2.0); // Adjust based on the new FOV


    // create buttons
    const size_t numButtons = 1;
    Button** buttons = malloc(numButtons * sizeof(Button*));
    Button* editButton = newButton("Edit", 10, WIN_HEIGHT_2D + 120, 100, 50, GREEN);
    buttons[0] = editButton;

    // game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
            // draw the 2d game
            ClearBackground(BLACK);
            draw_2dgame(state, &camera, WIN_HEIGHT_2D, WIN_WIDTH_2D);

            // draw the edit button
            drawButton(editButton);

            // draw the 3d game
            BeginScissorMode(WIN_WIDTH_2D, 0, SCREEN_WIDTH - WIN_WIDTH_2D, SCREEN_HEIGHT);
                draw_3dgame(state, &camera, SCREEN_HEIGHT, SCREEN_WIDTH);
            EndScissorMode();

            // get frame time for physics calculations
            float delta = GetFrameTime();

            // process user input
            processInput(state, buttons, delta);
        EndDrawing();
    }

    // free memory and close the window
    game_free(state);
    free(editButton);
    free(buttons);
    CloseWindow();

    return 0;
}

void processInput(GameState* state, Button** buttons, float delta)
{

// get the keyboard inputs
    // move user position
    if (IsKeyDown(KEY_W))
    {
        game_move_forward(state, delta);
    }
    if (IsKeyDown(KEY_S))
    {
        game_move_forward(state, -delta);
    }
    // turn user direction
    if (IsKeyDown(KEY_A))
    {
        game_turn_player(state, -delta);
    }
    if (IsKeyDown(KEY_D))
    {
        game_turn_player(state, delta);
    }

// handle mouse input
    // check if left click is even down
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return;
    }

    // get the mouse position
    Vector2 mousePos = GetMousePosition();

    // handle edit mode inputs
    if(state->editMode)
    {
        // check if mouse is in the bounds of the map
        if (mousePos.x < 0 || mousePos.x >= state->screen_size || mousePos.y < 0 || mousePos.y >= state->screen_size)
        {
            return;
        }

        // place a wall at the mouse position
        int wallX = (int)(mousePos.x / (state->screen_size / state->width));
        int wallY = (int)(mousePos.y / (state->screen_size / state->height));
        game_place_wall(state, wallX, wallY);
    }

    // check if the mouse is over a button
    for (int i = 0; i < 1; i++)
    {
        if (isButtonPressed(buttons[i], mousePos))
        {
            // handle button press
            if (strcmp(buttons[i]->text, "Edit") == 0)
            {
                state->editMode = !state->editMode;
            }
        }
    }
    return;
}