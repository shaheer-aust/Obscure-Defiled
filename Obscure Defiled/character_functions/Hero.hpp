

#ifndef HERO_H
#define HERO_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>
#include "enemy_functions\enemy.hpp";
#include <vector>
using namespace std;
struct Hero
{
    double HeroHealth;
    bool gettingHit = false;
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
    int hit_index = 0;
    bool isMoving = false;
    bool isAttacking = false;
    int attack_timer = 0;
    vector<int> character_attack_R_images;
    vector<int> character_attack_L_images;
    vector<int> character_idle_hit_R_images;
    vector<int> character_idle_hit_L_images;
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
    void init_idle_hit_images()
    {
        for (int i = 1; i <= 3; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Getting Hit//idle+knife//idle_right_%d.png", i);
            character_idle_hit_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 3; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Getting Hit//idle+knife//idle_left_%d.png", i);
            character_idle_hit_L_images.push_back(iLoadImage(a));
        }
    }
    void show_getting_hit()
    {
        int currentIdx = hit_index;
        if (isright)
        {
            iShowImage(characterPosition_X, characterPosition_Y, 96, 96, character_idle_hit_R_images[currentIdx]);
        }
        else
        {
            iShowImage(characterPosition_X, characterPosition_Y, 96, 96, character_idle_hit_L_images[currentIdx]);
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
    void hero_attack_update(Enemy& enemy1, Boss& boss1)
    {
        if (isAttacking && !isJumping)
        {
            double enemyX = enemy1.enemyPosition_X;
            double enemyY = enemy1.enemyPosition_Y;
            double bossX = boss1.bossPosition_X;
            double bossY = boss1.bossPosition_Y;
            
            // Check if attack hits the enemy
            if (abs(characterPosition_X - enemyX) < 50 && abs(characterPosition_Y - enemyY) < 50)
            {
                enemy1.takeDamage(20); // Damage dealt to the enemy
                isAttacking = false;
                enemy1.enemyGettingHit = true;
                if (enemy1.enemyHealth <= 0)
                {
                    enemy1.isActive = false; // Deactivate enemy if health is 0 or less
                }
                //attack_index = 0;
                //attack_timer = 0;
            }
            
            // Check if attack hits the boss
            if (abs(characterPosition_X - bossX) < 50 && abs(characterPosition_Y - bossY) < 50)
            {
                
                boss1.bosstakeDamage(20); // Damage dealt to the boss
                isAttacking = false;
                boss1.bossGettingHit = true;
                boss1.show_boss_hit();
                if(boss1.bossHealth <= 0)
                {
                    boss1.show_boss_dead();
                    boss1.isActive = false; // Deactivate boss if health is 0 or less
                }
                //attack_index = 0;
                //attack_timer = 0;
            }
        }
    }
    void update_attack()
    {
        if (isAttacking)
        {
            attack_timer++;
            if (attack_timer >= 2) // Show each frame for 8 ticks
            {
                attack_index++;
                attack_timer = 0;
                if (attack_index >= character_attack_R_images.size())
                {
                    isAttacking = false;
                    attack_index = 0;
                    isMoving = false;
                }
            }
        }
    }
    void show_character_attack()
    {
        int currentIdx = attack_index;
        if (isright)
        {
            iShowImage(characterPosition_X, characterPosition_Y + 10, 96, 96, character_attack_R_images[currentIdx]);
        }
        else
        {
            iShowImage(characterPosition_X, characterPosition_Y + 10, 96, 96, character_attack_L_images[currentIdx]);
        }
    }
};

#endif