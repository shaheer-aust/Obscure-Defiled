#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef ENEMY_H
#define ENEMY_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>

#include <vector>
using namespace std;
// Global state
struct Enemy
{
    vector<int> enemy_idle_R_images;
    vector<int> enemy_idle_L_images;
    double enemyPosition_X = SCREEN_WIDTH-64;
    double enemyPosition_Y = 100.0;
    bool isright = false;
    int movement_index = 0;
    double enemy_speed = 8.0;
    void initenemy()
    {
        init_enemy_images();
    }
    void init_enemy_images()
    {
        // Load enemy idle images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Enemy//level_1//Small enemy 1//Walking//Walking %d//right view//resize_right_walking_%d.png", i,i);
            enemy_idle_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Enemy//level_1//Small enemy 1//Walking//Walking %d//left view//resize_left_walking_%d.png", i,i);
            enemy_idle_L_images.push_back(iLoadImage(a));
        }
       
    }
    void show_enemy_moving()
    {
        int currentIdx = movement_index;
        if (isright)
        {
            iShowImage(enemyPosition_X, enemyPosition_Y, 64, 64, enemy_idle_R_images[currentIdx]);
        }
        else
        {
            iShowImage(enemyPosition_X, enemyPosition_Y, 64, 64, enemy_idle_L_images[currentIdx]);
        }
    }
    void move_enemy(double characterX)
    {
        // Simple horizontal movement logic (you can customize this)
        // Move left at a constant speed
        // if (enemyPosition_X < -64) // If the enemy goes off-screen, reset its position
        // {
        //     enemyPosition_X = SCREEN_WIDTH;
        // }
        if (enemyPosition_X > characterX+20)
        {
            enemyPosition_X -= enemy_speed;
            isright = false;
        }
        else if (enemyPosition_X < characterX-20)
        {
            enemyPosition_X += enemy_speed;
            isright = true;
        }
        movement_index++;
        if (movement_index >= enemy_idle_R_images.size())
        {
            movement_index = 0;
        }
    }
};

#endif