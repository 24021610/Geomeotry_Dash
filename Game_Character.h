#ifndef GAME_CHARACTER_H_INCLUDED
#define GAME_CHARACTER_H_INCLUDED

#include "header.h"
#include <stdfix.h>

struct GameCharacter{
    Gameobject character;
    float x_val, y_val;
    float x_pos, y_pos;

    int width_frame, height_frame;
    SDL_Rect  frame_clip[4];

    Input input_type;
    int frame_;
    int status;




    frame = 0;
	x_pos = 32;
	y_pos = 380;

	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	status = WALK_NONE;
	input_type_.jump = 0;
	input_type_.right = 0;

    void LoadImg(const char* filename)
    {
        character.texture =  IMG_LoadTexture(renderer, filename);
        width_frame = character.rect.w;
        height_frame = character.rect.h;
    }


    void Show()
    {
        if (status == WalkType)
    }


    void HandleInput(SDL_Event event)
    {
        status = WALK_RIGHT;
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                input_type.jump_ = 1;
            }
        }
    }




};

#endif // GAME_CHARACTER_H_INCLUDED
