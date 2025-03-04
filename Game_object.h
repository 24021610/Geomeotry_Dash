#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include "header.h"
#include "stdfix.h"
struct Gameobject{
    SDL_Texture* texture;
    SDL_Rect rect;

    Gameobject()
    {
        texture = NULL;
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
    }

   void loadTexture(const char *filename)
   {
        SDL_Surface *surface = IMG_Load(filename);

        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface  -> format, 255, 255, 255));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.w = surface ->w;
        rect.h = surface ->h;
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
   }

   void loadTexture(const char *filename)
   {
        SDL_Surface *surface = IMG_Load(filename);

        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface  -> format, 255, 255, 255));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.w = surface ->w;
        rect.h = surface ->h;
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
   }

   void loadBackground()
   {
       SDL_Texture* texture = IMG_LoadTexture(renderer, "Resources/background.png");
   }

   void SetRect(const int &x, const int &y)
    {
        rect.x = x;
        rect.y = y;
    }

    SDL_Rect GetRect()
    {
        return rect;
    }

    SDL_Texture* getTexture()
    {
        return texture;
    }

    void renderTexture()
    {
        SDL_Rect dest = {rect.x, rect.y, rect.w, rect.h};
        SDL_RenderCopy(renderer, texture, nullptr, &dest);
    }

};

#endif // GAME_OBJECT_H_INCLUDED
