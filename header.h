#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <windows.h>
#include <stdfix.h>


static const int SCREEN_WIDTH = 1080;
static const int SCREEN_HEIGHT = 600;
static const char* WINDOW_TITLE = "Geometry Dash Meltdown Remastered";

const int FRAME_PER_SECOND = 120;

extern SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
extern SDL_Renderer* renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

struct Input
{
    int right;
    int jump;
};

#define WALK_NONE  0
#define WALK_RIGHT 1

#define GRAVITY 3
#define RUN_SPEED 3
#define MAX_FALL_SPEED 14
#define MIN_FALL_SPEED -19
#define MAX_RUN_SPEED 13.6



#define BLANK_TILE_MIN 90
#define BLANK_TILE_MAX 100
#define BLANK_TILE 1
#define MAX_NUMBER_OF_TILES 150

#define SPIKE_MIN 40
#define SPIKE_MAX 70
#define ORIGINAL_MIN 8
#define ORIGINAL_MAX 10
#define RIDING_SHIP_MIN 2
#define RIDING_SHIP_MAX 4
#define ROCKET_MIN 11
#define ROCKET_MAX 13
#define REVERSAL_MIN 5
#define REVERSAL_MAX 7



#endif // HEADER_H_INCLUDED
