#include "header.h"
#include "Game_object.h"
#include "Gamemap.h"
#include "Game_Character.h"
#include "Timer.h"
#include "Menu.h"
#include "Font.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 0;
    if (TTF_Init() == -1) return 0;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return 0;

    Mix_Music *gameMusic = Mix_LoadMUS("Resources/ingame.mp3");
    Mix_Music *menuMusic = Mix_LoadMUS("Resources/menu.mp3");

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    GameCharacter character;
    character.LoadImg("Resources/model.jpg");


    Gameobject backgr;
    backgr.loadTexture("Resources/background.png");

    TTF_Font *font = loadFont("Resources/font.ttf",60);

    GameMap game_map_;
    game_map_.LoadMap("map1.txt");
    game_map_.LoadTiles();

    Timer timer;
    vector<int> scores = readHighScores();

    bool is_quit = false;
    SDL_Event event;
    while (!is_quit)
    {
        loadBlankScreen();
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
                HandleEventsWhilePausing(event, character.come_back_time);
            }
            else if(game_state_finish)
            {
                HandleEventsWhileFinishing(event,character.come_back_time);
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
            character.SetMapXY(map_data.start_x, map_data.start_y); // gan gia tri mapx mapy hien tai dang co
            character.Doplayer(map_data); // di chuyen nhan vat

            game_map_.SetMap(map_data); // renew map de update cho frame sau
            backgr.renderTexture(); // render background dau tien, sau do ve map
            game_map_.DrawMap();
            character.Show();
            renderText("Attempt", character.death_count, font); //render attempt cuoi cung de khong bi ghi de
            UpdateHighScore(character.come_back_time, scores); //update highscore vao file highscocres.txt sau moi lan choi
        }

        else if(game_state_paused)
        {
            LoadPauseScreen();
            if(Mix_PlayingMusic()) Mix_PauseMusic();
        }

        else if(game_state_finish)
        {
            game_map_.DrawMap();
            LoadFinishScreen();
        }

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        int real_time = timer.Get_Ticks();
        int one_frame = 1000/FRAME_PER_SECOND;

        if(real_time < one_frame)
        {
            int delay = one_frame - real_time;
            SDL_Delay(delay);
        }
    }
}
