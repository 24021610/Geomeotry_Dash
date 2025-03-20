#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "header.h"
#include "Game_object.h"

struct Bullet : Gameobject{

    int x_value;
    int y_value;
    bool is_move;


    Bullet()
    {
        x_value=0;
        y_value=0;
        is_move=0;
    }

    void set_x_value(const int &x){x_value = x;}
    void set_y_value(const int &y){y_value = y;}
    int get_y_value() const {return y_value;}
    int get_x_value() const {return x_value;}
    void set_ismove(const bool &ismove){is_move = ismove;}
    bool get_is_move_value() const {return is_move;}



    void HandleBullet(const int& x_border, const int &y_border)
    {
        rect.x += x_value;
        if(rect.x > x_border)
        {
            is_move = false;
        }
    }

};

#endif // BULLET_H_INCLUDED
