#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
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

const int WALK_NONE = 0;
const int WALK_RIGHT = 1;

const int GRAVITY = 3;
const int RUN_SPEED = 3;
const int MAX_FALL_SPEED = 14;
const int MIN_FALL_SPEED = -19;
const double MAX_RUN_SPEED = 13.6;



const int BLANK_TILE_MIN = 90;
const int BLANK_TILE_MAX = 100;
const int BLANK_TILE = 1;
const int MAX_NUMBER_OF_TILES = 150;

const int SPIKE_MIN = 40;
const int SPIKE_MAX = 70;
const int ORIGINAL_MIN = 8;
const int ORIGINAL_MAX = 10;
const int RIDING_SHIP_MIN = 2;
const int RIDING_SHIP_MAX = 4;
const int ROCKET_MIN = 11;
const int ROCKET_MAX = 13;
const int REVERSAL_MIN = 5;
const int REVERSAL_MAX = 7;

const int PAUSE_SCREEN_X = 90;
const int PAUSE_SCREEN_Y = 110;




#endif // HEADER_H_INCLUDED
