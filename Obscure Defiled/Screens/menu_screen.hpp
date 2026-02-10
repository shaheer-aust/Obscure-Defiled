#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 242
#define BUTTON_HEIGHT 62
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include <vector>
using namespace std;

struct MenuScreen
{
	bool lastFramePlayClicked = false;
	bool lastFrameSettingsClicked = false;
	bool lastFrameQuitClicked = false;
	bool lastFrameCreditsClicked = false;
	long long lastPlayBlipTime = 0;
	long long lastSettingsBlipTime = 0;
	long long lastQuitBlipTime = 0;
	long long lastCreditsBlipTime = 0;
	vector<int> initmenubar()
	{
		vector<int> images(6);
		images[0] = iLoadImage("resources//menu_screen//menu.jpg");
		images[1] = iLoadImage("resources//menu_screen//title.png");
		images[4] = iLoadImage("resources//menu_screen//Buttons//play.png");
		images[3] = iLoadImage("resources//menu_screen//Buttons//option.png");
		images[2] = iLoadImage("resources//menu_screen//Buttons//exit.png");
		images[5] = iLoadImage("resources//menu_screen//Buttons//credits.png");
		return images;
	}

	void drawMenuScreen(vector<int> images)
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
		iShowImage(SCREEN_WIDTH / 2 - (SCREEN_WIDTH * 0.4 / 2), SCREEN_HEIGHT / 2 + SCREEN_HEIGHT * 0.1, SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.4, images[1]);
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 200, BUTTON_WIDTH, BUTTON_HEIGHT, images[2]);
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, BUTTON_WIDTH, BUTTON_HEIGHT, images[3]);
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + 0, BUTTON_WIDTH, BUTTON_HEIGHT, images[4]);
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + 100, BUTTON_WIDTH, BUTTON_HEIGHT, images[5]);
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

		if (isCreditsButtonClicked(mx, my) && !lastFrameCreditsClicked)
		{
			if (currentTime - lastCreditsBlipTime > HOVER_COOLDOWN)
			{
				mciSendString("play ggsong from 0", NULL, 0, NULL);
				lastCreditsBlipTime = currentTime;
			}
			lastFrameCreditsClicked = true;
		}
		else if (!isCreditsButtonClicked(mx, my))
		{
			lastFrameCreditsClicked = false;
		}
	}
	// butoons
	bool isQuitButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int buttonY = SCREEN_HEIGHT / 2 - 200;

		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	bool isSettingsButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int buttonY = SCREEN_HEIGHT / 2 - 100;
		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	bool isPlayButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int buttonY = SCREEN_HEIGHT / 2 + 0;

		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	bool isCreditsButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int buttonY = SCREEN_HEIGHT / 2 + 100;

		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}
};
#endif
