#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
extern void takeDamage();
#ifndef ENEMY_H
#define ENEMY_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>
#include "character_functions\Hero.hpp";
#include <vector>
using namespace std;
// Global state
struct Enemy
{
    vector<int> enemy_idle_R_images;
    vector<int> enemy_idle_L_images;
    double enemyPosition_X = SCREEN_WIDTH-64;
    double enemyPosition_Y = 100.0;
    double enemyHealth = 100.0;
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
            iShowImage(enemyPosition_X, enemyPosition_Y, 80, 80, enemy_idle_R_images[currentIdx]);
        }
        else
        {
            iShowImage(enemyPosition_X, enemyPosition_Y, 80, 80, enemy_idle_L_images[currentIdx]);
        }
    }
    void move_enemy(double characterX)
    {
        if (enemyPosition_X > characterX+25)
        {
            enemyPosition_X -= enemy_speed;
            isright = false;
        }
        else if (enemyPosition_X < characterX-25)
        {
            enemyPosition_X += enemy_speed;
            isright = true;
        }
        movement_index++;
        if (movement_index >= enemy_idle_R_images.size())
        {
            movement_index = 0;
        }
        if(enemyPosition_X == characterX+25 || enemyPosition_X == characterX-25)
        {
            // Attack logic can be implemented here
            // For example, you can reduce the hero's health when the enemy is close enough
            Hero::takeDamage(5); // Reduce hero health by 0.5 when enemy is close
            //mciSendString("open \"resources//Enemy//enemy_attack_sound.mp3\" alias enemyattack", NULL, 0, NULL);
            //mciSendString("play enemyattack from 0", NULL, 0, NULL);
        }
    }
};

#endif