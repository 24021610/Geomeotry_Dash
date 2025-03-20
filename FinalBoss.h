#ifndef FINALBOSS_H_INCLUDED
#define FINALBOSS_H_INCLUDED


#include "header.h"
#include "Game_object.h"


struct ThreatsObject : Gameobject
{
    int frame_;
    int width_frame_;
    int height_frame_;
    float x_pos;
    float y_pos;
    int map_x;
    int map_y;
    float x_val;
    float y_val;

    ThreatsObject()
    {
    frame_ = 0;
	x_pos = 0;
	y_pos = 365;

	x_val = 0;
	y_val = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	map_x = 0;
	map_y = 0;
    }


    void set_x_value(const int &x){x_val = x;}
    void set_y_value(const int &y){y_val = y;}

    void set_x_pos(const float &x){x_pos = x;}
    void set_y_pos(const float &y){y_pos = y;}

    float get_y_pos() const {return y_pos;}
    float get_x_pos() const {return x_pos;}

    void SetMapXY(const int map_x_, const int map_y_)
    {
        map_x = map_x_;
        map_y = map_y_;
    }

    bool loadIMG()
    {

    }

    void Show()
    {

    }

    int get_width_frame()const {return width_frame_;}
    int get_height_frame() const{return height_frame_;}

    void DoBoss(Map& map)
    {

    }




};


#endif // FINALBOSS_H_INCLUDED
