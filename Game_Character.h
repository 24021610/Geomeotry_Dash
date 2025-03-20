#ifndef GAME_CHARACTER_H_INCLUDED
#define GAME_CHARACTER_H_INCLUDED

#include "header.h"
#include "Menu.h"
#include <stdfix.h>

struct GameCharacter{
    SDL_Texture* texture;
    SDL_Rect rect;
    float x_val, y_val;
    float x_pos, y_pos;

    int width_frame, height_frame;

    Input input_type;
    int frame;
    int status;

    bool on_ground;
    bool win;
    bool original_state;
    bool riding_ship_state;
    bool reversal_state;
    bool rocket_state;

    int map_x_;
    int map_y_;

    int come_back_time;
    double rotation;


     GameCharacter()
    {
    texture = NULL;
    rect.w = 45;
    rect.h = 45;
    frame = 0;
	x_pos = 0;
	y_pos = 365;

	x_val = 0;
	y_val = 0;
	width_frame = 45;
	height_frame = 45;
	map_x_ = 0;
	map_y_ = 0;

	status = WALK_NONE;
	input_type.jump = 0;
	input_type.right = 0;
	on_ground = true;
	win = false;

	original_state = true;
	riding_ship_state = false;
	reversal_state = false;
	rocket_state = false;
	come_back_time = 0;
	rotation = 0;
    }

    void SetMapXY(const int map_x, const int map_y)
    {
        map_x_ = map_x;
        map_y_ = map_y;
    }

    void LoadImg(const char* filename)
    {
        SDL_Surface *surface = IMG_Load(filename);

        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface  -> format, 127, 127, 127));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        rect.w = surface ->w;
        rect.h = surface ->h;
        SDL_FreeSurface(surface);
        SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    }



    void Show()
    {
        UpdateImageofPlayer();
        int x = x_pos - map_x_;
        int y = y_pos - map_y_;

        SDL_Rect dest_original;
        dest_original.x = x;
        dest_original.y = y;
        dest_original.w = 45;
        dest_original.h = 45;

        SDL_Rect dest_other;
        dest_other.x = x;
        dest_other.y = y;
        dest_other.w = 60;
        dest_other.h = 60;

        SDL_Point center = {22 , 22};

        if (original_state)
        {
            if(!on_ground)
            {
            SDL_RenderCopyEx(renderer, texture, NULL, &dest_original, rotation, &center, SDL_FLIP_NONE);
            rotation += 40.58;
            if (rotation > 360) rotation = 0;
            }
            else
            {
            SDL_Point center = {22 , 22};
            if (rotation >0 && rotation < 90) SDL_RenderCopyEx(renderer, texture, NULL, &dest_original, 90, &center, SDL_FLIP_NONE);
            else if (rotation >=90 && rotation < 180) SDL_RenderCopyEx(renderer, texture, NULL, &dest_original, 180, &center, SDL_FLIP_NONE);
            else if (rotation >=180 && rotation < 270) SDL_RenderCopyEx(renderer, texture, NULL, &dest_original, 270, &center, SDL_FLIP_NONE);

            else SDL_RenderCopy(renderer, texture, NULL, &dest_original);
            }
        }
        else if (rocket_state)
        {
            if (input_type.jump == 1) SDL_RenderCopyEx(renderer, texture, NULL, &dest_other, -45, &center, SDL_FLIP_NONE);
            else SDL_RenderCopyEx(renderer, texture, NULL, &dest_other, 45, &center, SDL_FLIP_NONE);
        }

        else if(reversal_state)
        {
            if(!on_ground)
            {
            SDL_RenderCopyEx(renderer, texture, NULL, &dest_original, rotation, &center, SDL_FLIP_NONE);
            rotation -= 4.58;
            if (rotation < -360) rotation = 0;
            }
            else
            {
            SDL_Point center = {22 , 22};
            if (rotation < 0 && rotation > -90) SDL_RenderCopyEx(renderer, texture, NULL, &dest_original, -90, &center, SDL_FLIP_NONE);
            else if (rotation <= -90 && rotation > -180) SDL_RenderCopyEx(renderer, texture, NULL, &dest_original, -180, &center, SDL_FLIP_NONE);
            else if (rotation <= -180 && rotation > -270) SDL_RenderCopyEx(renderer, texture, NULL, &dest_original, -270, &center, SDL_FLIP_NONE);

            else SDL_RenderCopy(renderer, texture, NULL, &dest_original);
            }
        }
        else SDL_RenderCopy(renderer, texture, NULL, &dest_original);
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

                if (rocket_state)
                {
                    input_type.jump = (input_type.jump == 1 ? 0 : 1);
                }
                else input_type.jump = 1;
                break;


            case SDLK_ESCAPE:
                if(game_state_paused == false)
                {
                    game_state_paused = true;
                    game_state_playing = false;
                }
                break;
            }
        }
    }


    void Doplayer(Map &map_data)
    {
        if(come_back_time == 0)
        {

            if(original_state)
            {
                x_val += RUN_SPEED;
                if (x_val > MAX_RUN_SPEED) x_val = MAX_RUN_SPEED;

                y_val += GRAVITY;
                if (y_val > MAX_FALL_SPEED) y_val = MAX_FALL_SPEED;
                if (y_val < MIN_FALL_SPEED) y_val = MIN_FALL_SPEED;

                if (input_type.jump == 1)
                {
                    if(on_ground)
                    {
                        y_val = -60;
                        on_ground = false;
                        input_type.jump = 0;
                    }
                }
            }

            else if (reversal_state)
            {
                x_val += RUN_SPEED;
                if (x_val > 14.3) x_val = 14.3;

                y_val -= 5;

                if (y_val < MIN_FALL_SPEED) y_val = MIN_FALL_SPEED;

                if (input_type.jump == 1)
                {
                    if(on_ground)
                    {
                        y_val = 31.1;
                        on_ground = false;
                        input_type.jump = 0;
                    }
                }
            }

            else if (rocket_state)
            {
                x_val += RUN_SPEED;
                if (x_val > MAX_RUN_SPEED) x_val = MAX_RUN_SPEED;
                if (input_type.jump == 1)
                {
                    y_val = -15;

                }
                else if (input_type.jump == 0)
                {
                    y_val = 15;
                }
            }

            else if (riding_ship_state)
            {
                 x_val += RUN_SPEED;
                if (x_val > MAX_RUN_SPEED) x_val = MAX_RUN_SPEED;

                y_val += 5;
                if (y_val > MAX_FALL_SPEED) y_val = MAX_FALL_SPEED;
                if (y_val < MIN_FALL_SPEED) y_val = MIN_FALL_SPEED;

                if (input_type.jump == 1)
                {
                    if(on_ground)
                    {
                        y_val = -60;
                        input_type.jump = 0;
                    }
                }
            }



    Check_to_map(map_data);
    CenterEntityOnMap(map_data);
        }

        else
        {
            come_back_time -= 2;
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

                if ( (val1 >= RIDING_SHIP_MIN  && val1 <= RIDING_SHIP_MAX) || (val2 >= RIDING_SHIP_MIN  && val2 <= RIDING_SHIP_MAX))
                    {
                        original_state = false;
                        riding_ship_state = true;
                        reversal_state = false;
                        rocket_state = false;
                    }

                else if ( (val1 >= ORIGINAL_MIN  && val1 <=ORIGINAL_MAX) || (val2 >= ORIGINAL_MIN  && val2 <= ORIGINAL_MAX))
                    {
                        original_state = true;
                        riding_ship_state = false;
                        reversal_state = false;
                        rocket_state = false;
                    }

                else if ( (val1 >= REVERSAL_MIN  && val1 <= REVERSAL_MAX) || (val2 >= REVERSAL_MIN  && val2 <=REVERSAL_MAX) )
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = true;
                        rocket_state = false;
                    }

                else if ( (val1 >= ROCKET_MIN  && val1 <= ROCKET_MAX) || (val2 >= ROCKET_MIN  && val2 <=ROCKET_MAX) )
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = false;
                        rocket_state = true;
                    }

                else if ( val1 > 99   || val2 >99)
                    {
                        game_state_finish = true;
                        game_state_playing = false;
                    }


                else if(val1 > BLANK_TILE || val2 > BLANK_TILE)
                {
                    if( (val1 > 42 && val1 < 65) ||  (val2 > 42 && val1 < 65))
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

                if ( (val1 >= RIDING_SHIP_MIN  && val1 <= RIDING_SHIP_MAX) || (val2 >= RIDING_SHIP_MIN  && val2 <= RIDING_SHIP_MAX))
                    {
                        original_state = false;
                        riding_ship_state = true;
                        reversal_state = false;
                        rocket_state = false;
                    }

                else if ( (val1 >= ORIGINAL_MIN && val1 <= ORIGINAL_MAX) || (val2 >= ORIGINAL_MIN && val2 <= ORIGINAL_MAX))
                    {
                        original_state = true;
                        riding_ship_state = false;
                        reversal_state = false;
                        rocket_state = false;
                    }

                 else if ( (val1 >= REVERSAL_MIN  && val1 <= REVERSAL_MAX) || (val2 >= REVERSAL_MIN  && val2 <= REVERSAL_MAX))
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = true;
                        rocket_state = false;
                    }

                else if ( (val1 >= ROCKET_MIN  && val1 <= ROCKET_MAX) || (val2 >= ROCKET_MIN  && val2 <= ROCKET_MAX))
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = false;
                        rocket_state = true;
                    }
                else if ( val1 > 99   || val2 >99)
                    {
                        game_state_finish = true;
                    }

                else if (val1 > BLANK_TILE || val2 > BLANK_TILE)
                {
                    if( (val1 > 42 && val1 < 65) ||  (val2 > 42 && val1 < 65))
                    {
                        come_back_time = 30;
                        original_state = true;
                        reversal_state = false;
                        riding_ship_state = false;
                        rocket_state = false;

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

				if ( (val1 >= RIDING_SHIP_MIN  && val1 <= RIDING_SHIP_MAX) || (val2 >= RIDING_SHIP_MIN  && val2 <= RIDING_SHIP_MAX) )
                    {
                        original_state = false;
                        riding_ship_state = true;
                        reversal_state = false;
                        rocket_state = false;
                    }

                else if ( (val1 >= REVERSAL_MIN  && val1 <= REVERSAL_MAX) || (val2 >= REVERSAL_MIN && val2 <= REVERSAL_MAX))
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = true;
                        rocket_state = false;
                    }

                else if ( (val1 >= ORIGINAL_MIN  && val1 <= ORIGINAL_MAX) || (val2 >= ORIGINAL_MIN  && val2 <= ORIGINAL_MAX))
                    {
                        original_state = true;
                        riding_ship_state = false;
                        reversal_state = false;
                        rocket_state = false;
                    }

                else if ( (val1 >= ROCKET_MIN  && val1 <= ROCKET_MAX) || (val2 >= ROCKET_MIN  && val2 <= ROCKET_MAX))
                    {
                        original_state = false;
                        riding_ship_state = false;
                        reversal_state = false;
                        rocket_state = true;
                    }

                 else if ( val1 > 99   || val2 >99)
                    {
                        game_state_finish = true;
                    }

				else if (val1 > BLANK_TILE || val2 > BLANK_TILE)
                    {
                        if( (val1 > 42 && val1 < 65) ||  (val2 > 42 && val1 < 65))
                        {
                        come_back_time = 30;
                        original_state = true;
                        reversal_state = false;
                        riding_ship_state = false;
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
		if (original_state)
		{
			LoadImg("Resources/model.jpg");
		}
		else if (riding_ship_state)
		{
			LoadImg("Resources/model2.png");
		}

		else if (reversal_state)
		{
			LoadImg("Resources/model3.png");
		}

		else if (rocket_state)
		{
			LoadImg("Resources/model4.png");
		}
}

};

#endif // GAME_CHARACTER_H_INCLUDED
