#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef Level_2_GAME_SCREEN_H
#define Level_2_GAME_SCREEN_H

// Forward declaration of idle index getter
extern int getIdleIndex();
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 242
#define BUTTON_HEIGHT 62
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include "enemy_functions\\enemy.hpp"
#include "character_functions\\Hero.hpp"
#include <vector>
using namespace std;

struct Lvl_2_GameScreen
{
    int bg_image;
    vector<int> health_bar_images;
    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Boss boss;
    Boss boss2;
    Hero hero1;
    bool spacePressed = false;
    bool rightPressed = false;
    bool leftPressed = false;
    int x = 0;
    double jumpVelocity = 0.0;
    double gravity = 2.0;
    double base_gravity = 5;
    double groundY = 100.0;
    double bg_speed = 4.0;
    bool enemy2Spawned = false; // Track if enemy2 has been spawned
    bool enemy3Spawned = false; // Track if enemy3 has been spawned
    bool bossSpawned = false;   // Track if boss has been spawned
    bool boss2Spawned = false;  // Track if boss2 has been spawned

    void initgame_screen()
    {
        bg_image = (iLoadImage("resources//game_screen//level_2//bg_2//Screen_bg_for_2nd_round.png"));
        hero1.init_character_images();
        groundY = hero1.characterPosition_Y;
        enemy1.initenemy(1);          // Initialize Small enemy 1
        enemy2.initenemy(2);          // Initialize Small enemy 2
        enemy2.isActive = false;      // Start with enemy2 inactive
        enemy2.enemyPosition_X = 64;  // Position enemy2 on the right side
        enemy3.initenemy(1);          // Initialize enemy3 (type 1)
        enemy3.isActive = false;      // Start with enemy3 inactive
        enemy3.enemyPosition_X = 128; // Position enemy3 further right
        boss.initboss();              // Initialize boss
        boss.isActive = false;        // Start with boss inactive
        boss2.initboss();             // Initialize boss2
        boss2.isActive = false;       // Start with boss2 inactive
        boss2.bossPosition_X = SCREEN_WIDTH - 256; // Offset boss2 position
        init_health_bar_images();
    }

    void init_health_bar_images()
    {
        for (int i = 0; i <= 100; i += 10)
        {
            char a[200];
            sprintf_s(a, "resources/Health Bar//%d Percent//resize_health_bar_%d.png", i, i);
            health_bar_images.push_back(iLoadImage(a));
        }
    }

    void startJump()
    {
        if (!hero1.isJumping)
        {
            hero1.isJumping = true;
            hero1.isMoving = false;
            // record the ground position to return to
            groundY = hero1.characterPosition_Y;
            jumpVelocity = 35.0; // initial jump impulse
            gravity = base_gravity;
            hero1.jump_index = 0;
        }
    }

    void updateJumpPhysics()
    {
        if (hero1.isJumping)
        {
            if (rightPressed)
            {
                x -= bg_speed;
                if (x <= -SCREEN_WIDTH)
                {
                    x = 0;
                }
                hero1.characterPosition_X += hero1.character_speed - 5;
                hero1.isright = true;
            }
            else if (leftPressed)
            {
                x += bg_speed;
                if (x >= SCREEN_WIDTH)
                {
                    x = 0;
                }
                hero1.characterPosition_X -= hero1.character_speed - 5;
                hero1.isright = false;
            }
            // apply vertical movement
            hero1.characterPosition_Y += jumpVelocity;
            jumpVelocity -= gravity;

            // advance jump animation frame
            if (hero1.isright)
            {
                hero1.jump_index++;
                if (hero1.jump_index >= (int)hero1.character_jump_R_images.size())
                {
                    hero1.jump_index = 0;
                }
            }
            else
            {
                hero1.jump_index++;
                if (hero1.jump_index >= (int)hero1.character_jump_L_images.size())
                {
                    hero1.jump_index = 0;
                }
            }
            // landing check
            if (hero1.characterPosition_Y <= groundY)
            {
                hero1.characterPosition_Y = groundY;
                hero1.isJumping = false;
                hero1.isMoving = true;
                jumpVelocity = 0.0;
                gravity = base_gravity;
                hero1.jump_index = 0;
            }
        }
    }

    void handleSpecialKeyboard(unsigned char key)
    {
        if (key == GLUT_KEY_UP)
        {
            startJump();
        }
        else if (key == GLUT_KEY_DOWN)
        {
        }
        else if (key == GLUT_KEY_LEFT)
        {
            leftPressed = true;
            hero1.isMoving = true;
            hero1.isright = false;
        }
        else if (key == GLUT_KEY_RIGHT)
        {
            rightPressed = true;
            hero1.isright = true;
            hero1.isMoving = true;
        }
    }

    void drawgame_screen()
    {
        iShowImage(-SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_image);
        iShowImage(x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_image);
        iShowImage(SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg_image);

        iShowImage(SCREEN_WIDTH / 2 - (275 / 2), SCREEN_HEIGHT - 150, 275, 200, health_bar_images[(hero1.HeroHealth / 10)]);

        // Draw boss health bar if boss is active
        if (boss.isActive && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(200.0, boss.bossHealth));
            int frameIndex = (int)floor((currentHealth / 200.0) * 15);
            iShowImage(boss.bossPosition_X - 10, boss.bossPosition_Y + 100, 122, 20, boss.boss_health_bar_images[frameIndex]);
        }
        if (boss2.isActive && !boss2.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(200.0, boss2.bossHealth));
            int frameIndex = (int)floor((currentHealth / 200.0) * 15);
            iShowImage(boss2.bossPosition_X - 10, boss2.bossPosition_Y + 100, 122, 20, boss2.boss_health_bar_images[frameIndex]);
        }
        if (enemy1.isActive && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(100.0, enemy1.enemyHealth));
            int frameIndex = (int)floor((currentHealth / 100.0) * 15);
            iShowImage(enemy1.enemyPosition_X - 2, enemy1.enemyPosition_Y + 100, 50, 15, boss.boss_health_bar_images[frameIndex]);
        }
        if (enemy2.isActive && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(100.0, enemy2.enemyHealth));
            int frameIndex = (int)floor((currentHealth / 100.0) * 15);
            iShowImage(enemy2.enemyPosition_X - 2, enemy2.enemyPosition_Y + 100, 50, 15, boss.boss_health_bar_images[frameIndex]);
        }
        if (enemy3.isActive && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(100.0, enemy3.enemyHealth));
            int frameIndex = (int)floor((currentHealth / 100.0) * 15);
            iShowImage(enemy3.enemyPosition_X - 2, enemy3.enemyPosition_Y + 100, 50, 15, boss.boss_health_bar_images[frameIndex]);
        }
        hero1.show_chracter_moving();
        enemy1.show_enemy_moving();
        enemy2.show_enemy_moving();
        enemy3.show_enemy_moving();
        boss.show_boss_moving();
        boss2.show_boss_moving();
    }
};

#endif
