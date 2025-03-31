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


    Gameobject backgr1;
    Gameobject backgr2;
    Gameobject backgr3;
    backgr3.loadTexture("Resources/background3.png");
    backgr1.loadTexture("Resources/background1.png");
    backgr2.loadTexture("Resources/background2.png");


    TTF_Font *font = loadFont("Resources/font.ttf",60);

    GameMap game_map_;
    game_map_.LoadMap("map1.txt");
    game_map_.LoadTiles();

    Timer timer;
    vector<int> scores = readHighScores();
    int i=0;

    bool is_quit = false;
    SDL_Event event;
    while (!is_quit)
    {

        timer.start(); //1 vong while chay 1 frame

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
                HandleEventsWhilePausing(event, character.come_back_time, character.death_count);
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

            Map current_map = game_map_.GetMap();
            character.SetMapXY(current_map.start_x, current_map.start_y); // gan gia tri mapx mapy hien tai dang co
            character.Doplayer(current_map); // di chuyen nhan vat

            game_map_.SetMap(current_map); // renew map de update cho frame sau
            if(i<=5)
            {
                backgr1.renderTexture();
                i++;
            }
            else if(i<=10)
            {
                backgr2.renderTexture();
                i++;
            }
            else if(i<=15)
            {
                backgr3.renderTexture();
                i++;
                if(i==15) i =0;
            }
            game_map_.DrawMap(); //ve map
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

        int bayh = timer.Get_Ticks();
        int one_frame = 1000/FRAME_PER_SECOND; //tgian chay 1 frame

        if(bayh < one_frame) //chay nhanh hon thoi gian du tinh
        {
            int delay = one_frame - bayh;
            SDL_Delay(delay); // delay thoi gian du tinh do de chay dong deu
        }
    }
}
