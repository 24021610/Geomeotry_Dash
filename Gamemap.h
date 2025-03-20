#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include <iostream>
#include "header.h"
#include "Game_object.h"

#define GAME_MAP_X 495
#define GAME_MAP_Y 15
#define OBJECT_SIZE 40

using namespace std;

struct Map{
    int start_x, start_y, max_x, max_y;

    int tile[GAME_MAP_Y][GAME_MAP_X];
    char* filename;
};

struct GameMap{
    Gameobject tile_mat[MAX_NUMBER_OF_TILES];
    Map game_map;
    FILE* fp = NULL;

    Map GetMap()
    {
        return game_map;
    }

    void SetMap(Map& map_data)
    {
        game_map = map_data;
    }

    void LoadMap(char* filename){
        fopen_s(&fp, filename, "rb");
        if(fp == NULL) return;

        game_map.max_x = 0;
        game_map.max_y = 0;

    for (int i=0; i< GAME_MAP_Y; i++)
        {
        for(int j = 0; j<GAME_MAP_X; j++)
            {
            fscanf(fp, "%d", &game_map.tile[i][j]);
            int val = game_map.tile[i][j];
                if(val >0){
                    if (j > game_map.max_x) game_map.max_x = j;
                    if (i > game_map.max_y) game_map.max_y = i;
                         }
            }
        }
    game_map.max_x = (game_map.max_x + 1) * OBJECT_SIZE;
	game_map.max_y = (game_map.max_y + 1) * OBJECT_SIZE;

	game_map.start_x = 0;
	game_map.start_y = 0;


        char* dat = filename;
        game_map.filename = dat;
        fclose(fp);

    }

    void LoadTiles ()
    {
        FILE* fp = NULL;
        char file_image[MAX_NUMBER_OF_TILES];

        for(int i=0; i< MAX_NUMBER_OF_TILES; i++)
        {
            sprintf_s(file_image, "Resources/%d.png", i);

            fopen_s(&fp, file_image,"rb");
            if(fp == NULL) continue;
            fclose(fp);
            tile_mat[i].loadTexture(file_image);
        }
    }

    void DrawMap()
    {
        int x1 = 0;
        int x2 = 0;

        int y1 = 0;
        int y2 = 0;


        int map_x = 0;
        int map_y = 0;

        map_x = game_map.start_x / OBJECT_SIZE;
        x1 = (game_map.start_x % OBJECT_SIZE) *-1;
        x2 = x1 + SCREEN_WIDTH +(x1==0? 0:OBJECT_SIZE);

        map_y = game_map.start_y / OBJECT_SIZE;
        y1 = (game_map.start_y % OBJECT_SIZE) *-1;
        y2 = y1+ SCREEN_HEIGHT +(y1==0? 0:OBJECT_SIZE);

        for(int i = y1; i <y2; i+= OBJECT_SIZE)
        {
             map_x = game_map.start_x/OBJECT_SIZE;

            for(int j = x1; j< x2; j+=OBJECT_SIZE)
            {
                int val = game_map.tile[map_y][map_x];
                if(val>0)
                {
                    tile_mat[val].SetRect(j,i);
                    tile_mat[val].renderTexture();
                }
                map_x++;
            }
            map_y++;
        }
    }

    void quit()
    {
        for(int i=0; i < MAX_NUMBER_OF_TILES; i++)
        {
            SDL_DestroyTexture(tile_mat[i].texture);
        }
    }
};




#endif // GAMEMAP_H_INCLUDED
