#ifndef TRAP_H
#define TRAP_H

#include <iostream>
#include <vector>
#include "character_functions/Hero.hpp"

using namespace std;

struct Trap
{
    int trapPosition_X;
    int trapPosition_Y;
    int trapWidth;
    int trapHeight;
    bool isActive;
    int trapImage; // or a vector if animated, but let's stick to one static image for now
    bool hasHitHero; 

    void initTrap(int startX, int startY, int width, int height)
    {
        trapPosition_X = startX;
        trapPosition_Y = startY;
        trapWidth = width;
        trapHeight = height;
        isActive = true;
        hasHitHero = false;
        
        // Load the first obstacle image
        trapImage = iLoadImage("resources//obstacles//obstacles_resize//obstacle_1.png"); 
    }

    void drawTrap()
    {
        if (isActive)
        {
            if (trapImage != -1) {
                iShowImage(trapPosition_X, trapPosition_Y, trapWidth, trapHeight, trapImage);
            } else {
                // Fallback draw a red rectangle if the image failed to load
                iSetColor(255, 0, 0); 
                iFilledRectangle(trapPosition_X, trapPosition_Y, trapWidth, trapHeight);
            }
        }
    }

    void checkCollision(Hero& hero)
    {
        if (isActive)
        {
            // Calculate center points and half-sizes for AABB collision
            // Hero images are drawn using 152x152
            double heroCenterX = hero.characterPosition_X + (152.0 / 2.0);
            double heroCenterY = hero.characterPosition_Y + (152.0 / 2.0);
            double heroHalfW = 152.0 / 2.0;
            double heroHalfH = 152.0 / 2.0;

            double trapCenterX = trapPosition_X + (trapWidth / 2.0);
            double trapCenterY = trapPosition_Y + (trapHeight / 2.0);
            double trapHalfW = trapWidth / 2.0;
            double trapHalfH = trapHeight / 2.0;

            // Simple box collision
            if (abs(heroCenterX - trapCenterX) < (heroHalfW + trapHalfW) &&
                abs(heroCenterY - trapCenterY) < (heroHalfH + trapHalfH))
            {
                if (!hasHitHero && !hero.isDead) // Only hit once per continuous touch
                {
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
                    hasHitHero = true;
                }
            }
            else
            {
                // Reset hit flag when hero is no longer touching the trap
                hasHitHero = false;
            }
        }
    }
};

#endif
