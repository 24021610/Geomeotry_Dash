#include "header.h"
#include "Game_object.h"
#include "Gamemap.h"
#include <stdfix.h>

using namespace std;

int main(int argc, char *argv[])
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


    GameMap gamemap;

    gamemap.LoadMap("map1.txt");
    gamemap.LoadTiles();
    gamemap.DrawMap();
    SDL_RenderPresent(renderer);


}
