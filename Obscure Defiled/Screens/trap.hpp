#ifndef TRAP_H
#define TRAP_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "character_functions/Hero.hpp"

using namespace std;

struct FallingTrap
{
    double x;
    double y;
    double speed;
    int imageIndex;
    bool active;
    bool hasHitHero;
};

struct Trap
{
    vector<FallingTrap> traps;
    int trapImages[3];
    int trapWidth;
    int trapHeight;
    bool isActive;

    void initTrap(int startX, int startY, int width, int height)
    {
        trapWidth = width;
        trapHeight = height;
        isActive = true;
        
        trapImages[0] = iLoadImage("resources//obstacles//obstacles_resize//1.png"); 
        trapImages[1] = iLoadImage("resources//obstacles//obstacles_resize//2.png"); 
        trapImages[2] = iLoadImage("resources//obstacles//obstacles_resize//3.png"); 
        
        traps.clear();
        spawnTrap(); 
    }

    void shiftTraps(double dx)
    {
        for (int i = 0; i < (int)traps.size(); i++)
        {
            if (traps[i].active) traps[i].x += dx;
        }
    }

	void spawnTrap()
	{
		if (!isActive) return;

		// Clear previous trap data to keep the vector size at 1
		traps.clear();

		FallingTrap t;
		t.x = (rand() % (1280 - trapWidth));
		t.y = 720;

		// Speed increased another 2x (Original: 0.05 -> Current: 0.1 -> New: 0.2)
		t.speed = 0.2;

		t.imageIndex = rand() % 3;
		t.active = true;
		t.hasHitHero = false;
		traps.push_back(t);
	}

    void drawTrap()
    {
        if (!isActive) return;

        bool currentTrapStillActive = false;

        for (int i = 0; i < (int)traps.size(); i++)
        {
            if (traps[i].active)
            {
                currentTrapStillActive = true;

                if (trapImages[traps[i].imageIndex] != -1) {
                    iShowImage(traps[i].x, traps[i].y, trapWidth, trapHeight, trapImages[traps[i].imageIndex]);
                } else {
                    iSetColor(255, 0, 0); 
                    iFilledRectangle(traps[i].x, traps[i].y, trapWidth, trapHeight);
                }

                traps[i].y -= traps[i].speed;

                // If it falls off screen, deactivate
                if (traps[i].y + trapHeight < 0)
                {
                    traps[i].active = false;
                }
            }
        }

        // If the current trap is gone (hit hero or hit floor), spawn the next one
        if (!currentTrapStillActive)
        {
            spawnTrap();
        }
    }

	void checkCollision(Hero& hero)
	{
		if (!isActive) return;

		double heroCenterX = hero.characterPosition_X + (152.0 / 2.0);
		double heroCenterY = hero.characterPosition_Y + (152.0 / 2.0);
		double heroHalfW = 152.0 / 4.0;
		double heroHalfH = 152.0 / 2.0;

		for (int i = 0; i < (int)traps.size(); i++)
		{
			if (traps[i].active)
			{
				double trapCenterX = traps[i].x + (trapWidth / 2.0);
				double trapCenterY = traps[i].y + (trapHeight / 2.0);
				double trapHalfW = trapWidth / 2.0;
				double trapHalfH = trapHeight / 2.0;

				if (abs(heroCenterX - trapCenterX) < (heroHalfW + trapHalfW) &&
					abs(heroCenterY - trapCenterY) < (heroHalfH + trapHalfH))
				{
					if (!hero.isDead)
					{
						// Increased damage 2x: changed from 5 to 10
						hero.HeroHealth -= 10;

						if (hero.HeroHealth <= 0)
						{
							hero.HeroHealth = 0;
							hero.isDead = true;
							hero.dead_index = 0;
						}
						else
						{
							hero.gettingHit = true;
							hero.hit_index = 0;
						}

						traps[i].active = false;
					}
				}else{
                    hero.gettingHit = false;
                    hero.hit_index = 0;
                }
			}
		}
	}
};

#endif