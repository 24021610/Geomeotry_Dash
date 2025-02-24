#include "header.h"
#include "Game_object.h"
#include "Gamemap.h"
#include "Game_Character.h"
#include <stdfix.h>


using namespace std;

int main(int argc, char *argv[])
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    GameCharacter character;
    GameMap background;

    background.LoadMap("map1.txt");
    background.LoadTiles();

    bool is_quit = false;
    SDL_Event event;
    while (!is_quit)
    {
        while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT) is_quit = true;
                character.HandleInput(event);
            }

            SDL_RenderClear(renderer);
            background.DrawMap();
            Map map_data = background.GetMap();

            character.Doplayer(map_data);
            character.Show();

            SDL_RenderPresent(renderer);

    }



}
