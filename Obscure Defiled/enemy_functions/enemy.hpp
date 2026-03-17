#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
extern void takeDamage();
#ifndef ENEMY_H
#define ENEMY_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>
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
    double enemyPosition_X = SCREEN_WIDTH - 64;
    double enemyPosition_Y = 100.0;
    double enemyHealth = 100.0;
    bool isright = false;
    int enemy_movement_index = 0;
    double enemy_speed = 8.0;
    bool enemyGettingHit = false;
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
        isActive = true; // Whether this enemy is currently active in the game
		this->level = level;
        enemyType = type;
        init_enemy_images(level);
    }
    void enemy_takeDamage(double damage)
    {
        cout << "Enemy takes damage: " << damage << endl;
        enemyHealth -= damage;
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
		
		
        // Load enemy images based on type
        if (enemyType == 1)
        {
            if (level == 1)
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
            else if (level == 2)
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
            }
        }
    }
    void show_enemy_moving()
    {
        if (!isActive)
            return; // Don't show inactive enemies

		if (enemy_idle_R_images.empty() || enemy_idle_L_images.empty())
			return;

		int currentIdx = enemy_movement_index;
		cout << " index: " << currentIdx << endl;
        if (isright)
        {
			iShowImage(enemyPosition_X, enemyPosition_Y, level==1?100:150, 100, enemy_idle_R_images[currentIdx]);
        }
        else
        {
			iShowImage(enemyPosition_X, enemyPosition_Y, level==1?100:150, 100, enemy_idle_L_images[currentIdx]);
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
        if (abs(enemyPosition_X - characterX) <= 51 && (enemyPosition_Y == characterY) && isActive)
        {
            if (hero1.isAttacking)
            {
                hero1.gettingHit = false;
                enemy_takeDamage(hero1.attack_damage); // Hero attack damage (boosted by power-up)
            }
            else
            {
                hero1.gettingHit = true;
                hero1.takeDamage(2); // hero takes 2 damage when hit by enemy
            }
        }
        else
        {
            hero1.gettingHit = false;
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
        if (abs(bossPosition_X - characterX) < 81 && (bossPosition_Y == characterY))
        {
            if (hero1.isAttacking)
            {
                bosstakeDamage(hero1.attack_damage * 0.6); // Hero attack damage on boss (60% of hero attack_damage, boosted by power-up)
                hero1.gettingHit = false;
            }
            else
            {
                hero1.takeDamage(0.8);
                cout << "Boss hit! Hero health: " << hero1.HeroHealth << endl;
                hero1.gettingHit = true;
            }
        }
        else
        {
            hero1.gettingHit = false;
        }
        // boss attack check
        if (abs(bossPosition_X - characterX) < 81 && (bossPosition_Y == characterY))
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

#endif
