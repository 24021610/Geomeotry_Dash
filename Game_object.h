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
            texture = IMG_LoadTexture(renderer, filename);
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
