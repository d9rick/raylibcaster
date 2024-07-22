#include "game.h"
#include <math.h>

GameState* game_init(size_t height, size_t width, size_t screen_size)
{
    GameState* state = malloc(sizeof(GameState));
    if (!state) {
        printf("Error: Failed to allocate memory for GameState\n");
        return NULL;
    }

    state->height = height;
    state->width = width;
    state->screen_size = screen_size;
    state->editMode = false;

    PlayerState* player = malloc(sizeof(PlayerState));
    if (!player) {
        printf("Error: Failed to allocate memory for PlayerState\n");
        free(state);
        return NULL;
    }

    player->x = width / 2.0;
    player->y = height / 2.0;
    player->dirX = 0;
    player->dirY = 1;
    player->moveSpeed = DEFAULT_MOVE_SPEED;
    player->turnSpeed = DEFAULT_TURN_SPEED;
    state->player = player;

    state->map = malloc(height * sizeof(size_t*));
    if (!state->map) {
        printf("Error: Failed to allocate memory for map\n");
        free(player);
        free(state);
        return NULL;
    }

    for (int i = 0; i < height; i++)
    {
        state->map[i] = malloc(width * sizeof(size_t));
        if (!state->map[i]) {
            printf("Error: Failed to allocate memory for map row %d\n", i);
            for (int j = 0; j < i; j++) {
                free(state->map[j]);
            }
            free(state->map);
            free(player);
            free(state);
            return NULL;
        }

        for (int j = 0; j < width; j++)
        {
            state->map[i][j] = 0;
        }
    }

    return state;
}

void game_free(GameState* state)
{
    if (!state) return;
    
    for (int i = 0; i < state->height; i++) {
        free(state->map[i]);
    }
    free(state->map);
    free(state->player);
    free(state);
}


void game_move_forward(GameState* state, float delta)
{
    // calculate distance to move
    double xDist = state->player->dirX * state->player->moveSpeed * delta;
    double yDist = state->player->dirY * state->player->moveSpeed * delta;

    // check that player is in bounds after move
    if (state->player->x + xDist < 0 || state->player->x + xDist >= state->width || state->player->y + yDist < 0 || state->player->y + yDist >= state->height)
    {
        return;
    }

    // then check that player isn't moving into a wall
    if (state->map[(int)(state->player->y + yDist)][(int)(state->player->x + xDist)] != 0)
    {
        return;
    }

    // if all is good, move player forward in the direction they are facing
    state->player->x += xDist;
    state->player->y += yDist;
}

void game_turn_player(GameState* state, float delta)
{
    // rotate player direction
    state->player->dirX = state->player->dirX * cos(state->player->turnSpeed * delta) - state->player->dirY * sin(state->player->turnSpeed * delta);
    state->player->dirY = state->player->dirX * sin(state->player->turnSpeed * delta) + state->player->dirY * cos(state->player->turnSpeed * delta);

    // and then normalize direction vector so everything works
    double length = sqrt(state->player->dirX * state->player->dirX + state->player->dirY * state->player->dirY);
    state->player->dirX /= length;
    state->player->dirY /= length;
}

void game_place_wall(GameState* state, size_t x, size_t y)
{
    // place a wall at the given coordinate
    state->map[y][x] += 1;
    state->map[y][x] %= 3; // wrap around to 0 if we go over 2
}