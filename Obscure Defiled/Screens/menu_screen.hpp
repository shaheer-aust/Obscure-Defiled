#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#define BASE_SCREEN_WIDTH 1280
#define BASE_SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include <vector>
using namespace std;

struct MenuScreen
{
	int screenWidth;
	int screenHeight;
	
	MenuScreen() : screenWidth(BASE_SCREEN_WIDTH), screenHeight(BASE_SCREEN_HEIGHT) {}
	
	void updateScreenDimensions(int width, int height)
	{
		screenWidth = width;
		screenHeight = height;
	}
	
	bool lastFramePlayClicked = false;
	bool lastFrameSettingsClicked = false;
	bool lastFrameQuitClicked = false;
	long long lastPlayBlipTime = 0;
	long long lastSettingsBlipTime = 0;
	long long lastQuitBlipTime = 0;
	vector<int> initmenubar()
	{
		vector<int> images(5);
		images[0] = iLoadImage("resources//menu_screen//menu.jpg");
		images[1] = iLoadImage("resources//menu_screen//title.png");
		images[4] = iLoadImage("resources//menu_screen//Buttons//play.png");
		images[3] = iLoadImage("resources//menu_screen//Buttons//option.png");
		images[2] = iLoadImage("resources//menu_screen//Buttons//exit.png");
		return images;
	}

	void drawMenuScreen(vector<int> images)
	{
		iShowImage(0, 0, screenWidth, screenHeight, images[0]);
		iShowImage(screenWidth / 2 - (screenWidth * 0.4 / 2), screenHeight / 2 + screenHeight * 0.1, screenWidth * 0.4, screenHeight * 0.4, images[1]);
		iShowImage(screenWidth / 2 - BUTTON_WIDTH / 2, screenHeight / 2 - 200, BUTTON_WIDTH, BUTTON_HEIGHT, images[2]);
		iShowImage(screenWidth / 2 - BUTTON_WIDTH / 2, screenHeight / 2 - 100, BUTTON_WIDTH, BUTTON_HEIGHT, images[3]);
		iShowImage(screenWidth / 2 - BUTTON_WIDTH / 2, screenHeight / 2 + 0, BUTTON_WIDTH, BUTTON_HEIGHT, images[4]);
	}
	// hover and click detection for menu
	void checkButtonHover(int mx, int my)
	{
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
		long long currentTime = glutGet(GLUT_ELAPSED_TIME);

		if (isQuitButtonClicked(mx, my) && !lastFrameQuitClicked)
		{
			if (currentTime - lastQuitBlipTime > HOVER_COOLDOWN)
			{
				mciSendString("play ggsong from 0", NULL, 0, NULL);
				lastQuitBlipTime = currentTime;
			}
			lastFrameQuitClicked = true;
		}
		else if (!isQuitButtonClicked(mx, my))
		{
			lastFrameQuitClicked = false;
		}

		if (isSettingsButtonClicked(mx, my) && !lastFrameSettingsClicked)
		{
			if (currentTime - lastSettingsBlipTime > HOVER_COOLDOWN)
			{
				mciSendString("play ggsong from 0", NULL, 0, NULL);
				lastSettingsBlipTime = currentTime;
			}
			lastFrameSettingsClicked = true;
		}
		else if (!isSettingsButtonClicked(mx, my))
		{
			lastFrameSettingsClicked = false;
		}

		if (isPlayButtonClicked(mx, my) && !lastFramePlayClicked)
		{
			if (currentTime - lastPlayBlipTime > HOVER_COOLDOWN)
			{
				mciSendString("play ggsong from 0", NULL, 0, NULL);
				lastPlayBlipTime = currentTime;
			}
			lastFramePlayClicked = true;
		}
		else if (!isPlayButtonClicked(mx, my))
		{
			lastFramePlayClicked = false;
		}
	}
	// butoons
	bool isQuitButtonClicked(int mx, int my)
	{
		int buttonX = screenWidth / 2 - BUTTON_WIDTH / 2;
		int buttonY = screenHeight / 2 - 200;

		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	bool isSettingsButtonClicked(int mx, int my)
	{
		int buttonX = screenWidth / 2 - BUTTON_WIDTH / 2;
		int buttonY = screenHeight / 2 - 100;
		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	bool isPlayButtonClicked(int mx, int my)
	{
		int buttonX = screenWidth / 2 - BUTTON_WIDTH / 2;
		int buttonY = screenHeight / 2 + 0;

		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}
};
#endif
