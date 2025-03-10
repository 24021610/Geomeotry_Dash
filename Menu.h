#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "header.h"
#include "Game_object.h"

bool game_state_playing = false;
bool game_state_paused = false;
bool game_state_menu = true;
bool game_state_finish = false;



Gameobject background;

Gameobject menu;
Gameobject play_button;
Gameobject pause_button;
Gameobject finish_screen;

void loadMenu()
{
    menu.SetRect(0,0);
    menu.loadTexture("Resources/menu.png");
    menu.renderTexture();
}



void LoadPauseButton()
{
    pause_button.SetRect(900, 30);
}

void LoadStartButton()
{
    play_button.SetRect(420, 160);
    play_button.loadTexturewithoutQuerying("Resources/play_button.png");
    play_button.renderTexture();
}

void LoadFinishScreen()
{
    finish_screen.SetRect(100, 100);
    finish_screen.loadTexturewithoutQuerying("Resources/finish_screen.png");
    finish_screen.renderTexture();
}

void HandleEventsInMenu(SDL_Event &event)
{
     if (event.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);


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
                }
            }
        }
}

void UpdateMenu()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

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



#endif // MENU_H_INCLUDED
