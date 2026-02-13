#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
extern void takeDamage();
#ifndef ENEMY_H
#define ENEMY_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>
#include "character_functions\Hero.hpp";
#include "Screens\game_screen.hpp"
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
    bool isActive = true; // Whether this enemy is currently active in the game
    int enemyType = 1; // 1 for Small enemy 1, 2 for Small enemy 2
    
    void initenemy(int type = 1)
    {
        enemyType = type;
        init_enemy_images();
    }
    void init_enemy_images()
    {
        // Load enemy images based on type
        if (enemyType == 1)
        {
            // Load Small enemy 1 walking images
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
        else if (enemyType == 2)
        {
            // Load Small enemy 2 walking images
            for (int i = 1; i <= 3; i++)
            {
                char a[200];
                ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Enemy/level_1/Small enemy 2/Walking/Walking 1/Right View/resize_green_walking_1_right.png
                sprintf_s(a, "resources/Enemy/level_1/Small enemy 2/Walking/Walking %d/Right View/resize_green_walking_%d_right.png", i,i);
                enemy_idle_R_images.push_back(iLoadImage(a));
            }
            for (int i = 1; i <= 3; i++)
            {
                char a[200];
                ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Enemy/level_1/Small enemy 2/Walking/Walking 1/Left View/resize_green_walking_1_left.png
                sprintf_s(a, "resources/Enemy/level_1/Small enemy 2/Walking/Walking %d/Left View/resize_green_walking_%d_left.png", i,i);
                enemy_idle_L_images.push_back(iLoadImage(a));
            }
        }
       
    }
    void show_enemy_moving()
    {
        if (!isActive) return; // Don't show inactive enemies
        
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
    void move_enemy(Hero& hero1)
    {
        if (!isActive) return; // Don't move inactive enemies
        
        double characterX= hero1.characterPosition_X;
        double characterY= hero1.characterPosition_Y;
		if (abs(enemyPosition_X - characterX) < 26 && (enemyPosition_Y==characterY)){
			hero1.takeDamage(2);
            hero1.gettingHit = true;
			//cout << hero1.HeroHealth<< endl;
		}else{
            hero1.gettingHit = false;
        }
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
		//if (characterX - enemyPosition_X < 30 || enemyPosition_X - characterX<30)
        //{
            // Attack logic can be implemented here
            // For example, you can reduce the hero's health when the enemy is close enough
			//cout << hero1.characterPosition_X; // Reduce hero health by 0.5 when enemy is close
            //mciSendString("open \"resources//Enemy//enemy_attack_sound.mp3\" alias enemyattack", NULL, 0, NULL);
            //mciSendString("play enemyattack from 0", NULL, 0, NULL);
        //}
    }
};

#endif