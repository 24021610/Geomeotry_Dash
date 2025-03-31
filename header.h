#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <stdfix.h>


const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Geometry Dash Meltdown Remastered";
const int FRAME_PER_SECOND = 28;
extern SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
extern SDL_Renderer* renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

struct Input
{
    int right;
    int jump;
    int left;
};
const int GRAVITY = 3;
const int RUN_SPEED = 3;
const int MAX_FALL_SPEED = 14;
const int MIN_FALL_SPEED = -19;
const double MAX_RUN_SPEED = 13.6;
const double MIN_RUN_SPEED = -13.6;



const int BLANK_TILE_MIN = 90;
const int BLANK_TILE_MAX = 100;
const int BLANK_TILE = 1;
const int MAX_NUMBER_OF_TILES = 150;

const int SPIKE_MIN = 40;
const int SPIKE_MAX = 80;
const int ORIGINAL_MIN = 8;
const int ORIGINAL_MAX = 10;
const int RIDING_SHIP_MIN = 2;
const int RIDING_SHIP_MAX = 4;
const int ROCKET_MIN = 11;
const int ROCKET_MAX = 13;
const int REVERSAL_MIN = 5;
const int REVERSAL_MAX = 7;
const int DECORATION_MIN = 97;
const int DECORATION_MAX = 109;

const int PAUSE_SCREEN_X = 0;
const int PAUSE_SCREEN_Y = 0;

const int FINISH_SCREEN_X = 100;
const int FINISH_SCREEN_Y = 100;

const char* HIGHSCORE_FILE = "highscores.txt";


#endif // HEADER_H_INCLUDED
