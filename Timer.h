#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "header.h"

struct Timer{

    int start_tick;

    bool is_started;

    Timer()
    {
        start_tick = 0;
        is_started = false;
    }

    void start()
    {
        is_started = true;
        start_tick = SDL_GetTicks();
    }

    int Get_Ticks()
    {
        return SDL_GetTicks() - start_tick;
        return 0;
    }

};

#endif // TIMER_H_INCLUDED
