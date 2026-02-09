#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include <vector>
using namespace std;
struct Setting_screen
{
    vector<int> images;
    int screenWidth;
    int screenHeight;
    
    Setting_screen() : screenWidth(1280), screenHeight(720) {}
    
    void updateScreenDimensions(int width, int height)
    {
        screenWidth = width;
        screenHeight = height;
    }
    
    // Responsive dimensions based on screen size
    int getBackButtonSize() { return (int)(screenHeight * 0.11); }
    int getBackButtonX() { return (int)(screenWidth * 0.016); }
    int getBackButtonY() { return (int)(screenHeight - getBackButtonSize() - screenHeight * 0.028); }
    
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
        iShowImage(0, 0, screenWidth, screenHeight, images[0]);
        iShowImage(getBackButtonX(), getBackButtonY(), getBackButtonSize(), getBackButtonSize(), images[1]);
        // Additional drawing code for settings can be added here
    }
    // back button hover and click detection for settings
    bool isBackButtonClicked(int mx, int my)
    {
        int x = getBackButtonX();
        int y = getBackButtonY();
        int size = getBackButtonSize();
        return (mx >= x && mx <= x + size && my >= y && my <= y + size);
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