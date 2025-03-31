#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "header.h"
#include "Game_object.h"

bool game_state_playing = false;
bool game_state_paused = false;
bool game_state_menu = true;
bool game_state_finish = false;
bool game_state_boss = false;



Gameobject background;

Gameobject menu;
Gameobject blank;
Gameobject play_button;
Gameobject pause_screen;
Gameobject finish_screen;

void loadMenu()
{
    menu.SetRect(0,0);
    menu.loadTexture("Resources/menu.png");
    menu.renderTexture();
}


void LoadPauseScreen()
{
    pause_screen.SetRect(PAUSE_SCREEN_X, PAUSE_SCREEN_Y);
    pause_screen.loadTexture("Resources/pause_screen.png");
    pause_screen.renderTexture();
}

void LoadStartButton()
{
    play_button.SetRect(420, 160);
    play_button.loadTexture("Resources/play_button.png");
    play_button.renderTexture();
}

void LoadFinishScreen()
{
    finish_screen.SetRect(100, 100);
    finish_screen.loadTexture("Resources/finish_screen.png");
    finish_screen.renderTexture();
}

void HandleEventsInMenu(SDL_Event &event)
{
     if (event.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if(game_state_menu)
            {
            if ( (x > 440 && x < 660 && y > 160 && y < 370) )
            {
                LoadStartButton();
            }
            else
            {
                SDL_DestroyTexture(play_button.texture);
                loadMenu();
            }
            }
        }

        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);

            if (game_state_menu)
            {
            if (x > 440 && x < 660 && y > 160 && y < 370)
                {
                game_state_playing = true;
                game_state_menu = false;
                game_state_paused = false;
                }
            }
        }

        else if(game_state_paused==true && game_state_playing==false) SDL_DestroyTexture(menu.texture);
}

void HandleEventsWhilePausing(SDL_Event &event, int &value, int &reset)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
    {
        game_state_paused = false;
        game_state_playing = true;
        game_state_menu = false;
    }

    else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);


            if ( (x > PAUSE_SCREEN_X+450 && x < PAUSE_SCREEN_X+620 && y > PAUSE_SCREEN_Y+280 && y < PAUSE_SCREEN_Y+460) )
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    game_state_menu=true;
                    reset=0;
                    game_state_playing = false;
                    game_state_paused=false;
                    SDL_DestroyTexture(pause_screen.texture);
                }
            }

            else if ( (x > PAUSE_SCREEN_X+680 && x < PAUSE_SCREEN_X+870 && y > PAUSE_SCREEN_Y+280 && y < PAUSE_SCREEN_Y+450) )
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    game_state_menu=false;
                    game_state_playing = true;
                    game_state_paused=false;
                    value = 30;
                    SDL_DestroyTexture(pause_screen.texture);
                }
            }
        }
}

void HandleEventsWhileFinishing(SDL_Event &event, int &value)
{
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
    {
        game_state_paused = false;
        game_state_playing = false;
        game_state_menu = true;

    }

    else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);


            if ( (x > FINISH_SCREEN_X+150 && x < FINISH_SCREEN_X+290 && y > FINISH_SCREEN_Y+320 && y < FINISH_SCREEN_Y+400) )
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    game_state_menu=false;
                    game_state_playing = true;
                    game_state_paused=false;
                    value = 30;
                    SDL_DestroyTexture(finish_screen.texture);
                }
            }

            else if ( (x > FINISH_SCREEN_X+600 && x < FINISH_SCREEN_X+720 && y > FINISH_SCREEN_Y+320 && y < FINISH_SCREEN_Y+400) )
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    game_state_menu=true;
                    game_state_playing = false;
                    game_state_paused=false;
                    Mix_PauseMusic();
                    SDL_DestroyTexture(finish_screen.texture);
                }
            }
        }
}
void UpdateMenu()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    if(game_state_menu)
    {
        if (x > 440 && x < 660 && y > 160 && y < 370)
        {
            LoadStartButton();
        }
        else
        {
            SDL_DestroyTexture(play_button.texture);
            loadMenu();
        }
    }
    else if(game_state_paused==true && game_state_playing==false) SDL_DestroyTexture(menu.texture);
}

void quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}



#endif // MENU_H_INCLUDED
