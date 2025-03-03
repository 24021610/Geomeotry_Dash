#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "header.h"

struct Timer{

    int start_tick;
    int paused_tick;

    bool is_paused;
    bool is_started;

    Timer()
    {
        start_tick = 0;
        paused_tick = 0;
        is_paused = false;
        is_started = false;
    }

    void start()
    {
        is_started = true;
        is_paused = false;
        start_tick = SDL_GetTicks();
    }

    void stop()
    {
        is_started = false;
        is_started = false;
    }

    void paused()
    {
        if(is_started == true && is_paused == false)
        {
            is_paused == true;
            paused_tick = SDL_GetTicks() - start_tick;
        }
    }

    void unpaused()
    {
        if(is_paused)
        {
            is_paused == false;
            start_tick = SDL_GetTicks() - paused_tick;
            paused_tick = 0;
        }
    }

    int Get_Ticks()
    {
        if(is_started)
        {
            if(is_paused) return paused_tick;
        }
        else return SDL_GetTicks() - start_tick;
        return 0;
    }

    bool is_started_()
    {
        return is_started;
    }

    bool is_paused_()
    {
        return is_paused;
    }
};

#endif // TIMER_H_INCLUDED
