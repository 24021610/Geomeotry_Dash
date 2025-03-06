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
static const char* WINDOW_TITLE = "Hello World";

const int FRAME_PER_SECOND = 30;

extern SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
extern SDL_Renderer* renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

struct Input
{
    int right;
    int jump;
};

#define WALK_NONE  0
#define WALK_RIGHT 1

#define GRAVITY 0.8
#define RUN_SPEED 5
#define MAX_FALL_SPEED 12
#define MAX_RUN_SPEED 10
#define PLAYER_SPEED 18


#define BLANK_TILE_MIN 90
#define BLANK_TILE_MAX 100
#define BLANK_TILE 1
#define MAX_NUMBER_OF_TILES 150


#endif // HEADER_H_INCLUDED
