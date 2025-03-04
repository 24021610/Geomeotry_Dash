#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "header.h"
#include "Game_object.h"

bool game_state_playing = false;
bool game_state_paused = false;
bool game_state_menu = true;


Gameobject background;

Gameobject menu;
Gameobject play_button;
Gameobject pause_button;
Gameobject finish_screen;

void loadMenu()
{
    menu.SetRect(0,0);
    menu.loadTexturewithoutQuerying("Resources/menu.jpg");
    menu.renderTexture();
}

void LoadPauseButton()
{
    pause_button.SetRect(900, 30);
}

void LoadStartButton()
{
    play_button.SetRect(475, 200);
    play_button.loadTexturewithoutQuerying("Resources/play_button.png");
    play_button.renderTexture();
}

void HandleEventsInMenu(SDL_Event &event)
{
     if (event.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);


            if ( (x > 480 && x<690 && y>200 && y<410) )
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
            if (x > 480 && x<690 && y>200 && y<410)
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

    if (x > 480 && x < 690 && y > 200 && y < 410) {
        LoadStartButton();
    } else {
        SDL_DestroyTexture(play_button.texture);
        loadMenu();
    }
}


#endif // MENU_H_INCLUDED
