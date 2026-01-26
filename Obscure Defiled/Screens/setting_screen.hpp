#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include <vector>
using namespace std;
struct Setting_screen
{
    vector<int> images;;
    void initsettingbar()
    {
        images.push_back(iLoadImage("resources//menu_screen//menu.jpg"));
        // Load images or resources needed for the settings screen
    }
    void drawsetting_screen()
    {
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        // Additional drawing code for settings can be added here
    }
};
#endif