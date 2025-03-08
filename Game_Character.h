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
    SDL_Rect frame_clip[7];

    Input input_type;
    int frame;
    int status;

    bool on_ground;
    bool alive;
    bool original_state;
    bool riding_ship_state;
    bool reversal_state;

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
	width_frame = 40;
	height_frame = 40;
	map_x_ = 0;
	map_y_ = 0;
	status = WALK_NONE;
	input_type.jump = 0;
	input_type.right = 0;
	on_ground = true;
	alive = true;
	original_state = true;
	riding_ship_state = false;
	reversal_state = false;
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
        UpdateImageofPlayer();
        SDL_Rect dest;
        dest.x = x_pos - map_x_;
        dest.y = y_pos - map_y_;
        dest.w = 60;
        dest.h = 60;
        SDL_RenderCopy(renderer, texture, NULL, &dest);

    }

    void HandleInput(SDL_Event event)
    {
        UpdateImageofPlayer();
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
        if(come_back_time == 0)
        {
        x_val += RUN_SPEED;
        if (x_val > MAX_RUN_SPEED) x_val = MAX_RUN_SPEED;


        (reversal_state == true? y_val -= 5 : y_val += 5);
        if (y_val > MAX_FALL_SPEED) y_val = MAX_FALL_SPEED;

        if (y_val < MIN_FALL_SPEED) y_val = MIN_FALL_SPEED;

        Check_to_map(map_data);

    if(input_type.jump == 1 && original_state == true)
        {
            if(on_ground == true)
            {
                y_val = -60;
                on_ground = false;
                input_type.jump = 0;
            }
        }

        else if (input_type.jump == 1 && riding_ship_state == true)
            {
                y_val = -60;
                on_ground = false;
                input_type.jump = 0;
            }

        else if (input_type.jump == 1 && reversal_state == true)
            if(on_ground == true)
            {
                y_val = 60;
                on_ground = false;
                input_type.jump = 0;
            }

    Check_to_map(map_data);
    CenterEntityOnMap(map_data);
        }

        else
        {
            come_back_time--;
            if (come_back_time == 0)
            {
                x_pos = 0;
                y_pos = 380;
                y_val = 0;
                x_val = 0;
            }
        }
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

                if (val1 == 2 || val2 == 2)
                    {
                        original_state = false;
                        riding_ship_state = true;
                        reversal_state = false;
                    }

                else if ( (val1 >= 5  && val1 <=7) || (val2 >= 5  && val2 <=7))
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = true;
                    }


                else if(val1 > BLANK_TILE || val2 > BLANK_TILE)
                {
                    if( (val1 > 42 && val1 < 60) ||  (val2 > 42 && val1 < 60))
                    {
                        come_back_time = 30;
                        original_state = true;
                        reversal_state = false;

                    }
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

                if (val1 == 2 || val2 == 2)
                    {
                        original_state = false;
                        riding_ship_state = true;
                        reversal_state = false;
                    }

                 else if ( (val1 >= 5  && val1 <=7) || (val2 >= 5  && val2 <=7))
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = true;
                    }

                else if (val1 > BLANK_TILE || val2 > BLANK_TILE)
                {
                    if( (val1 > 42 && val1 < 60) ||  (val2 > 42 && val1 < 60))
                    {
                        come_back_time = 30;
                        original_state = true;
                        reversal_state = false;

                    }
                        y_pos = (y2 * OBJECT_SIZE);
                        y_pos -= (height_frame+1);
                        y_val = 0;
                        on_ground = true;
                }
            }

            else if(y_val <= 0)
            {
                int val1 = map_data.tile[y1][x1];
				int val2 = map_data.tile[y1][x2];

				if (val1 == 2 || val2 == 2)
                    {
                        original_state = false;
                        riding_ship_state = true;
                        reversal_state = false;
                    }

                else if ( (val1 >= 5  && val1 <=7) || (val2 >= 5  && val2 <=7))
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = true;
                    }

				else

                    if (val1 > BLANK_TILE || val2 > BLANK_TILE)
                    {
                        if( (val1 > 42 && val1 < 60) ||  (val2 > 42 && val1 < 60))
                    {
                        come_back_time = 30;
                        original_state = true;
                        reversal_state = false;
                    }

                        y_pos = (y1+1)*OBJECT_SIZE;
                        y_val = 0;
                        on_ground = true;
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
void UpdateImageofPlayer()
{
		if (original_state == 1)
		{
			LoadImg("Resources/model.jpg");
		}
		else if (riding_ship_state == 1)
		{
			LoadImg("Resources/model2.png");
		}
}

};

#endif // GAME_CHARACTER_H_INCLUDED
