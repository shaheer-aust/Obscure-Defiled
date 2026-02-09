#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include <vector>
using namespace std;

struct MenuScreen
{
	int screenWidth;
	int screenHeight;
	
	MenuScreen() : screenWidth(1280), screenHeight(720) {}
	
	void updateScreenDimensions(int width, int height)
	{
		screenWidth = width;
		screenHeight = height;
	}
	
	// Responsive dimensions based on screen size
	int getButtonWidth() { return (int)(screenWidth * 0.23); }
	int getButtonHeight() { return (int)(screenHeight * 0.125); }
	int getTitleWidth() { return (int)(screenWidth * 0.4); }
	int getTitleHeight() { return (int)(screenHeight * 0.4); }
	
	// Responsive positions
	int getTitleX() { return screenWidth / 2 - getTitleWidth() / 2; }
	int getTitleY() { return (int)(screenHeight / 2 + screenHeight * 0.1); }
	
	int getQuitButtonX() { return screenWidth / 2 - getButtonWidth() / 2; }
	int getQuitButtonY() { return (int)(screenHeight / 2 - screenHeight * 0.28); }
	
	int getSettingsButtonX() { return screenWidth / 2 - getButtonWidth() / 2; }
	int getSettingsButtonY() { return (int)(screenHeight / 2 - screenHeight * 0.14); }
	
	int getPlayButtonX() { return screenWidth / 2 - getButtonWidth() / 2; }
	int getPlayButtonY() { return screenHeight / 2; }
	
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
		iShowImage(getTitleX(), getTitleY(), getTitleWidth(), getTitleHeight(), images[1]);
		iShowImage(getQuitButtonX(), getQuitButtonY(), getButtonWidth(), getButtonHeight(), images[2]);
		iShowImage(getSettingsButtonX(), getSettingsButtonY(), getButtonWidth(), getButtonHeight(), images[3]);
		iShowImage(getPlayButtonX(), getPlayButtonY(), getButtonWidth(), getButtonHeight(), images[4]);
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
		int buttonX = getQuitButtonX();
		int buttonY = getQuitButtonY();

		return (mx >= buttonX && mx <= buttonX + getButtonWidth() &&
				my >= buttonY && my <= buttonY + getButtonHeight());
	}

	bool isSettingsButtonClicked(int mx, int my)
	{
		int buttonX = getSettingsButtonX();
		int buttonY = getSettingsButtonY();
		return (mx >= buttonX && mx <= buttonX + getButtonWidth() &&
				my >= buttonY && my <= buttonY + getButtonHeight());
	}

	bool isPlayButtonClicked(int mx, int my)
	{
		int buttonX = getPlayButtonX();
		int buttonY = getPlayButtonY();

		return (mx >= buttonX && mx <= buttonX + getButtonWidth() &&
				my >= buttonY && my <= buttonY + getButtonHeight());
	}
};
#endif
