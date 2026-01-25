#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#include <iostream>
#include <vector>
using namespace std;

struct MenuScreen
{
	bool lastFramePlayClicked = false;
	bool lastFrameSettingsClicked = false;
	bool lastFrameQuitClicked = false;

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
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
		iShowImage(SCREEN_WIDTH / 2 - (SCREEN_WIDTH * 0.4 / 2), SCREEN_HEIGHT / 2 + SCREEN_HEIGHT * 0.1, SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.4, images[1]);
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 200, BUTTON_WIDTH, BUTTON_HEIGHT, images[2]);
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, BUTTON_WIDTH, BUTTON_HEIGHT, images[3]);
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + 0, BUTTON_WIDTH, BUTTON_HEIGHT, images[4]);
	}
	// hover and click detection for menu
	void checkButtonHover(int mx, int my)
	{
		if (isQuitButtonClicked(mx, my) && !lastFrameQuitClicked)
		{
			PlaySound("resources//menu_screen//button_sound//button.wav", NULL, SND_ASYNC);
			lastFrameQuitClicked = true;
		}
		else if (!isQuitButtonClicked(mx, my))
		{
			lastFrameQuitClicked = false;
		}

		if (isSettingsButtonClicked(mx, my) && !lastFrameSettingsClicked)
		{
			PlaySound("resources//menu_screen//button_sound//button.wav", NULL, SND_ASYNC);
			lastFrameSettingsClicked = true;
		}
		else if (!isSettingsButtonClicked(mx, my))
		{
			lastFrameSettingsClicked = false;
		}

		if (isPlayButtonClicked(mx, my) && !lastFramePlayClicked)
		{
			PlaySound("resources//menu_screen//button_sound//button.wav", NULL, SND_ASYNC);
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
};
#endif
