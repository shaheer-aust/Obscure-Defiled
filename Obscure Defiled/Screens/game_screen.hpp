#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

// Forward declaration of idle index getter
extern int getIdleIndex();
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
    vector<int> character_idle_R_images;
    vector<int> character_idle_L_images;
    vector<int> character_run_L_images;
    vector<int> character_run_R_images;
    int movement_index = 0;
    bool isMoving = false;
    int x = 0;
    double characterPosition_X = 100.0;
    double characterPosition_Y = 100.0;
    double bg_speed = 20.0;
    double character_speed = 25.0;
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
            character_idle_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Idle//idle_left_%d.png", i + 1);
            character_idle_L_images.push_back(iLoadImage(a));
        }
        // Load character run images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Run//walking_left_%d.png", i + 1);
            character_run_L_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Run//walking_right_%d.png", i + 1);
            character_run_R_images.push_back(iLoadImage(a));
        }
        // character_idle_images.push_back(iLoadImage("resources//Main_Character//Normal/With Knife//Idle//idle_left_1.png"));
    }
    void show_character_idle()
    {
        int currentIdx = getIdleIndex();
        iShowImage(characterPosition_X, characterPosition_Y, 64, 64, character_idle_R_images[currentIdx]);
    }
    void show_character_run()
    {
        
        if (movement_index >= character_run_R_images.size())
        {
         
            movement_index = 0;
        }
        iShowImage(characterPosition_X, characterPosition_Y, 64, 64, character_run_R_images[movement_index]);
        //movement_index++;
    }
    void handleSpecialKeyboard(unsigned char key)
    {
        // Handle special keyboard input for game controls (e.g., arrow keys for movement)
        if (key == GLUT_KEY_UP)
        {
            // Move player up
            characterPosition_Y += bg_speed;
            if (characterPosition_Y > SCREEN_HEIGHT)
            {
                characterPosition_Y = SCREEN_HEIGHT;
            }
        }
        else if (key == GLUT_KEY_DOWN)
        {
            // Move player down
            characterPosition_Y -= bg_speed;
            if (characterPosition_Y < 0)
            {
                characterPosition_Y = 0;
            }
        }
        else if (key == GLUT_KEY_LEFT)
        {
            // Move player left
            characterPosition_X -= character_speed;
            if (characterPosition_X < 0)
            {
                characterPosition_X = 0;
            }
        }
        else if (key == GLUT_KEY_RIGHT)
        {
            // Move player right (forward)
            characterPosition_X += character_speed;
            if (characterPosition_X > SCREEN_WIDTH)
            {
                characterPosition_X = SCREEN_WIDTH;
            }
            isMoving = true;
            movement_index++;
            
        }
        else
        {
            isMoving = false;
            movement_index = 0;
        }
    }

    void drawgame_screen()
    {
		
        iShowImage(-SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        iShowImage(x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        iShowImage(SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        // Additional drawing code for settings can be added here
        if (isMoving)
        {
            show_character_run();
        }
        else
        {
            show_character_idle();
        }
    }
};

#endif