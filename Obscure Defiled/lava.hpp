#ifndef LAVA_H
#define LAVA_H

#include <iostream>
#include <cmath>
#include <vector>
#include "character_functions/Hero.hpp"

using namespace std;

struct Lava
{
	double x;
	double y;
	double speed;
	int lavaWidth;
	int lavaHeight;
	bool isActive;

	// Image array and animation variables
	vector<int> lavaImages;
	int frameIndex = 0;
	int frameTimer = 0;

	// Call this once to set up the lava initially
	void initLava(double startX, double startY, int width, int height, double moveSpeed)
	{
		x = startX;
		y = startY;
		lavaWidth = width *1.5;
		lavaHeight = height;
		speed = moveSpeed *2.5;
		isActive = true;
		frameIndex = 0;
		frameTimer = 0;

		// Clear array in case of re-initialization
		lavaImages.clear();

		// Load your 36 lava animation frames (0 to 35)
		for (int i = 0; i <= 35; i++)
		{
			char imagePath[200];
			// Use %03d so it correctly formats frame_000.png to frame_035.png
			sprintf_s(imagePath, "resources//lava//frame_%03d.png", i);
			lavaImages.push_back(iLoadImage(imagePath));
		}
	}

	// Only spawns the lava if the game is currently on level 3
	void spawnLava(double startX, double startY, int currentLevel)
	{
		if (currentLevel != 3) return; // Fixed typo here (was 35)

		x = startX;
		y = startY;
		isActive = true;
	}

	// Pass the current level to ensure it only draws and moves on level 3
	void drawLava(int currentLevel)
	{
		if (currentLevel != 3) return; // Level 3 restriction
		if (!isActive) return;

		// Draw the lava using the animated image array if it successfully loaded
		if (!lavaImages.empty() && lavaImages[0] != -1) {
			iShowImage(x, y, lavaWidth, lavaHeight, lavaImages[frameIndex]);

			// Handle Animation looping
			frameTimer++;
			if (frameTimer >= 5) // Change '5' to adjust animation speed (higher = slower)
			{
				frameIndex++;
				if (frameIndex >= lavaImages.size())
				{
					frameIndex = 0;
				}
				frameTimer = 0;
			}
		}
		else {
			// Fallback: draw an orange-red rectangle if images are missing
			iSetColor(255, 69, 0);
			iFilledRectangle(x, y, lavaWidth, lavaHeight);
		}

		// Move the lava towards the left side
		x -= speed;

		// Make it disappear once it fully reaches past the far left screen
		if (x + lavaWidth < 0)
		{
			isActive = false;
		}
	}

	void checkCollision(Hero& hero)
	{
		if (hero.level != 3) return; // Level 3 restriction
		if (!isActive) return;

		// Setup Hero bounding boxes identically to your Trap logic
		double heroCenterX = hero.characterPosition_X + (152.0 / 2.0);
		double heroCenterY = hero.characterPosition_Y + (152.0 / 2.0);
		double heroHalfW = 152.0 / 4.0;
		double heroHalfH = 152.0 / 2.0;

		// Setup Lava bounding boxes
		double lavaCenterX = x + (lavaWidth / 2.0);
		double lavaCenterY = y + (lavaHeight / 2.0);
		double lavaHalfW = lavaWidth / 2.0;
		double lavaHalfH = lavaHeight / 2.0;

		// AABB Collision Detection
		if (abs(heroCenterX - lavaCenterX) < (heroHalfW + lavaHalfW) &&
			abs(heroCenterY - lavaCenterY) < (heroHalfH + lavaHalfH))
		{
			if (!hero.isDead)
			{
				// Same damage as traps (10 damage)
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

				// Make the lava disappear after successfully hitting the hero
				isActive = false;
			}
		}
		else
		{
			// Reset getting hit state when not colliding, matching your trap logic
			if (!hero.isDead && hero.gettingHit)
			{
				hero.gettingHit = false;
				hero.hit_index = 0;
			}
		}
	}
};

#endif