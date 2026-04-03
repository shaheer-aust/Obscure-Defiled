#ifndef LIGHTNING_H
#define LIGHTNING_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include "character_functions/Hero.hpp"
using namespace std;

struct LightningBolt
{
	double x;
	double y;
	double speed;
	int width;
	int height;
	bool active;
	bool hasHit;
	int imageIndex;
};

struct Lightning
{
	LightningBolt bolt;
	vector<int> lightningImages;
	int boltWidth;
	int boltHeight;
	double baseSpeed;
	bool isActive;

	void initLightning(int width, int height, double speed)
	{
		boltWidth = width;
		boltHeight = height;
		baseSpeed = speed;
		isActive = true;

		lightningImages.clear();
		for (int i = 0; i <= 8; i++)
		{
			char path[200];
			sprintf_s(path, "resources\\Environment\\Cloud\\%d.png", i);
			lightningImages.push_back(iLoadImage(path));
		}

		spawnBolt(baseSpeed);
	}

	void spawnBolt(double inSpeed)
	{
		bolt.x = rand() % (SCREEN_WIDTH - boltWidth);
		// Spawn just above the screen instead of miles away
		bolt.y = SCREEN_HEIGHT + 10 + (rand() % 300);
		// Hardcoded solid integer dropping speed with no random variance 
		bolt.speed = 2.0; 
		bolt.width = boltWidth;
		bolt.height = boltHeight;
		bolt.active = true;
		bolt.hasHit = false;
		bolt.imageIndex = rand() % 8; // pick a random still image
	}

	void drawLightning(int currentLevel)
	{
		if (currentLevel != 1 && currentLevel != 2) return;
		if (!isActive) return;

		if (!bolt.active)
		{
			spawnBolt(baseSpeed); // respawn next bolt
			return;
		}

		if (!lightningImages.empty() && lightningImages[bolt.imageIndex] != -1)
		{
			iShowImage(bolt.x, bolt.y, bolt.width, bolt.height, lightningImages[bolt.imageIndex]);
		}
		else
		{
			iSetColor(255, 255, 0);
			iFilledRectangle(bolt.x, bolt.y, bolt.width, bolt.height);
		}

		bolt.y -= bolt.speed;

		// Respawn when it reaches 100 pixels from the bottom of the screen
		if (bolt.y <= 100.0)
		{
			spawnBolt(baseSpeed);
		}
	}

	void checkCollision(Hero& hero, int currentLevel)
	{
		if (currentLevel != 1 && currentLevel != 2) return;
		if (!isActive || !bolt.active || bolt.hasHit) return;

		double heroCenterX = hero.characterPosition_X + (152.0 / 2.0);
		double heroCenterY = hero.characterPosition_Y + (152.0 / 2.0);
		double heroHalfW = 152.0 / 4.0;
		double heroHalfH = 152.0 / 2.0;

		double boltCenterX = bolt.x + (bolt.width / 2.0);
		double boltCenterY = bolt.y + (bolt.height / 2.0);

		// Simple AABB overlap check
		bool hitX = (boltCenterX >= hero.characterPosition_X) &&
		            (boltCenterX <= hero.characterPosition_X + 152.0);
		bool hitY = (boltCenterY >= hero.characterPosition_Y) &&
		            (boltCenterY <= hero.characterPosition_Y + 152.0);

		if (hitX && hitY)
		{
			hero.HeroHealth -= 10;
			if (hero.HeroHealth < 0) hero.HeroHealth = 0;
			bolt.hasHit = true;
			bolt.active = false;
		}
	}
};

#endif