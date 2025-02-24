#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <stdfix.h>

static const int SCREEN_WIDTH = 1080;
static const int SCREEN_HEIGHT = 600;
static const char* WINDOW_TITLE = "Hello World";

extern SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
extern SDL_Renderer* renderer = SDL_CreateRenderer(window, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

struct Input
{
    int right_;
    int jump_;
};

#define WALK_NONE  0
#define WALK_RIGHT 1


#endif // HEADER_H_INCLUDED
