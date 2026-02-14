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

// Forward declarations to avoid circular dependencies
struct Hero;
struct GameScreen;
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
    bool enemyGettingHit = false;
    bool isActive = true; // Whether this enemy is currently active in the game
    int enemyType = 1; // 1 for Small enemy 1, 2 for Small enemy 2
    
    void initenemy(int type = 1)
    {
        enemyType = type;
        init_enemy_images();
    }
	void enemyTakeDamage(double damage)
	{
		enemyHealth -= damage;
		enemyGettingHit = true;
		//hit_index = 0;

		if (enemyHealth < 0)
		{
			enemyHealth = 0;
			isActive = false; // Boss defeated
		}
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
        //}
    }
};

// Boss Enemy struct
struct Boss
{
    vector<int> boss_walking_R_images;
    vector<int> boss_walking_L_images;
    vector<int> boss_attacking_L_images;
	vector<int> boss_attacking_R_images;
    vector<int> boss_hit_R_images;
    vector<int> boss_hit_L_images;
    vector<int> boss_dead_L_images;
    vector<int> boss_dead_R_images;
    
    double bossPosition_X = SCREEN_WIDTH - 128;
    double bossPosition_Y = 100;
    double bossHealth = 200.0;
    double maxBossHealth = 200.0;
    bool isright = true;
    int movement_index = 0;
    double boss_speed = 5.0;
    bool isActive = false; // Boss spawns later in the game
    bool isAttacking = false;
    int attack_index = 0;
    bool bossGettingHit = false;
    int hit_index = 0;
    int attack_timer = 0;
    void initboss()
    {
        init_boss_images();
    }
    
    void init_boss_images()
    {
        // Load boss walking images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Level_1//Boss//Walking//Rlvl_1_boss_idle+walking_%d.png", i);
            boss_walking_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Level_1//Boss//Walking//Llvl_1_boss_idle+walking_%d.png", i);
            boss_walking_L_images.push_back(iLoadImage(a));
        }
        
        
        
        // Load boss getting hit images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Getting Hit/L_lvl_1_idle_1.png
            sprintf_s(a, "resources//Level_1//Boss//Getting Hit//R_lvl_1_idle_%d.png", i);
            boss_hit_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Getting Hit/R_lvl_1_idle_2.png
            sprintf_s(a, "resources//Level_1//Boss//Getting Hit//L_lvl_1_idle_%d.png", i);
            boss_hit_L_images.push_back(iLoadImage(a));
        }
        
        // Load boss dead images
        for (int i = 1; i <= 2; i++)
        {
            char a[200];
            ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Dead/Llvl_1_boss_dead_1.png
            sprintf_s(a, "resources//Level_1//Boss/Dead//Rlvl_1_boss_dead_%d.png", i);
            boss_dead_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 2; i++)
        {
            char a[200];
            ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Dead/Llvl_1_boss_dead_1.png
            sprintf_s(a, "resources//Level_1//Boss/Dead//Llvl_1_boss_dead_%d.png", i);
            boss_dead_L_images.push_back(iLoadImage(a));
        }
        // load attacking images
        for(int i = 1; i <= 5; i++)
        {
            char a[200];
            ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Attacking/L_boss_attack_1.png
            sprintf_s(a, "resources/Level_1/Boss/Attacking/L_boss_attack_%d.png", i);
            boss_attacking_L_images.push_back(iLoadImage(a));
        }
        for(int i = 1; i <= 5; i++)
        {
            char a[200];
            ///Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Attacking/R_boss_attack_1.png
            sprintf_s(a, "resources/Level_1/Boss/Attacking/R_boss_attack_%d.png", i);
            boss_attacking_R_images.push_back(iLoadImage(a));
        }
    }
    void show_attack()
    {
        if (!isActive) return; // Don't show inactive boss
        
        int currentIdx = attack_index;
        if (isright)
        {
            iShowImage(bossPosition_X, bossPosition_Y, 108, 108, boss_attacking_R_images[currentIdx]);
        }
        else
        {
            iShowImage(bossPosition_X, bossPosition_Y, 108, 108, boss_attacking_L_images[currentIdx]);
        }
    }
    
    void show_boss_moving()
    {
        if (!isActive) return; // Don't show inactive boss
        
        if (bossGettingHit)
        {
            show_boss_hit();
            return;
        }else if(bossHealth <= 0)
        {
            //show_boss_dead();
            return;
        }else if (isAttacking)
        {
            show_attack();
            return;
        }
        
        int currentIdx = movement_index % boss_walking_R_images.size();
        if (isright)
        {
            iShowImage(bossPosition_X, bossPosition_Y, 108, 108, boss_walking_R_images[currentIdx]);
        }
        else
        {
            iShowImage(bossPosition_X, bossPosition_Y, 108, 108, boss_walking_L_images[currentIdx]);
        }

    }
    
    void show_boss_hit()
    {
        if (hit_index >= boss_hit_R_images.size())
        {
            hit_index = 0;
            bossGettingHit = false;
        }
        
        if (isright)
        {
            iShowImage(bossPosition_X, bossPosition_Y, 108, 108, boss_hit_R_images[hit_index]);
        }
        else
        {
            iShowImage(bossPosition_X, bossPosition_Y, 108, 108, boss_hit_L_images[hit_index]);
        }
    }
    void show_boss_dead()
    {
        int currentIdx = hit_index / 4; // Slow down the death animation
        if (currentIdx >= boss_dead_R_images.size())
        {
            currentIdx = boss_dead_R_images.size() - 1; // Stay on the last frame
        }
        
        if (isright)
        {
            iShowImage(bossPosition_X, bossPosition_Y, 108, 108, boss_dead_R_images[currentIdx]);
        }
        else
        {
            iShowImage(bossPosition_X, bossPosition_Y, 108, 108, boss_dead_L_images[currentIdx]);
        }
    }
    void move_boss(Hero& hero1)
    {
        if (!isActive) return; // Don't move inactive boss
        
        double characterX = hero1.characterPosition_X;
        double characterY = hero1.characterPosition_Y;
        //boss attack check
        if (abs(bossPosition_X - characterX) < 66 && (bossPosition_Y == characterY))
        {
            if (!isAttacking)
            {
                isAttacking = true;
                attack_index = 0;
            }
        }
        else
        {
            isAttacking = false;
            attack_index = 0;
        }
        // Boss collision check
        if (abs(bossPosition_X - characterX) < 55 && (bossPosition_Y == characterY))
        {
            hero1.takeDamage(4); // Boss does more damage
            cout << "Boss hit! Hero health: " << hero1.HeroHealth << endl;
            hero1.gettingHit = true;
        }
        else
        {
            hero1.gettingHit = false;
        }
        
        // Boss AI - chase the hero
        if (bossPosition_X > characterX + 50)
        {
            bossPosition_X -= boss_speed;
            isright = false;
        }
        else if (bossPosition_X < characterX - 50)
        {
            bossPosition_X += boss_speed;
            isright = true;
        }
        
        movement_index++;
        if (movement_index >= boss_walking_R_images.size())
        {
            movement_index = 0;
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
                if (attack_index >= boss_attacking_R_images.size())
                {
                    isAttacking = false;
                    attack_index = 0;
                    //isMoving = false;
                }
            }
        }
    }
    void bosstakeDamage(double damage)
    {
        bossHealth -= damage;
        bossGettingHit = true;
        hit_index = 0;
        
        if (bossHealth < 0)
        {
            bossHealth = 0;
            isActive = false; // Boss defeated
        }
    }
};

#endif
