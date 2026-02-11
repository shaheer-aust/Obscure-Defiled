#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H
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
    vector<int> character_idle_images;
    vector<int> character_run_images;
    int x = 0;
    double bg_speed = 20.0;
    void initgame_screen()
    {
        images.push_back(iLoadImage("resources//game_screen//level_1/bg_1//screen_for_level_1_new.jpg"));
        init_character_images();
        //iSetTimer(200, idle_animation);
    }
    void init_character_images()
    {
        // Load character idle images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Idle//idle_right_%d.png", i + 1);
            character_idle_images.push_back(iLoadImage(a));
        }
        // character_idle_images.push_back(iLoadImage("resources//Main_Character//Normal/With Knife//Idle//idle_left_1.png"));
    }
	int idx=1;
    void show_character_idle()
    {
        iShowImage(100, 100, 64, 64, character_idle_images[idx]);
    }

    void handleSpecialKeyboard(unsigned char key)
    {
        // Handle special keyboard input for game controls (e.g., arrow keys for movement)
        if (key == GLUT_KEY_UP)
        {
            // Move player up
        }
        else if (key == GLUT_KEY_DOWN)
        {
            // Move player down
        }
        else if (key == GLUT_KEY_LEFT)
        {
            // Move player left
            x += bg_speed;
            if (x >= SCREEN_WIDTH)
            {
                x = 0; // Reset position to create a looping effect
            }
        }
        else if (key == GLUT_KEY_RIGHT)
        {
            // Move player right
            
            x -= bg_speed;
            if (x <= -SCREEN_WIDTH)
            {
                x = 0; // Reset position to create a looping effect
            }
        }
    }

    void drawgame_screen()
    {
		
        iShowImage(-SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        iShowImage(x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        iShowImage(SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        // Additional drawing code for settings can be added here
        show_character_idle();
    }
};

#endif