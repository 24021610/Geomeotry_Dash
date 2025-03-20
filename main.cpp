#include "header.h"
#include "Game_object.h"
#include "Gamemap.h"
#include "Game_Character.h"
#include "Timer.h"
#include "Menu.h"
#include "Bullet.h"
#include "FinalBoss.h"

int main(int argc, char *argv[])
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return 0;
    Mix_Music *gameMusic = Mix_LoadMUS("Resources/ingame.mp3");
    Mix_Music *menuMusic = Mix_LoadMUS("Resources/menu.mp3");

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
            if(event.type == SDL_QUIT)
            {
                quit();
                is_quit = true;
            }
            if (game_state_menu)
            {
                HandleEventsInMenu(event);
                character.come_back_time = 30;
            }
            else if(game_state_playing)
            {
                character.HandleInput(event);
            }
            else if(game_state_paused)
            {
                HandleEventsWhilePausing(event);
            }
        }

        if (game_state_menu)
        {
            if(Mix_PlayingMusic() == 0)Mix_PlayMusic(menuMusic,-1);
            if(Mix_PausedMusic() && Mix_PlayingMusic() )
            {
                Mix_HaltMusic();
            }
            loadMenu();
            UpdateMenu();
        }
        else if (game_state_playing)
        {
            if(Mix_PlayingMusic() == 0) Mix_PlayMusic(gameMusic,-1);
            if (Mix_PausedMusic()) Mix_ResumeMusic();
            if (character.x_pos == 0) Mix_HaltMusic();

            Map map_data = game_map_.GetMap();
            character.SetMapXY(map_data.start_x, map_data.start_y);
            character.Doplayer(map_data);

            game_map_.SetMap(map_data);
            backgr.renderTexture();
            game_map_.DrawMap();
            character.Show();
        } // Missing closing brace added here
        else if(game_state_paused)
        {
            LoadPauseScreen();
            if(Mix_PlayingMusic()) Mix_PauseMusic();
        }

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
