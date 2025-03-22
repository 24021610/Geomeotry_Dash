#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "header.h"


    TTF_Font* loadFont(const char* path, int size)
    {
    TTF_Font* gFont = TTF_OpenFont( path, size );
    }


    void renderText(const char* text, int value, TTF_Font* font)
    {
        string finalText = string(text) + " " + to_string(value);
        SDL_Color color = {255, 255, 0, 0};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, finalText.c_str() ,color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface( textSurface );
        SDL_Rect rect = {20, 20, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }

    vector<int> readHighScores()
    {
        vector<int> scores;
        ifstream file(HIGHSCORE_FILE);
        int score;
        while (file >> score)
        {
            scores.push_back(score);
        }
        file.close();
        return scores;
    }

    void writeHighScores(const vector<int>& scores)
    {
        ofstream file(HIGHSCORE_FILE);
        for (int score : scores) {
            file << score << endl;
        }
        file.close();
    }

    void UpdateHighScore(int come_back_time, vector<int>& scores)
    {
        static int highscore = SDL_GetTicks();

        if(come_back_time == 0)
        {
            highscore = SDL_GetTicks();
        }

        if(come_back_time==30)
        {
            int alltime_highscore = SDL_GetTicks() - highscore;
            if (scores.empty() || alltime_highscore > *max_element(scores.begin(), scores.end())) {
            scores.push_back(alltime_highscore);
            sort(scores.begin(), scores.end());
            writeHighScores(scores);
        }
    }
    }


#endif // FONT_H_INCLUDED
