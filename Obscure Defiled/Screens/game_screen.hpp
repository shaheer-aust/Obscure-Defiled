#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef GAME_SCREEN_H
#define GAME_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 242
#define BUTTON_HEIGHT 62
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include <vector>
using namespace std;
struct GameScreen
{
    vector<int> images;
    int x = 0;
    void initgame_screen()
    {
        images.push_back(iLoadImage("resources//game_screen//level_1/bg_1//Screen_for_1st_round.png"));
    
    }
    void updategame_screen()
    {
        // Code to update game state, animations, etc. can be added here
        x-=10;
        if (x <= -SCREEN_WIDTH) {
            x = 0; // Reset to create a looping background effect
        }

    }
    void drawgame_screen()
    {
        iShowImage(x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        iShowImage(SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        // Additional drawing code for settings can be added here
    }
};

#endif