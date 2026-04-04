#ifndef ICON_HPP
#define ICON_HPP

#include <iostream>
#include <vector>
#include "character_functions/Hero.hpp"

using namespace std;

struct Level2PowerUp
{
    int currentLevel = 0;
    int bottleImage = 0;
    vector<int> animationFrames;
    bool iconVisible = false;
    bool animationActive = false;
    bool animationDone = false;
    int currentFrame = 0;
    int animationTimer = 0;
    double iconX = 100.0;
    double iconY = 460.0;
    
    void init(int level)
    {
        currentLevel = level;
        if (level != 2 && level != 3)
        {
            iconVisible = false;
            animationActive = false;
            animationDone = false;
            return;
        }

        if (level == 2)
        {
            bottleImage = iLoadImage("resources\\Level_2\\powerUp\\Power Bottol\\image.png");
            animationFrames.clear();
            for (int i = 0; i <= 8; i++)
            {
                char path[200];
                sprintf_s(path, "resources\\Level_2\\powerUp\\Animition\\frame_%03d.png", i);
                animationFrames.push_back(iLoadImage(path));
            }
        }
        else if (level == 3)
        {
            bottleImage = iLoadImage("resources\\Level_3\\powerUp\\Power Bottol\\image.png");
            animationFrames.clear();
            for (int i = 0; i <= 8; i++)
            {
                char path[200];
                sprintf_s(path, "resources\\Level_3\\powerUp\\Animition\\frame_%03d.png", i);
                animationFrames.push_back(iLoadImage(path));
            }
        }
        
        iconVisible = false;
        animationActive = false;
        animationDone = false;
        currentFrame = 0;
        animationTimer = 0;
    }
    
    void updateAndDraw(int level, int killCount, double heroX, double heroY, bool boss1Defeated)
    {
        if (level != 2 && level != 3) return;
        
        bool conditionMet = false;
        if (level == 2 && killCount >= 3) conditionMet = true;
        if (level == 3 && boss1Defeated) conditionMet = true;

        if (!animationActive && !animationDone && conditionMet)
        {
            iconVisible = true;
        }

        if (iconVisible)
        {
            if (bottleImage != 0)
                iShowImage(iconX, iconY, 60, 60, bottleImage);
            
            iSetColor(255, 255, 255);
            iText(iconX - 25, iconY - 20, "Press P to Power Up", GLUT_BITMAP_HELVETICA_18);
        }

        if (animationActive)
        {
            if (!animationFrames.empty() && animationFrames[currentFrame] != -1)
            {
                // Draw animation centered on the hero X, but vertically locked
                int yPos = (currentLevel == 3) ? 65 : 80;
                iShowImage(heroX - 32, yPos, 200, 200, animationFrames[currentFrame]);
            }
            
            animationTimer++;
            int speedTarget = (currentLevel == 3) ? 25 : 9;
            if (animationTimer >= speedTarget) // Animation speed logic (slower for level 3)
            {
                animationTimer = 0;
                currentFrame++;
                if (currentFrame >= animationFrames.size())
                {
                    currentFrame = 0;
                    animationActive = false;
                    animationDone = true; // Loops one time then terminates
                }
            }
        }
    }
    
    bool handleKeyboard(unsigned char key, Hero& hero)
    {
        if (iconVisible && (key == 'p' || key == 'P'))
        {
            iconVisible = false;
            animationActive = true;
            currentFrame = 0;
            animationTimer = 0;
            
            // Apply actual power up effect
            if (currentLevel == 2)
            {
                hero.character_speed *= 1.15; // Increase movement speed by 15%
                hero.attack_damage *= 1.20;   // Increase damage to enemies by 20%
            }
            else if (currentLevel == 3)
            {
                hero.character_speed *= 1.20; // Increase movement speed by 20%
                hero.attack_damage *= 1.25;   // Increase damage to enemies by 25%
            }
            
            return true;
        }
        return false;
    }
    
    void shiftIcon(double dx)
    {
        // HUD element: locked to screen coordinates!
    }
};

#endif // ICON_HPP
