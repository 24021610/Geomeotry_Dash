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
    character.LoadImg("Resources/model.jpg");
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


            SDL_SetRenderDrawColor(renderer, 0,255,255,255);
            SDL_RenderClear(renderer);
            background.DrawMap();
            Map map_data = background.GetMap();

            character.Check_to_map(map_data);
            character.Doplayer(map_data);
            character.Show();

            SDL_RenderPresent(renderer);
            SDL_Delay(200);

    }



}
