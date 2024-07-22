#include "2drenderer.h"

void draw_debug(GameState* state, const int WIN_HEIGHT)
{
    // draw player info
    DrawText(TextFormat("Player: (%.2f, %.2f)", state->player->x, state->player->y), 0, WIN_HEIGHT + 10, 20, GREEN);
    DrawText(TextFormat("Player Dir: (%.2f, %.2f)", state->player->dirX, state->player->dirY), 0, WIN_HEIGHT + 30, 20, GREEN);

    // draw edit info
    DrawText(TextFormat("Edit Mode: %d", state->editMode), 10, WIN_HEIGHT + 60, 20, GREEN);
    DrawText(TextFormat("Mouse Pos: (%.2f, %.2f)", GetMousePosition().x, GetMousePosition().y), 10, WIN_HEIGHT + 80, 20, GREEN);

    return;
}

void draw_2dgame(GameState* state, CameraPlane* camera, const int WIN_HEIGHT, const int WIN_WIDTH)
{
    // draw map
    const int squareHeight = WIN_HEIGHT / state->height;
    const int squareWidth = WIN_WIDTH / state->width;
    for (int i = 0; i < state->height; i++)
    {
        const int wallY = i * WIN_HEIGHT / state->height;
        for (int j = 0; j < state->width; j++)
        {
            const int wallX = j * WIN_WIDTH / state->width;
            
            // get the color of each wall,
            Color wallColor;
            switch (state->map[i][j]) {
                case 0:
                    wallColor = BLACK;
                    break;
                case 1:
                    wallColor = RED;
                    break;
                default:
                    wallColor = BLUE;
                    break;
            }

            // and then draw that wall.
            DrawRectangle(wallX, wallY, squareWidth, squareHeight, wallColor);
        }
    }

    // draw the grid
    for (int i = 0; i < state->height; i++)
    {
        DrawLine(0, i * WIN_HEIGHT / state->height, WIN_WIDTH, i * WIN_HEIGHT / state->height, GRAY);
    }
    for (int i = 0; i < state->width; i++)
    {
        DrawLine(i * WIN_WIDTH / state->width, 0, i * WIN_WIDTH / state->width, WIN_HEIGHT, GRAY);
    }
    
    // draw window borders
    DrawRectangleLines(0, 0, WIN_WIDTH, WIN_HEIGHT, WHITE);

    // draw the player
    DrawCircle(state->player->x * squareWidth, state->player->y * squareHeight, PLAYER_SIZE_2D, GREEN);
    DrawLine(
        state->player->x * squareWidth,
        state->player->y * squareHeight,
        (state->player->x + state->player->dirX) * squareWidth,
        (state->player->y + state->player->dirY) * squareHeight,
        RED
    );

    // Draw the rays cast from the player's position
    draw_2d_rays(state, &camera, WIN_HEIGHT, WIN_WIDTH);

    if (DEBUG) {
        draw_debug(state, WIN_HEIGHT);
    }
}

// Function to draw rays cast from the player's position
void draw_2d_rays(GameState* state, CameraPlane* camera, const int WIN_HEIGHT, const int WIN_WIDTH)
{
    if (!state || !camera || !state->player || !state->map) return;

    const int squareHeight = WIN_HEIGHT / state->height;
    const int squareWidth = WIN_WIDTH / state->width;

    for (int i = 0; i < WIN_WIDTH; i++)
    {
        double cameraX = 2 * i / (double)WIN_WIDTH - 1;
        double rayDirX = state->player->dirX + camera->planeX * cameraX;
        double rayDirY = state->player->dirY + camera->planeY * cameraX;

        int mapX = (int)state->player->x;
        int mapY = (int)state->player->y;

        double sideDistX;
        double sideDistY;

        double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
        double perpWallDist;

        int stepX;
        int stepY;

        bool hit = false;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (state->player->x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - state->player->x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (state->player->y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - state->player->y) * deltaDistY;
        }

        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (mapX < 0 || mapX >= state->width || mapY < 0 || mapY >= state->height) {
                printf("Error: mapX or mapY out of bounds (mapX=%d, mapY=%d)\n", mapX, mapY);
                return;
            }

            if (state->map[mapX][mapY] > 0) hit = true;
        }

        if (side == 0) perpWallDist = (mapX - state->player->x + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - state->player->y + (1 - stepY) / 2) / rayDirY;

        int endX = (int)(state->player->x + rayDirX * perpWallDist) * squareWidth;
        int endY = (int)(state->player->y + rayDirY * perpWallDist) * squareHeight;

        DrawLine(
            state->player->x * squareWidth,
            state->player->y * squareHeight,
            endX,
            endY,
            YELLOW
        );
    }
}