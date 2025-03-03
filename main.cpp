#include "header.h"
#include "Game_object.h"
#include "Gamemap.h"
#include "Game_Character.h"
#include <stdfix.h>
#include "Timer.h"


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
        while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT) is_quit = true;
                character.HandleInput(event);
            }



            Map map_data = game_map_.GetMap();
            character.SetMapXY(map_data.start_x, map_data.start_y);
            character.Doplayer(map_data);

            game_map_.SetMap(map_data);
            backgr.renderTexture();
            game_map_.DrawMap();
            character.Show();

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
