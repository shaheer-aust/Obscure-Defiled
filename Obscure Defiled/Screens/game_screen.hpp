#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

// Forward declaration of idle index getter
extern int getIdleIndex();
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 242
#define BUTTON_HEIGHT 62
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include "enemy_functions\enemy.hpp";
#include "character_functions\Hero.hpp";
#include <vector>
using namespace std;
struct GameScreen
{
    vector<int> images;
    vector<int> health_bar_images;
    Enemy enemy1;
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
 
    void initgame_screen()
    {
        images.push_back(iLoadImage("resources//game_screen//level_1/bg_1//screen_for_level_1_new.jpg"));
        init_character_images();
        groundY = hero1.characterPosition_Y;
        enemy1.initenemy();
        init_health_bar_images();
        hero1.init_fighting_images();
        hero1.init_idle_hit_images();
		hero1.HeroHealth = 100;
        // iSetTimer(200, idle_animation);
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
    void init_character_images()
    {
        // Load character idle images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Idle//idle_right_%d.png", i);
            hero1.character_idle_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Idle//idle_left_%d.png", i);
            hero1.character_idle_L_images.push_back(iLoadImage(a));
        }
        // Load character run images
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Walking//walking_left_%d.png", i);
            hero1.character_run_L_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal/With Knife//Walking//walking_right_%d.png", i);
            hero1.character_run_R_images.push_back(iLoadImage(a));
        }
        // load character jump images if needed
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Jumping//jumping_right_%d.png", i);
            hero1.character_jump_R_images.push_back(iLoadImage(a));
        }
        for (int i = 1; i <= 4; i++)
        {
            char a[200];
            sprintf_s(a, "resources//Main_Character//Normal//With Knife//Jumping//jumping_left_%d.png", i);
            hero1.character_jump_L_images.push_back(iLoadImage(a));
        }
    }
    void show_character_idle()
    {
        int currentIdx = getIdleIndex();
        if (hero1.isright)
        {
            iShowImage(hero1.characterPosition_X, hero1.characterPosition_Y, 96, 96, hero1.character_idle_R_images[currentIdx]);
        }
        else
        {
            iShowImage(hero1.characterPosition_X, hero1.characterPosition_Y, 96, 96, hero1.character_idle_L_images[currentIdx]);
        }
    }
    void show_character_run()
    {

        if (hero1.movement_index >= hero1.character_run_R_images.size())
        {

            hero1.movement_index = 0;
        }
        if (hero1.isright)
        {
            iShowImage(hero1.characterPosition_X, hero1.characterPosition_Y, 96, 96, hero1.character_run_R_images[hero1.movement_index]);
        }
        else
        {
            iShowImage(hero1.characterPosition_X, hero1.characterPosition_Y, 96, 96, hero1.character_run_L_images[hero1.movement_index]);
        }
        // movement_index++;
    }

    void resetMovement()
    {
        // isMoving = false;
        hero1.movement_index = 0;
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

    void updatePhysics()
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
                hero1.characterPosition_X += hero1.character_speed+5;
                hero1.isright = true;
            }
            else if (leftPressed)
            {
                x += bg_speed;
                if (x >= SCREEN_WIDTH)
                {
                    x = 0;
                }
                hero1.characterPosition_X -= hero1.character_speed+5;
                hero1.isright = false;
            }
            // apply vertical movement
            hero1.characterPosition_Y += jumpVelocity;
            jumpVelocity -= gravity;

            // advance jump animation frame
            if (hero1.isright)
            {
                hero1.jump_index++;
                if (hero1.jump_index >= hero1.character_jump_R_images.size())
                {
                    hero1.jump_index = 0;
                }
            }
            else
            {
                hero1.jump_index++;
                if (hero1.jump_index >= hero1.character_jump_L_images.size())
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

    void show_character_jump1()
    {
        // choose frame based on direction and jump_index
        if (hero1.isright)
        {
            if (!hero1.character_jump_R_images.empty())
                iShowImage(hero1.characterPosition_X, hero1.characterPosition_Y, 96, 96, hero1.character_jump_R_images[hero1.jump_index]);
        }
        else
        {
            if (!hero1.character_jump_L_images.empty())
                iShowImage(hero1.characterPosition_X, hero1.characterPosition_Y, 96, 96, hero1.character_jump_L_images[hero1.jump_index]);
        }
    }

    void handleSpecialKeyboard(unsigned char key)
    {
        // Handle special keyboard input for game controls (e.g., arrow keys for movement)

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

        iShowImage(-SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        iShowImage(x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        iShowImage(SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
        // Additional drawing code for settings can be added here
        //cout << "Hero Health: " << hero1.HeroHealth << endl;
        iShowImage(SCREEN_WIDTH/2-(275/2), SCREEN_HEIGHT - 150, 275, 200, health_bar_images[(hero1.HeroHealth / 10)]);
        if (hero1.isAttacking)
        {
            hero1.show_character_attack();
        }
        else if (hero1.isJumping)
        {
            show_character_jump1();
        }
        else if (hero1.isMoving)
        {
            show_character_run();
		}
		else if (hero1.gettingHit){
			
			hero1.show_getting_hit();
		}
        else
        {
            show_character_idle();
        }
		enemy1.show_enemy_moving();
    }
};

#endif