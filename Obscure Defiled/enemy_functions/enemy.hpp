#ifndef ENEMY_H
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
extern void takeDamage();

#define ENEMY_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "character_functions\Hero.hpp";
// #include "Screens\Level_1_game_screen.hpp"
#include <vector>
using namespace std;

// Forward declarations to avoid circular dependencies
struct Hero;
// struct Lvl_1_GameScreen;
//  Global state
struct Enemy
{
    vector<int> enemy_idle_R_images;
    vector<int> enemy_idle_L_images;
    vector<int> enemy_attacking_R_images;
    vector<int> enemy_attacking_L_images;
    vector<int> enemy_hit_R_images;
    vector<int> enemy_hit_L_images;
    double enemyPosition_X = SCREEN_WIDTH - 64;
    double enemyPosition_Y = 100.0;
    double enemyHealth = 100.0;
    bool isright = false;
    int enemy_movement_index = 0;
    double enemy_speed = 8.0;
    bool enemyGettingHit = false;
    bool isAttacking = false;
    int attack_index = 0;
    int hit_index = 0;
    bool isActive = true; // Whether this enemy is currently active in the game
    int enemyType = 1;    // 1 for Small enemy 1, 2 for Small enemy 2
	int level = 1;
    void initenemy(int type = 1, int level = 1)
    {
        enemyPosition_X = SCREEN_WIDTH - 64;
        enemyPosition_Y = 100.0;
        enemyHealth = 100.0;
        isright = false;
		enemy_movement_index = 0;
        enemy_speed = 8.0;
        enemyGettingHit = false;
        isAttacking = false;
        attack_index = 0;
        hit_index = 0;
        isActive = true; // Whether this enemy is currently active in the game
		this->level = level;
        enemyType = type;
        init_enemy_images(level);
    }
    void enemy_takeDamage(double damage)
    {
        cout << "Enemy takes damage: " << damage << endl;
        enemyHealth -= damage;
        enemyGettingHit = true;
        hit_index = 0;
        isAttacking = false;
        attack_index = 0;
        if (enemyHealth <= 0)
        {

            enemyHealth = 0;
            isActive = false; // Deactivate enemy when health reaches 0
        }
    }
    void init_enemy_images(int level = 1)
    {
		enemy_idle_L_images.clear();
		enemy_idle_R_images.clear();
		enemy_attacking_L_images.clear();
		enemy_attacking_R_images.clear();
		enemy_hit_L_images.clear();
		enemy_hit_R_images.clear();
		
		
        // Load enemy images based on type
        if (enemyType == 1)
        {
            if (level == 1|| level == 2)
            {
                // Load Small enemy 1 walking images
				
                for (int i = 1; i <= 4; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources//Enemy//level_1//Small enemy 1//Walking//Walking %d//right view//resize_right_walking_%d.png", i, i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 1; i <= 4; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources//Enemy//level_1//Small enemy 1//Walking//Walking %d//left view//resize_left_walking_%d.png", i, i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
            }
            else if (level == 3)
            {
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 1/right/walking/frame_%03d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 1/left/walking/frame_%03d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 1/right/attacking/frame_%03d.png", i);
                    enemy_attacking_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 1/left/attacking/frame_%03d.png", i);
                    enemy_attacking_L_images.push_back(iLoadImage(a));
                }
            }
            
        }
        else if (enemyType == 2)
        {
            // Load Small enemy 2 walking images
            if (level == 1)
            {
				
                for (int i = 1; i <= 3; i++)
                {
                    char a[200];
                    /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Enemy/level_1/Small enemy 2/Walking/Walking 1/Right View/resize_green_walking_1_right.png
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 2/Walking/Walking %d/Right View/resize_green_walking_%d_right.png", i, i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 1; i <= 3; i++)
                {
                    char a[200];
                    /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Enemy/level_1/Small enemy 2/Walking/Walking 1/Left View/resize_green_walking_1_left.png
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 2/Walking/Walking %d/Left View/resize_green_walking_%d_left.png", i, i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
            }
            else if (level == 2)
            {
			
                for (int i = 0; i <= 35; i++)
                {

                    char a[200];
                    /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Enemy/level_1/Small enemy 2/right/00.png
                    // sprintf_s(a, "resources//Level_1//Boss//Walking//Rlvl_1_boss_idle+walking_%d.png", i);
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 2/right/%d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 2/left/%d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
                for (int i = 1; i <= 36; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_1/Boss/Attacking/right/%d.png", i);
                    enemy_attacking_R_images.push_back(iLoadImage(a));
                }
                for (int i = 1; i <= 36; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_1/Boss/Attacking/left/%d.png", i);
                    enemy_attacking_L_images.push_back(iLoadImage(a));
                }
                for (int i = 2; i <= 22; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_1/Boss/Getting Hit/right/%d.png", i);
                    enemy_hit_R_images.push_back(iLoadImage(a));
                }
                for (int i = 2; i <= 22; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_1/Boss/Getting Hit/left/%d.png", i);
                    enemy_hit_L_images.push_back(iLoadImage(a));
                }
            }
            else if (level == 3)
            {
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 2/right/walking/frame_%03d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 2/left/walking/frame_%03d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 2/right/attacking/frame_%03d.png", i);
                    enemy_attacking_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 2/left/attacking/frame_%03d.png", i);
                    enemy_attacking_L_images.push_back(iLoadImage(a));
                }
            }
        }
        else if (enemyType == 3)
        {
            if (level == 1)
            {
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 3/Right/Walking/frame_%03d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 3/Left/Walking/frame_%03d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
            }else if (level == 2)
            {
                // Load Small enemy 1 walking images for level 2 (can be different if desired)
				
                for (int i = 0; i <= 15; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_2/Small enemy 1/Right/Walking/frame_%03d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 1; i <= 15; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_2/Small enemy 1/Left/Walking/frame_%03d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
				
            }
            else if (level == 3)
            {
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 3/right/walking/frame_%03d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 3/left/walking/frame_%03d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 3/right/attacking/frame_%03d.png", i);
                    enemy_attacking_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 3/left/attacking/frame_%03d.png", i);
                    enemy_attacking_L_images.push_back(iLoadImage(a));
                }
                // for (int i = 0; i <= 35; i++)
                // {
                //     char a[200];
                //     sprintf_s(a, "resources/Level_3/enemy 3/right/getting hit/frame_%03d.png", i);
                //     enemy_hit_R_images.push_back(iLoadImage(a));
                // }
                // for (int i = 0; i <= 35; i++)
                // {
                //     char a[200];
                //     sprintf_s(a, "resources/Level_3/enemy 3/left/getting hit/frame_%03d.png", i);
                //     enemy_hit_L_images.push_back(iLoadImage(a));
                // }
            }
        }
        else if (enemyType == 4)
        {
            if (level == 1)
            {
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 4/Right/Walking/frame_%03d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 4/Left/Walking/frame_%03d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 4/Right/Attacking/frame_%03d.png", i);
                    enemy_attacking_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 4/Left/Attacking/frame_%03d.png", i);
                    enemy_attacking_L_images.push_back(iLoadImage(a));
                }
            }
            else if (level == 2)
            {
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 4/Right/Walking/frame_%03d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 4/Left/Walking/frame_%03d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 4/Right/Attacking/frame_%03d.png", i);
                    enemy_attacking_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 8; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Enemy/level_1/Small enemy 4/Left/Attacking/frame_%03d.png", i);
                    enemy_attacking_L_images.push_back(iLoadImage(a));
                }
            }
            else if (level == 3)
            {
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 4/right/walking/frame_%03d.png", i);
                    enemy_idle_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 4/left/walking/frame_%03d.png", i);
                    enemy_idle_L_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 4/right/attacking/frame_%03d.png", i);
                    enemy_attacking_R_images.push_back(iLoadImage(a));
                }
                for (int i = 0; i <= 35; i++)
                {
                    char a[200];
                    sprintf_s(a, "resources/Level_3/enemy 4/left/attacking/frame_%03d.png", i);
                    enemy_attacking_L_images.push_back(iLoadImage(a));
                }
            }
        }
    }
    void show_enemy_attack()
    {
        if (enemy_attacking_R_images.empty() || enemy_attacking_L_images.empty())
            return;

        int currentIdx = attack_index % enemy_attacking_R_images.size();
        if (isright)
        {
            iShowImage(enemyPosition_X, enemyPosition_Y - 30, 190, 130, enemy_attacking_R_images[currentIdx]);
        }
        else
        {
            iShowImage(enemyPosition_X, enemyPosition_Y - 30, 190, 130, enemy_attacking_L_images[currentIdx]);
        }
    }
    void show_enemy_hit()
    {
        if (enemy_hit_R_images.empty() || enemy_hit_L_images.empty()||level == 3)
            return;

        int currentIdx = hit_index % enemy_hit_R_images.size();
        if (isright)
        {
            iShowImage(enemyPosition_X, enemyPosition_Y - 30, 190, 130, enemy_hit_R_images[currentIdx]);
        }
        else
        {
            iShowImage(enemyPosition_X, enemyPosition_Y - 30, 190, 130, enemy_hit_L_images[currentIdx]);
        }
    }
    void show_enemy_moving()
    {
        if (!isActive)
            return; // Don't show inactive enemies

		if (enemy_idle_R_images.empty() || enemy_idle_L_images.empty())
			return;

		if (enemyGettingHit && !enemy_hit_R_images.empty() && !enemy_hit_L_images.empty())
		{
			show_enemy_hit();
			return;
		}

		if (isAttacking && !enemy_attacking_R_images.empty() && !enemy_attacking_L_images.empty())
		{
			show_enemy_attack();
			return;
		}

		int currentIdx = enemy_movement_index % enemy_idle_R_images.size();
		//cout << " index: " << currentIdx << endl;
        if (isright)
        {
			iShowImage(enemyPosition_X, enemyPosition_Y, 100, 100, enemy_idle_R_images[currentIdx]);
        }
        else
        {
			iShowImage(enemyPosition_X, enemyPosition_Y, 100, 100, enemy_idle_L_images[currentIdx]);
        }
    }
    void move_enemy(Hero &hero1)
    {
        if (!isActive)
            return; // Don't move inactive enemies

		if (enemy_idle_R_images.empty() || enemy_idle_L_images.empty())
			return;

        double characterX = hero1.characterPosition_X;
        double characterY = hero1.characterPosition_Y;
        if (abs(enemyPosition_X - characterX) <= 51 && abs(enemyPosition_Y - characterY) <= 50 && isActive)
        {
            if (hero1.isAttacking)
            {
                hero1.gettingHit = false;
                enemy_takeDamage(hero1.attack_damage); // Hero attack damage (boosted by power-up)
            }
            else
            {
                hero1.gettingHit = true;
                if (!enemy_attacking_R_images.empty() && !enemy_attacking_L_images.empty())
                {
                    isAttacking = true;
                }
                hero1.takeDamage(2); // hero takes 2 damage when hit by enemy
            }
        }
        else
        {
            hero1.gettingHit = false;
            isAttacking = false;
            attack_index = 0;
        }

		if (enemyGettingHit && !enemy_hit_R_images.empty() && !enemy_hit_L_images.empty())
		{
			hit_index++;
			if (hit_index >= enemy_hit_R_images.size())
			{
				hit_index = 0;
				enemyGettingHit = false;
			}
			return;
		}

		if (isAttacking && !enemy_attacking_R_images.empty() && !enemy_attacking_L_images.empty())
		{
			attack_index++;
			if (attack_index >= enemy_attacking_R_images.size())
			{
				attack_index = 0;
			}
			return;
		}
        if (enemyPosition_X > characterX + 50)
        {
            if (enemyHealth <= 0)
            {
                // isActive = false;
                return;
            }
            enemyPosition_X -= enemy_speed;
            isright = false;
        }
        else if (enemyPosition_X < characterX - 50)
        {
            if (enemyHealth <= 0)
            {
                // isActive = false;
                return;
            }
            enemyPosition_X += enemy_speed;
            isright = true;
        }
		enemy_movement_index++;
		if (enemy_movement_index >= enemy_idle_R_images.size()-1)
        {
			enemy_movement_index = 0;
        }
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
    vector<int> boss_health_bar_images;

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
    int dead_index = 0;
    int dead_timer = 0;
	int level = 1;
    void initboss(int level = 1)
    {
		this->level = level;
        bossPosition_X = SCREEN_WIDTH - 128;
        bossPosition_Y = 100;
        bossHealth = 200.0;
        maxBossHealth = 200.0;
        isright = true;
        movement_index = 0;
        boss_speed = 5.0;
        isActive = false; // Boss spawns later in the game
        isAttacking = false;
        attack_index = 0;
        bossGettingHit = false;
        hit_index = 0;
        attack_timer = 0;
        dead_index = 0;
        dead_timer = 0;
        init_boss_images(level);
    }

    void init_boss_images(int level = 1)
    {
        // Load boss walking images
		boss_walking_R_images.clear();
		boss_walking_L_images.clear();
		boss_hit_R_images.clear();
		boss_hit_L_images.clear();
		boss_dead_R_images.clear();
		boss_dead_L_images.clear();
		boss_attacking_L_images.clear();
		boss_attacking_R_images.clear();
        init_boss_health_bar_images();
        if (level == 1)
        {
            for (int i = 0; i <= 35; i++)
            {

                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Enemy/level_1/Small enemy 2/right/00.png
                // sprintf_s(a, "resources//Level_1//Boss//Walking//Rlvl_1_boss_idle+walking_%d.png", i);
                sprintf_s(a, "resources/Enemy/level_1/Small enemy 2/right/%d.png", i);
                boss_walking_R_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 35; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Enemy/level_1/Small enemy 2/left/%d.png", i);
                boss_walking_L_images.push_back(iLoadImage(a));
            }

            // Load boss getting hit images
            for (int i = 2; i <= 8; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Getting Hit/L_lvl_1_idle_1.png
                sprintf_s(a, "resources/Level_1/Boss/Getting Hit/right/%d.png", i);
                boss_hit_R_images.push_back(iLoadImage(a));
            }
            for (int i = 2; i <= 8; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Getting Hit/R_lvl_1_idle_2.png
                sprintf_s(a, "resources/Level_1/Boss/Getting Hit/left/%d.png", i);
                boss_hit_L_images.push_back(iLoadImage(a));
            }

            // Load boss dead images
            for (int i = 1; i <= 2; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Dead/Llvl_1_boss_dead_1.png
                sprintf_s(a, "resources//Level_1//Boss/Dead//Rlvl_1_boss_dead_%d.png", i);
                boss_dead_R_images.push_back(iLoadImage(a));
            }
            for (int i = 1; i <= 2; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Dead/Llvl_1_boss_dead_1.png
                sprintf_s(a, "resources//Level_1//Boss/Dead//Llvl_1_boss_dead_%d.png", i);
                boss_dead_L_images.push_back(iLoadImage(a));
            }
            // load attacking images
            for (int i = 1; i <= 36; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Attacking/L_boss_attack_1.png
                sprintf_s(a, "resources/Level_1/Boss/Attacking/left/%d.png", i);
                boss_attacking_L_images.push_back(iLoadImage(a));
            }
            for (int i = 1; i <= 36; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Attacking/R_boss_attack_1.png
                sprintf_s(a, "resources/Level_1/Boss/Attacking/right/%d.png", i);
                boss_attacking_R_images.push_back(iLoadImage(a));
            }
        }
        else if (level == 2)
        {
            for (int i = 0; i <= 26; i++)
            {

                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Enemy/level_1/Small enemy 2/right/00.png
                // sprintf_s(a, "resources//Level_1//Boss//Walking//Rlvl_1_boss_idle+walking_%d.png", i);
                sprintf_s(a, "resources/Level_2/Boss/Left/Walking/frame_%03d.png", i);
                boss_walking_L_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 26; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Level_2/Boss/Right/Walking/frame_%03d.png", i);
                boss_walking_R_images.push_back(iLoadImage(a));
            }
            // load attacking images
            for (int i = 0; i <= 35; i++)
            {
                char a[200];
                /// /Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_2/Boss/Left/Attacking/frame_000.png
                sprintf_s(a, "resources/Level_2/Boss/Left/Attacking/frame_%03d.png", i);
                boss_attacking_L_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 35; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Attacking/R_boss_attack_1.png
                sprintf_s(a, "resources/Level_2/Boss/Right/Attacking/frame_%03d.png", i);
                boss_attacking_R_images.push_back(iLoadImage(a));
            }

            // Load boss dead images
            for (int i = 0; i <= 35; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Dead/Llvl_1_boss_dead_1.png
                sprintf_s(a, "resources/Level_2/Boss/Right/Dying/frame_%03d.png", i);
                boss_dead_R_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 35; i++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level_1/Boss/Dead/Llvl_1_boss_dead_1.png
                sprintf_s(a, "resources/Level_2/Boss/Left/Dying/frame_%03d.png", i);
                boss_dead_L_images.push_back(iLoadImage(a));
            }
        }
        else if (level == 3)
        {
            for (int i = 0; i <= 8; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Level_3/boss/Right/walking/frame_%03d.png", i);
                boss_walking_R_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 8; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Level_3/boss/Left/walking/frame_%03d.png", i);
                boss_walking_L_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 8; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Level_3/boss/Right/attacking/frame_%03d.png", i);
                boss_attacking_R_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 8; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Level_3/boss/Left/attacking/frame_%03d.png", i);
                boss_attacking_L_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 8; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Level_3/boss/Right/dying/frame_%03d.png", i);
                boss_dead_R_images.push_back(iLoadImage(a));
            }
            for (int i = 0; i <= 8; i++)
            {
                char a[200];
                sprintf_s(a, "resources/Level_3/boss/Left/dying/frame_%03d.png", i);
                boss_dead_L_images.push_back(iLoadImage(a));
            }
        }
    }
    void init_boss_health_bar_images()
    {
		boss_health_bar_images.clear();
        for (int i = 1; i <= 4; i++)
        {
            for (int j = 1; j <= 4; j++)
            {
                char a[200];
                /// Users/shaheerimam/Documents/GitHub/Obscure-Defiled/Obscure Defiled/resources/Level 1 boss enemy health bar/Enemy_health_bar_100.png
                sprintf_s(a, "resources//Level 1 boss enemy health bar//row-%d-column-%d.png", i, j);
                boss_health_bar_images.push_back(iLoadImage(a));
            }
        }
    }
    void show_attack()
    {
        if (!isActive)
            return; // Don't show inactive boss

        if (boss_attacking_R_images.empty() || boss_attacking_L_images.empty())
            return;

        int currentIdx = attack_index;
        if (isright)
        {
			iShowImage(bossPosition_X, bossPosition_Y -30, level == 1 ? 190 : 200, level == 1 ? 130 : 200, boss_attacking_R_images[currentIdx]);
        }
        else
        {
			iShowImage(bossPosition_X, bossPosition_Y -30, level == 1 ? 190 : 200, level == 1 ? 130 : 200, boss_attacking_L_images[currentIdx]);
        }
    }
    void show_boss_dead()
    {
        if (boss_dead_R_images.empty() || boss_dead_L_images.empty())
            return;

        if (isright)
        {
            iShowImage(bossPosition_X, bossPosition_Y - 10, 162, 162, boss_dead_R_images[dead_index]);
        }
        else
        {
            iShowImage(bossPosition_X, bossPosition_Y - 10, 162, 162, boss_dead_L_images[dead_index]);
        }
    }

    void show_boss_moving()
    {
        if (bossHealth <= 0)
        {
            show_boss_dead();
            return;
        }
        else if (bossGettingHit && isActive)
        {
            show_boss_hit();
            return;
        }
        else if (isAttacking && isActive)
        {
            show_attack();
            return;
        }

        int currentIdx = movement_index % boss_walking_R_images.size();
        if (isright && isActive)
        {
            iShowImage(bossPosition_X, bossPosition_Y, level==1?122:130, level==1?81:170, boss_walking_R_images[currentIdx]);
        }
        else if (isActive)
        {
			iShowImage(bossPosition_X, bossPosition_Y, level == 1 ? 122 : 130, level == 1 ? 81 : 170, boss_walking_L_images[currentIdx]);
        }
    }

    void show_boss_hit()
    {
        if (boss_hit_R_images.empty() || boss_hit_L_images.empty())
        {
            bossGettingHit = false;
            hit_index = 0;
            return;
        }

        if (hit_index >= boss_hit_R_images.size()-1)
        {
            hit_index = 0;
            bossGettingHit = false;
        }

        if (isright)
        {
            iShowImage(bossPosition_X, bossPosition_Y - (level==1?30:0), level==1?190:200, level==1?130:200, boss_hit_R_images[hit_index]);
        }
        else
        {
			iShowImage(bossPosition_X, bossPosition_Y - (level == 1 ? 30 : 0), level == 1 ? 190 : 200, level == 1 ? 130 : 200, boss_hit_L_images[hit_index]);
        }
    }
    void boss_hit_loop()
    {
        if (bossGettingHit && isActive)
        {
            hit_index++;
            if (hit_index >= boss_hit_R_images.size())
            {
                hit_index = 0;
                bossGettingHit = false;
            }
        }
    }
    // timer calls this to move the boss and check for collisions with the hero
    void move_boss(Hero &hero1)
    {
        if (!isActive)
            return; // Don't move inactive boss

        double characterX = hero1.characterPosition_X;
        double characterY = hero1.characterPosition_Y;

        // Boss collision check
        if (abs(bossPosition_X - characterX) < 81 && abs(bossPosition_Y - characterY) < 50)
        {
            if (hero1.isAttacking)
            {
                bosstakeDamage(hero1.attack_damage * 0.6); // Hero attack damage on boss (60% of hero attack_damage, boosted by power-up)
                hero1.gettingHit = false;
            }
            else
            {
                hero1.takeDamage(2);
                cout << "Boss hit! Hero health: " << hero1.HeroHealth << endl;
                hero1.gettingHit = true;
            }
        }
        else
        {
            hero1.gettingHit = false;
        }
        // boss attack check
        if (abs(bossPosition_X - characterX) < 81 && abs(bossPosition_Y - characterY) < 50)
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
        // Boss AI - chase the hero
        if (bossPosition_X > characterX + 80)
        {
            if (bossHealth <= 0)
            {
                return;
            }
            bossPosition_X -= boss_speed;
            isright = false;
        }
        else if (bossPosition_X < characterX - 80)
        {
            if (bossHealth <= 0)
            {
                return;
            }
            bossPosition_X += boss_speed;
            isright = true;
        }

        movement_index++;
        if (movement_index >= boss_walking_R_images.size())
        {
            movement_index = 0;
        }
    }
    void update_dead()
    {
        if (bossHealth <= 0)
        {
            dead_timer++;
            if (dead_timer > level==1?16:-1) // Show each frame for 16 ticks
            {
                dead_timer = 0;
                dead_index++;
                if (dead_index >= boss_dead_R_images.size())
                {
                    dead_index = boss_dead_R_images.size() - 1; // Stay on the last frame of death animation
                }
            }
        }
    }
    void update_attack()
    {
        if (isAttacking)
        {
            attack_index++;
			
            if (attack_index >= boss_attacking_R_images.size()-1)
            {
                isAttacking = false;
                attack_index = 0;
            }
        }
    }
    void bosstakeDamage(double damage)
    {
        bossHealth -= damage;
        bossGettingHit = true;
        hit_index = 0;

        if (bossHealth <= 0)
        {

            bossHealth = 0;
            isActive = false; // Boss defeated
        }
    }
};

struct AlphaBoss
{
    vector<int> walking_R_images;
    vector<int> walking_L_images;
    vector<int> dying_R_images;
    vector<int> dying_L_images;
    vector<int> chanting_R_images;
    vector<int> chanting_L_images;
    vector<int> firing_R_images;
    vector<int> firing_L_images;
    vector<int> sword_R_images;
    vector<int> sword_L_images;

    double alphaPosition_X = SCREEN_WIDTH - 180;
    double alphaPosition_Y = 100.0;
    double alphaHealth = 300.0;
    double maxAlphaHealth = 300.0;
    double alpha_speed = 4.0;
    bool isright = true;
    bool isActive = false;
    bool isAttacking = false;
    int movement_index = 0;
    int attack_index = 0;
    int dead_index = 0;
    int dead_timer = 0;
    int attack_timer = 0;
    int attackMode = 0; // 0: chanting, 1: firing, 2: sword
    int level = 3;

    void initAlphaBoss(int level = 3)
    {
        this->level = level;
        alphaPosition_X = SCREEN_WIDTH - 180;
        alphaPosition_Y = 100.0;
        alphaHealth = 300.0;
        maxAlphaHealth = 300.0;
        alpha_speed = 4.0;
        isright = true;
        isActive = false;
        isAttacking = false;
        movement_index = 0;
        attack_index = 0;
        dead_index = 0;
        dead_timer = 0;
        attack_timer = 0;
        attackMode = 0;

        static bool seeded = false;
        if (!seeded)
        {
            srand((unsigned int)time(NULL));
            seeded = true;
        }

        init_alpha_images(level);
    }

    void init_alpha_images(int level = 3)
    {
        walking_R_images.clear();
        walking_L_images.clear();
        dying_R_images.clear();
        dying_L_images.clear();
        chanting_R_images.clear();
        chanting_L_images.clear();
        firing_R_images.clear();
        firing_L_images.clear();
        sword_R_images.clear();
        sword_L_images.clear();

        if (level != 3)
        {
            return;
        }

        for (int i = 0; i <= 35; i++)
        {
            char a[220];
            sprintf_s(a, "resources/Level_3/alpha boss/Right/Walking/frame_%03d.png", i);
            walking_R_images.push_back(iLoadImage(a));
        }
        for (int i = 0; i <= 35; i++)
        {
            char a[220];
            sprintf_s(a, "resources/Level_3/alpha boss/Left/Walking/frame_%03d.png", i);
            walking_L_images.push_back(iLoadImage(a));
        }
        for (int i = 0; i <= 35; i++)
        {
            char a[220];
            sprintf_s(a, "resources/Level_3/alpha boss/Right/Dying/frame_%03d.png", i);
            dying_R_images.push_back(iLoadImage(a));
        }
        for (int i = 0; i <= 35; i++)
        {
            char a[220];
            sprintf_s(a, "resources/Level_3/alpha boss/Left/Dying/frame_%03d.png", i);
            dying_L_images.push_back(iLoadImage(a));
        }

        for (int i = 0; i <= 35; i++)
        {
            char a[240];
            sprintf_s(a, "resources/Level_3/alpha boss/Right/Attacking/Chanting/frame_%03d.png", i);
            chanting_R_images.push_back(iLoadImage(a));
        }
        for (int i = 0; i <= 35; i++)
        {
            char a[240];
            sprintf_s(a, "resources/Level_3/alpha boss/Left/Attacking/Chanting/frame_%03d.png", i);
            chanting_L_images.push_back(iLoadImage(a));
        }

        for (int i = 0; i <= 35; i++)
        {
            char a[240];
            sprintf_s(a, "resources/Level_3/alpha boss/Right/Attacking/Firing/frame_%03d.png", i);
            firing_R_images.push_back(iLoadImage(a));
        }
        for (int i = 0; i <= 35; i++)
        {
            char a[240];
            sprintf_s(a, "resources/Level_3/alpha boss/Left/Attacking/Firing/frame_%03d.png", i);
            firing_L_images.push_back(iLoadImage(a));
        }

        for (int i = 0; i <= 35; i++)
        {
            char a[240];
            sprintf_s(a, "resources/Level_3/alpha boss/Right/Attacking/Sword/frame_%03d.png", i);
            sword_R_images.push_back(iLoadImage(a));
        }
        for (int i = 0; i <= 35; i++)
        {
            char a[240];
            sprintf_s(a, "resources/Level_3/alpha boss/Left/Attacking/Sword/frame_%03d.png", i);
            sword_L_images.push_back(iLoadImage(a));
        }
    }

    vector<int>& currentAttackFramesRight()
    {
        if (attackMode == 0) return chanting_R_images;
        if (attackMode == 1) return firing_R_images;
        return sword_R_images;
    }

    vector<int>& currentAttackFramesLeft()
    {
        if (attackMode == 0) return chanting_L_images;
        if (attackMode == 1) return firing_L_images;
        return sword_L_images;
    }

    int currentAttackDamage() const
    {
        if (attackMode == 0) return 2;
        if (attackMode == 1) return 3;
        return 4;
    }

    void chooseRandomAttack()
    {
        attackMode = rand() % 3;
    }

    void alphaTakeDamage(double damage)
    {
        alphaHealth -= damage;
        if (alphaHealth <= 0)
        {
            alphaHealth = 0;
            isActive = false;
            isAttacking = false;
            attack_index = 0;
        }
    }

    void show_alpha_moving()
    {
        if (alphaHealth <= 0)
        {
            if (dying_R_images.empty() || dying_L_images.empty())
                return;

            int idx = dead_index;
            if (idx >= (int)dying_R_images.size())
            {
                idx = (int)dying_R_images.size() - 1;
            }

            if (isright)
            {
                iShowImage(alphaPosition_X, alphaPosition_Y - 20, 220, 220, dying_R_images[idx]);
            }
            else
            {
                iShowImage(alphaPosition_X, alphaPosition_Y - 20, 220, 220, dying_L_images[idx]);
            }
            return;
        }

        if (!isActive)
            return;

        if (isAttacking)
        {
            vector<int>& attackR = currentAttackFramesRight();
            vector<int>& attackL = currentAttackFramesLeft();
            if (attackR.empty() || attackL.empty())
                return;

            int idx = attack_index;
            if (idx >= (int)attackR.size())
            {
                idx = (int)attackR.size() - 1;
            }

            if (isright)
            {
                iShowImage(alphaPosition_X, alphaPosition_Y - 30, 240, 240, attackR[idx]);
            }
            else
            {
                iShowImage(alphaPosition_X, alphaPosition_Y - 30, 240, 240, attackL[idx]);
            }
            return;
        }

        if (walking_R_images.empty() || walking_L_images.empty())
            return;

        int idx = movement_index % walking_R_images.size();
        if (isright)
        {
            iShowImage(alphaPosition_X, alphaPosition_Y, 180, 180, walking_R_images[idx]);
        }
        else
        {
            iShowImage(alphaPosition_X, alphaPosition_Y, 180, 180, walking_L_images[idx]);
        }
    }

    void move_alpha(Hero &hero1)
    {
        if (alphaHealth <= 0)
            return;

        if (!isActive)
            return;

        double characterX = hero1.characterPosition_X;
        double characterY = hero1.characterPosition_Y;
        bool inAttackRange = (abs(alphaPosition_X - characterX) < 120 && abs(alphaPosition_Y - characterY) < 80);

        if (inAttackRange && hero1.isAttacking)
        {
            alphaTakeDamage(hero1.attack_damage * 0.7);
        }

        if (inAttackRange)
        {
            if (!isAttacking)
            {
                chooseRandomAttack();
                isAttacking = true;
                attack_index = 0;
                attack_timer = 0;
            }
        }

        if (isAttacking)
        {
            attack_timer++;
            if (inAttackRange && attack_timer % 12 == 0)
            {
                hero1.takeDamage(currentAttackDamage());
                hero1.gettingHit = true;
            }
            return;
        }

        if (alphaPosition_X > characterX + 110)
        {
            alphaPosition_X -= alpha_speed;
            isright = false;
        }
        else if (alphaPosition_X < characterX - 110)
        {
            alphaPosition_X += alpha_speed;
            isright = true;
        }

        movement_index++;
        if (movement_index >= (int)walking_R_images.size())
        {
            movement_index = 0;
        }
    }

    void update_attack()
    {
        if (!isAttacking)
            return;

        vector<int>& attackR = currentAttackFramesRight();
        if (attackR.empty())
        {
            isAttacking = false;
            attack_index = 0;
            return;
        }

        attack_index++;
        if (attack_index >= (int)attackR.size())
        {
            attack_index = 0;
            isAttacking = false;
            attack_timer = 0;
        }
    }

    void update_dead()
    {
        if (alphaHealth > 0)
            return;

        dead_timer++;
        if (dead_timer > 4)
        {
            dead_timer = 0;
            dead_index++;
            if (dead_index >= (int)dying_R_images.size())
            {
                dead_index = (int)dying_R_images.size() - 1;
            }
        }
    }
};

#endif
