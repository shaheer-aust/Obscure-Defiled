#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef HERO_H
#define HERO_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>

#include <vector>
using namespace std;
class Hero
{
public:
    double HeroHealth = 50.0;
    vector<int> character_idle_R_images;
    vector<int> character_idle_L_images;
    vector<int> character_run_L_images;
    vector<int> character_run_R_images;
    vector<int> character_jump_R_images;
    vector<int> character_jump_L_images;
    double characterPosition_X = 100.0;
    double characterPosition_Y = 100.0;
    double character_speed = 6;
    bool isJumping = false;
    bool isright = true;
    int movement_index = 0;
    int jump_index = 0;
    bool isMoving = false;
    void takeDamage(double damage)
    {
        HeroHealth -= damage;
        if (HeroHealth < 0)
        {
            HeroHealth = 0;
        }
    }
};

#endif