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
    double attack_index = 0;
    double character_speed = 6;
    bool isJumping = false;
    bool isright = true;
    int movement_index = 0;
    int jump_index = 0;
    bool isMoving = false;
    bool isAttacking = false;
    int attack_timer = 0;
    vector<int> character_attack_R_images;
    vector<int> character_attack_L_images;
    void takeDamage(double damage)
    {
        HeroHealth -= damage;
        if (HeroHealth < 0)
        {
            HeroHealth = 0;
        }
    }
    void init_fighting_images()
    {
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Ground Hitting//hit_right_%d.png", i);
            character_attack_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Ground Hitting//hit_left_%d.png", i);
            character_attack_L_images.push_back(iLoadImage(a));
        }
    }
    void startAttack()
    {
        if (!isAttacking && !isJumping)
        {
            isAttacking = true;
            attack_index = 0;
            attack_timer = 0;
            isMoving = false;
        }
    }
    void show_character_attack()
    {
        int currentIdx = attack_index;
        if (isright)
        {
            iShowImage(characterPosition_X, characterPosition_Y, 96, 96, character_attack_R_images[currentIdx]);
        }
        else
        {
            iShowImage(characterPosition_X, characterPosition_Y, 96, 96, character_attack_L_images[currentIdx]);
        }
    }
};

#endif