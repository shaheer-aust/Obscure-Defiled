

#ifndef HERO_H
#define HERO_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>
#include "enemy_functions\enemy.hpp";
#include "Screens\game_over_screen.hpp";
#include <vector>
using namespace std;
struct Hero
{
    double HeroHealth;

    vector<int> character_idle_R_images;
    vector<int> character_idle_L_images;
    vector<int> character_run_L_images;
    vector<int> character_run_R_images;
    vector<int> character_jump_R_images;
    vector<int> character_jump_L_images;
    vector<int> character_dead_R_images;
    vector<int> character_dead_L_images;
    vector<int> character_attack_R_images;
    vector<int> character_attack_L_images;
    vector<int> character_idle_hit_R_images;
    vector<int> character_idle_hit_L_images;
	int level = 1;
    double characterPosition_X;
    double characterPosition_Y;
    double attack_index = 0;
    int dead_index = 0;
    double character_speed = 20;
    double base_speed = 20;       // Primary speed (restored when power-up ends)
    double attack_damage = 8;    // Damage dealt per hit (boosted by power-up)
    bool isJumping = false;
    bool gettingHit = false;
    bool isright = true;
    int movement_index = 0;
    int idle_Index = 0;
    int jump_index = 0;
    int hit_index = 0;
    bool isMoving = false;
    bool isAttacking = false;
    int attack_timer = 0;
    int dead_timer = 0;
    bool isDead = false;

    void takeDamage(double damage)
    {
        HeroHealth -= damage;
        if (HeroHealth < 0)
        {
            HeroHealth = 0;
        }
    }
    void init_character_images(int level = 1)
    {
		character_idle_R_images.clear();
		character_idle_L_images.clear();
		character_run_L_images.clear();
		character_run_R_images.clear();
		character_jump_R_images.clear();
		character_jump_L_images.clear();
		
		character_attack_R_images.clear();
		character_attack_L_images.clear();
		character_idle_hit_R_images.clear();
		character_idle_hit_L_images.clear();
		characterPosition_X = 100.0;
		characterPosition_Y = 100.0;
		attack_index = 0;
		dead_index = 0;
		character_speed = 20;
		base_speed = 20;
		attack_damage = 20;
		isJumping = false;
		gettingHit = false;
		 isright = true;
		movement_index = 0;
		idle_Index = 0;
		jump_index = 0;
		hit_index = 0;
		isMoving = false;
		isAttacking = false;
		attack_timer = 0;
		dead_timer = 0;
		isDead = false;
		this->level = level;
        init_fighting_images(level);
        init_idle_hit_images(level);
        init_character_dead_images(level);
        HeroHealth = 100;
        
        if (level == 1)
        {
            // Load character idle images - adjust paths as needed
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
        }else if(level == 2){
            // Load character idle images - adjust paths as needed
            for (int i = 0; i <= 15; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Idle/Left/frame_%03d.png", i);
                character_idle_L_images.push_back(iLoadImage(a));
            }
            for (int i = 1; i <= 4; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Idle/Right/frame_%03d.png", i);
                character_idle_R_images.push_back(iLoadImage(a));
            }
            // Load character run images
			for (int i = 1; i <= 35; i++)
			{
				char a[200];
				sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Walking/Left/frame_%03d.png", i);
				character_run_L_images.push_back(iLoadImage(a));
			}
			for (int i = 1; i <= 35; i++)
			{
				char a[200];
				sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Walking/Right/frame_%03d.png", i);
				character_run_R_images.push_back(iLoadImage(a));
			}
                    // load character jump images if needed
            for (int i = 1; i <= 4; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Jumping/Right/frame_%03d.png", i);
                character_jump_R_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 35; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Jumping/Left/frame_%03d.png", i);
                character_jump_L_images.push_back(iLoadImage(a));
            }
        }
    }
    void init_character_dead_images(int level = 1)
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
    void init_fighting_images(int level = 1)
    {
        if (level == 1)
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
        }else if(level == 2){
            for (int i = 0; i <= 12; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Shooting/Right/frame_%03d.png", i);
                character_attack_R_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 12; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Shooting/Left/frame_%03d.png", i);
                character_attack_L_images.push_back(iLoadImage(a));
            }
        }
    }

    void init_idle_hit_images(int level = 1)
    {
        if (level == 1)
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
        }else if(level == 2){
            for (int i = 0; i <= 34; i++)
            {
                char a[200];
                ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Main_Character/Normal/With Handgun/Getting Hit/Left/frame_000.png
                sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Getting Hit/Right/frame_%03d.png", i);
                character_idle_hit_R_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 34; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Main_Character/Normal/With Handgun/Getting Hit/Left/frame_%03d.png", i);
                character_idle_hit_L_images.push_back(iLoadImage(a));
            }
        }
    }
    void show_character_jump1()
    {
        // choose frame based on direction and jump_index
		if (jump_index >= character_jump_R_images.size() - 1){
			jump_index = 0;
		}
        if (isright)
        {
            if (!character_jump_R_images.empty())
                iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_jump_R_images[jump_index]);
        }
        else
        {
            if (!character_jump_L_images.empty())
                iShowImage(characterPosition_X, characterPosition_Y, 152, 152, character_jump_L_images[jump_index]);
        }
    }
    void show_chracter_moving()
    {
        if (isAttacking)
        {
            show_character_attack();
        }
        else if (HeroHealth <= 0)
        {
            show_character_dead();
        }
        else if (isJumping)
        {
            show_character_jump1();
        }
        else if (isMoving)
        {
            show_character_run();
        }
        else if (gettingHit)
        {

            show_getting_hit();
        }
        else
        {
            show_character_idle();
        }
    }
    void show_character_dead()
    {
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
    void show_character_attack()
    {
        int currentIdx = attack_index;  
        if (isright)
        {
			iShowImage(characterPosition_X-(level==1?0:50), characterPosition_Y + (level == 1 ? 10 : 0), level == 1 ? 152 : 250, 152, character_attack_R_images[currentIdx]);
        }
        else
        {
			iShowImage(characterPosition_X - (level == 1 ? 0 : 50), characterPosition_Y + (level == 1 ? 10 : 0), level == 1 ? 152 : 250, 152, character_attack_L_images[currentIdx]);
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
    void update_dead() // 50 mili second main loop e call hobe
    {
        if (HeroHealth <= 0)
        {
            dead_timer++;       // Increment timer
            if (dead_timer > 1) // Show each frame for 16 ticks
            {
                dead_timer = 0;
                dead_index++;
                if (dead_index >= character_dead_R_images.size())
                {
                    dead_index = character_dead_R_images.size() - 1; // Stay on the last frame of death animation
                    isDead = true;
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
            if (attack_timer >= level==1?2:-1) // Show each frame for 2 ticks
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
};

#endif