#ifndef GAME_CHARACTER_H_INCLUDED
#define GAME_CHARACTER_H_INCLUDED

#include "header.h"
#include <stdfix.h>

struct GameCharacter{
    SDL_Texture* texture;
    SDL_Rect rect;
    float x_val, y_val;
    float x_pos, y_pos;

    int width_frame, height_frame;
    SDL_Rect  frame_clip[4];

    Input input_type;
    int frame;
    int status;
    bool on_ground;



    GameCharacter()
    {
    rect.w = 60;
    rect.h = 60;
    frame = 0;
	x_pos = 32;
	y_pos = 380;

	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	status = WALK_NONE;
	input_type.jump = 0;
	input_type.right = 0;
	on_ground = false;
    }

    void LoadImg(const char* filename)
    {
        texture =  IMG_LoadTexture(renderer, filename);
        width_frame = rect.w;
        height_frame = rect.h;
    }

    void Show()
    {
        rect.x = x_pos;
        rect.y = y_pos;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void HandleInput(SDL_Event event)
    {
        status = WALK_RIGHT;
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                input_type.jump = 1;
            }
        }
    }


    void Doplayer(Map &map_data)
    {
        x_val = 0;
        y_val += GRAVITY;
        if (y_val > MAX_FALL_SPEED) y_val = MAX_FALL_SPEED;

        if(input_type.jump == 1)
        {

        }
    }


    void Check_to_map(Map& map_data)
    {
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;

        //check ngang

        int height_min = (height_frame > OBJECT_SIZE ? height_frame : OBJECT_SIZE);
        x1 = (x_pos + x_val) / OBJECT_SIZE;
        x2 = (x_pos + x_val + width_frame-1) / OBJECT_SIZE;

        y1 = y_pos / OBJECT_SIZE;
        y2 = (y_pos + height_min - 1) / OBJECT_SIZE;

        if(x1 >= 0&& x2 < GAME_MAP_X && y1 >=0 && y2 < GAME_MAP_Y)
        {
            if (x_val > 0)
            {
                int val1 = map_data.tile[y1][x2];
                int val2 = map_data.tile[y2][x2];

                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                        x_pos = x2* OBJECT_SIZE;
                        x_pos -= width_frame+1;
                }
            }
        }


        //check doc
        int width_min = min(width_frame, OBJECT_SIZE);
        x1 = x_pos / OBJECT_SIZE;
        x2 = (x_pos + width_min) / OBJECT_SIZE;

        y1 = (y_pos + x_val) / OBJECT_SIZE;
        y2 = (y_pos + x_val + height_frame-1) / OBJECT_SIZE;

        if(x1 >= 0&& x2 < GAME_MAP_X && y1 >=0 && y2 < GAME_MAP_Y)
        {
            if (y_val > 0)
            {
                int val1 = map_data.tile[y2][x1];
                int val2 = map_data.tile[y2][x2];

                if(val1= BLANK_TILE || val2 != BLANK_TILE)
                {
                        y_pos = y2 * OBJECT_SIZE;
                        y_pos -= height_frame+1;
                        y_val = 0;
                        on_ground = true;
                }
            }

            else if(y_val >0)
            {
                int val1 = map_data.tile[y1][x1];
				int val2 = map_data.tile[y1][x2];

				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos = (y1+1)*OBJECT_SIZE;
                    y_val = 0;
                }
            }
        }

        x_pos += x_val;
        y_pos += y_val;

        if(x_pos+width_frame > map_data.max_x) x_pos = map_data.max_x - width_frame - 1;

    }


};

#endif // GAME_CHARACTER_H_INCLUDED
