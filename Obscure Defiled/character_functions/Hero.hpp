

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
    vector<int> character_dead_R_images;
    vector<int> character_dead_L_images;
    double characterPosition_X = 100.0;
    double characterPosition_Y = 100.0;
    double attack_index = 0;
    int dead_index = 0;
    double character_speed = 6;
    bool isJumping = false;
    bool isright = true;
    int movement_index = 0;
    int idle_Index = 0;
    int jump_index = 0;
    int hit_index = 0;
    bool isMoving = false;
    bool isAttacking = false;
    int attack_timer = 0;
    int dead_timer = 0;
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
    void init_character_images()
    {
        init_fighting_images();
        init_idle_hit_images();
        init_character_dead_images
        HeroHealth = 100;
        // Load character idle images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Idle//idle_right_%d.png", i);
            character_idle_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Idle//idle_left_%d.png", i);
            character_idle_L_images.push_back(iLoadImage(a));
        }
        // Load character run images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Walking//walking_left_%d.png", i);
            character_run_L_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Walking//walking_right_%d.png", i);
            character_run_R_images.push_back(iLoadImage(a));
        }
        // load character jump images if needed
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Jumping//jumping_right_%d.png", i);
            character_jump_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Jumping//jumping_left_%d.png", i);
            character_jump_L_images.push_back(iLoadImage(a));
        }
    }
    void init_character_dead_images()
    {
       for (int i = 1; i <= 8; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Dead from above//L_jump_dead_%d.png", i);
            character_dead_L_images.push_back(iLoadImage(a));
        }
       for (int i = 1; i <= 8; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Dead from above//R_jump_dead_%d.png", i);
            character_dead_R_images.push_back(iLoadImage(a));
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
    void show_character_dead(){
        int currentIdx = dead_index;
        if (isright)
        {
            iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_dead_R_images[currentIdx]);
        }
        else
        {
            iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_dead_L_images[currentIdx]);
        }
    }
    void show_getting_hit()
    {
        int currentIdx = hit_index;
        if (isright)
        {
            iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_idle_hit_R_images[currentIdx]);
        }
        else
        {
            iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_idle_hit_L_images[currentIdx]);
        }
    }
    void show_character_idle()
    {
        int currentIdx = idle_Index;
        if (isright)
        {
            iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_idle_R_images[currentIdx]);
        }
        else
        {
            iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_idle_L_images[currentIdx]);
        }
    }
    void show_character_run()
    {

        {
            if (movement_index >= character_run_R_images.size())
            {
                movement_index = 0;
            }
        }
        if (isright)
        {
            iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_run_R_images[movement_index]);
        }
        else
        {
            iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_run_L_images[movement_index]);
        }
    }
        void update_dead()
    {
        if (HeroHealth <= 0)
        {
            dead_timer++;
            if (dead_timer > 8) // Show each frame for 16 ticks
            {
                dead_timer = 0;
                dead_index++;
                if (dead_index >= character_dead_R_images.size())
                {
                    dead_index = character_dead_R_images.size() - 1; // Stay on the last frame of death animation
                }
            }
        }
    }
    void idle_animation()
    {
        idle_Index++;
        if (idle_Index >= 3)
        {
            idle_Index = 0;
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
    void update_attack()
    {
        if (isAttacking)
        {
            attack_timer++;
            if (attack_timer >= 2) // Show each frame for 2 ticks
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
            iShowImage(characterPosition_X, characterPosition_Y + 10, 152, 152, character_attack_R_images[currentIdx]);
        }
        else
        {
            iShowImage(characterPosition_X, characterPosition_Y + 10, 152, 152, character_attack_L_images[currentIdx]);
        }
    }
};

#endif