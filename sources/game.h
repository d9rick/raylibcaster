#pragma once

#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_MOVE_SPEED 3
#define DEFAULT_TURN_SPEED 5

// describes the location, angle, and physics of the player
typedef struct {
    // player position (origin)
    double x;
    double y;

    // direction vector (defaults to north)
    double dirX;
    double dirY;

    // physics
    float moveSpeed; // in pixels per tick
    float turnSpeed; // in rads per tick
} PlayerState;

typedef struct {
    // player state
    PlayerState* player;
    
    // world state
    size_t** map;
    size_t height;
    size_t width;

    // edit mode
    bool editMode;

    // screen height and width (same since square screen)
    size_t screen_size;
} GameState;

// initializes the game state with player at center of an empty map aimed at 0 degrees
GameState* game_init(size_t height, size_t width, size_t screen_size);

// frees the game state
void game_free(GameState* state);

// moves the player forward
void game_move_forward(GameState* state, float delta);

// turns the player 
void game_turn_player(GameState* state, float delta);

// place a wall at a coordinate
void game_place_wall(GameState* state, size_t x, size_t y);