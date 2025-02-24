#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED

#include "header.h"
#include "stdfix.h"
struct Gameobject{
    SDL_Texture* texture;
    SDL_Rect rect;

    Gameobject() = default;

   void loadTexture(const char *filename)
   {
        SDL_Surface *surface = IMG_Load(filename);
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface -> format, 255, 255, 254));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load Texture: %s", IMG_GetError());
   }

   void SetRect(const int &x, const int &y)
    {
        rect.x = x;
        rect.y = y;
    }

    void renderTexture()
    {
        SDL_Rect dest = {rect.x, rect.y, 60, 60};

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

};

#endif // GAME_OBJECT_H_INCLUDED
