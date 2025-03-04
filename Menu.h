#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "header.h"
#include "Game_object.h"

bool game_state_playing = false;
bool game_state_paused = false;
bool game_state_menu = true;
bool current_game_state;

Gameobject background;

Gameobject menu;
Gameobject play_button;
Gameobject pause_button;
Gameobject finish_screen;

void loadMenu()
{
    menu.loadTexture ()
}

void LoadPauseButton()
{
    pause_button.loadTexture("Resources/pause.png");
    pause_button.SetRect(900, 30);
}

void LoadStartButton()
{
    play_button.loadTexture("Resources/play.png");
    play_button.SetRect(900, 30);
    play_button.renderTexture();
}

void HandleEventsInMenu(SDL_Event &event)
{
     if (event.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {

            if (x > 160 && x<320 && y>160 && y<320)
            {
                LoadStartButton();
            }
            else
            {
                SDL_DestroyTexture(play_button.texture);
            }
        }

}




#endif // MENU_H_INCLUDED
