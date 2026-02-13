#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef CREDIT_SCREEN_HPP
#define CREDIT_SCREEN_HPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define BACK_BUTTON 81
#define HOVER_COOLDOWN 300 // milliseconds

#include <iostream>
#include <vector>
using namespace std;
struct Credit_screen
{
	vector<int> credit_images; // holds the credit picture
	long long lastBackBlipTime = 0;
	bool lastFrameBackClicked = false;
	void initcreditbar()
	{
		credit_images.push_back(iLoadImage("resources//credit//credit_info.png"));
		credit_images.push_back(iLoadImage("resources//menu_screen//Buttons//back.png"));
		// Load images or resources needed for the credit screen
	}
	void drawcredit_screen()
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, credit_images[0]);
		iShowImage(20, SCREEN_HEIGHT - BACK_BUTTON - 20, BACK_BUTTON, BACK_BUTTON, credit_images[1]);
		// Additional drawing code for credits can be added here
	}
	// back button hover and click detection for settings
	bool isBackButtonClicked(int mx, int my)
	{
		return (mx >= 20 && mx <= BACK_BUTTON + 20 && my >= SCREEN_HEIGHT - (BACK_BUTTON + 20) && my <= SCREEN_HEIGHT);
	}
	// hover detection
	void checkButtonHover(int mx, int my)
	{
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
		long long currentTime = glutGet(GLUT_ELAPSED_TIME);

		if (isBackButtonClicked(mx, my) && !lastFrameBackClicked)
		{
			if (currentTime - lastBackBlipTime > HOVER_COOLDOWN)
			{
				mciSendString("play ggsong from 0", NULL, 0, NULL);
				lastBackBlipTime = currentTime;
			}
			lastFrameBackClicked = true;
		}
		else if (!isBackButtonClicked(mx, my))
		{
			lastFrameBackClicked = false;
		}
	}
}

;
#endif
