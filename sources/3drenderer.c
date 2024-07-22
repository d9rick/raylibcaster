#include "3drenderer.h"
#include "raylib.h"
#include <math.h>

// CREDIT TO https://lodev.org/cgtutor/raycasting.html
// for the raycasting algorithm, and much of this code

void draw_3dgame(GameState* state, CameraPlane* camera, const int WIN_HEIGHT, const int WIN_WIDTH)
{
    if (!state || !camera || !state->player || !state->map) return;

    // loop over every vertical line, creating a ray
    for (int i = 0; i < WIN_WIDTH; i++)
    {
        // calculate that ray's direction & position
        double cameraX = 2.0 * i / (double)WIN_WIDTH - 1.0; 
        double rayDirX = state->player->dirX + camera->planeX * cameraX;
        double rayDirY = state->player->dirY + camera->planeY * cameraX;

        // which box of the map we're in
        int mapX = (int)state->player->x;
        int mapY = (int)state->player->y;

        // length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // length of ray from one x or y-side to next x or y-side
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
        double perpWallDist;

        // what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        // was a wall hit?
        bool hit = false;
        int side; // was the wall vertical or horizontal?

        // calculate step and initial sideDist
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

        // perform DDA (Digital Differential Analysis)
        while (!hit)
        {
            // jump to next map square, OR in x-direction, OR in y-direction
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

            // check if ray has hit a wall
            if (mapX < 0 || mapX >= state->width || mapY < 0 || mapY >= state->height) {
                return;
            }

            // check if ray has hit a wall
            if (state->map[mapX][mapY] > 0) hit = true;
        }

        // calculate distance to the point of impact
        if (side == 0) perpWallDist = (mapX - state->player->x + (1 - stepX) / 2) / rayDirX;
        else           perpWallDist = (mapY - state->player->y + (1 - stepY) / 2) / rayDirY;

        // calculate height of line to draw on screen
        int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

        // calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
        if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

        // choose wall color
        Color color;
        switch(state->map[mapX][mapY])
        {
            case 1:  color = RED;  break; // red
            default: color = BLUE; break; // blue
        }

        // give x and y sides different brightness
        if (side == 1) {color.r = color.r / 2; color.g = color.g / 2; color.b = color.b / 2;}

        // debug prints
        printf("Drawing line at x=%d from y=%d to y=%d with color (%d, %d, %d)\n", i, drawStart, drawEnd, color.r, color.g, color.b);

        // draw the pixels of the stripe as a vertical line
        DrawLine(i, drawStart, i, drawEnd, color);
    }
}
