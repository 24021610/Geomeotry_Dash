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

    int map_x_;
    int map_y_;

    int come_back_time;



    GameCharacter()
    {
    texture = NULL;
    rect.w = 60;
    rect.h = 60;
    frame = 0;
	x_pos = 0;
	y_pos = 360;

	x_val = 0;
	y_val = 0;
	width_frame = 60;
	height_frame = 60;
	map_x_ = 0;
	map_y_ = 0;
	status = WALK_NONE;
	input_type.jump = 0;
	input_type.right = 0;
	on_ground = false;
	come_back_time = 0;
    }

    void SetMapXY(const int map_x, const int map_y)
    {
        map_x_ = map_x;
        map_y_ = map_y;
    }

    void LoadImg(const char* filename)
    {
        texture =  IMG_LoadTexture(renderer, filename);
        if (texture == nullptr) SDL_Quit();
        width_frame = rect.w;
        height_frame = rect.h;
    }

    void Show()
    {
        SDL_Rect dest;
        dest.x = x_pos - map_x_;
        dest.y = y_pos - map_y_;
        dest.w = 60;
        dest.h = 60;
        SDL_RenderCopy(renderer, texture, NULL, &dest);
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
        x_val += RUN_SPEED;
        if (x_val > MAX_RUN_SPEED) x_val = MAX_RUN_SPEED;


        y_val += 5 ;
        if (y_val > MAX_FALL_SPEED) y_val = MAX_FALL_SPEED;

        Check_to_map(map_data);

    if(input_type.jump == 1)
    {
        if(on_ground == true)
        {
        y_val = -25;
        on_ground = false;
        input_type.jump = 0;
        }
    }

    Check_to_map(map_data);
    CenterEntityOnMap(map_data);
}

    void Check_to_map(Map& map_data)
    {
        int x1 = 0, x2 = 0;
        int y1 = 0, y2 = 0;

        //check ngang

        int height_min = min(height_frame , OBJECT_SIZE) ;
        x1 = (x_pos + x_val) / OBJECT_SIZE;
        x2 = (x_pos + x_val + width_frame-1) / OBJECT_SIZE;

        y1 = y_pos / OBJECT_SIZE;
        y2 = (y_pos + height_min - 1) / OBJECT_SIZE;

        if(x1 >= 0 && x2 < GAME_MAP_X && y1 >=0 && y2 < GAME_MAP_Y)
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

        y1 = (y_pos + y_val) / OBJECT_SIZE;
        y2 = (y_pos + y_val + height_frame-1) / OBJECT_SIZE;

        if(x1 >= 0 && x2 < GAME_MAP_X && y1 >=0 && y2 < GAME_MAP_Y)
        {
            if (y_val > 0)
            {
                int val1 = map_data.tile[y2][x1];
                int val2 = map_data.tile[y2][x2];

                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                        y_pos = y2 * OBJECT_SIZE;
                        y_pos -= (height_frame+1);
                        y_val = 0;
                        on_ground = true;
                }
            }

            else if(y_val <= 0)
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


    }

 void CenterEntityOnMap(Map& map_data)
{

	map_data.start_x = x_pos - (SCREEN_WIDTH / 3.4);

	if (map_data.start_x < 0)
	{
		map_data.start_x = 0;
	}
	else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
	{
		map_data.start_x = map_data.max_x - SCREEN_WIDTH;
	}
}

};

#endif // GAME_CHARACTER_H_INCLUDED
