#include "header.h"
#include "Game_object.h"
#include "Gamemap.h"
#include "Game_Character.h"
#include "Timer.h"
#include "Menu.h"


int main(int argc, char *argv[])
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    GameCharacter character;
    character.LoadImg("Resources/model.jpg");

    Gameobject backgr;
    backgr.loadTexture("Resources/background.png");

    GameMap game_map_;
    game_map_.LoadMap("map1.txt");
    game_map_.LoadTiles();

    Timer timer;



    bool is_quit = false;
    SDL_Event event;
    while (!is_quit)
    {

        timer.start();
        loadMenu();
        while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT) is_quit = true;
                if (game_state_menu == true)
                {
                    HandleEventsInMenu(event);
                }

                else if(game_state_playing)
                {
                    character.HandleInput(event);
                }
            }

            if (game_state_menu) UpdateMenu();
            else  if (game_state_playing == true) SDL_Quit();

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);

            int real_time = timer.Get_Ticks();
            int one_frame = 1000/FRAME_PER_SECOND; // MILLISECOND

            if(real_time < one_frame)
            {
                int delay = one_frame - real_time;
                SDL_Delay(delay);
            }
    }



}
