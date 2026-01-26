#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define BACK_BUTTON 81
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include <vector>
using namespace std;
struct Setting_screen
{
    vector<int> images;
    ;
    bool lastFrameBackClicked = false;
    long long lastBackBlipTime = 0;

    void initsettingbar()
    {
        images.push_back(iLoadImage("resources//menu_screen//menu.jpg"));
        images.push_back(iLoadImage("resources//menu_screen//Buttons//back.png"));
        // Load images or resources needed for the settings screen
    }
    void drawsetting_screen()
    {
        iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        iShowImage(50, SCREEN_HEIGHT - BACK_BUTTON - 50, BACK_BUTTON, BACK_BUTTON, images[1]);
        // Additional drawing code for settings can be added here
    }
    // back button hover and click detection for settings
    bool isBackButtonClicked(int mx, int my)
    {
        return (mx >= 50 && mx <= BACK_BUTTON + 50 && my >= SCREEN_HEIGHT - (BACK_BUTTON + 50) && my <= SCREEN_HEIGHT);
    }

    // hover detection
    void checkButtonHover(int mx, int my)
    {
        mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
        long long currentTime = glutGet(GLUT_ELAPSED_TIME);

        if (isBackButtonClicked(mx, my) && !lastFrameBackClicked)
        {
            if (currentTime - lastBackBlipTime > HOVER_COOLDOWN)
            {
                mciSendString("play ggsong from 0", NULL, 0, NULL);
                lastBackBlipTime = currentTime;
            }
            lastFrameBackClicked = true;
        }
        else if (!isBackButtonClicked(mx, my))
        {
            lastFrameBackClicked = false;
        }
    }
};
#endif