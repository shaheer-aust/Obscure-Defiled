#ifndef CLOUD_H
#define CLOUD_H

#include <iostream>
#include "character_functions/Hero.hpp"
using namespace std;

struct Cloud
{
	double x;
	double y;
	
	int cloudWidth;
	int cloudHeight;
	int cloudImage;
	bool isActive;

	void initCloud(double startX, double startY, int width, int height)
	{
		x = startX;
		y = startY;
		cloudWidth = width;
		cloudHeight = height;
		isActive = true;
		cloudImage = iLoadImage("resources\\Environment\\Cloud\\cloud.png");
	}

	void drawCloud(int currentLevel)
	{
		if (currentLevel != 1) return;
		if (!isActive) return;

		if (cloudImage != -1)
		{
			iShowImage(x, y, cloudWidth, cloudHeight, cloudImage);
		}
	}
};

#endif