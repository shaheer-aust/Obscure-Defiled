#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>
#include <vector>
using namespace std;

struct MenuScreen
{

	vector<int> initmenubar()
	{
		vector<int> images(2);
		images[0] = iLoadImage("resources//menu_screen//menu.jpg");
		images[1] = (iLoadImage("resources//menu_screen//title.png"));
		// images->push_back(iLoadImage("resources//menu_screen//play_button.png"));
		// images->push_back(iLoadImage("resources//menu_screen//settings_button.png"));
		// images->push_back(iLoadImage("resources//menu_screen//exit_button.png"));
		return images;
	}
	void drawMenuScreen(vector<int> images)
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
		iShowImage(SCREEN_WIDTH / 2 - (SCREEN_WIDTH * 0.4 / 2), SCREEN_HEIGHT / 2 + SCREEN_HEIGHT * 0.1, SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.4, images[1]);
		iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 100, "EXIT");
		iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 50, "SETTINGS");
		iText(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "PLAY");
	}

	// butoons
	bool isQuitButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - 50;
		int buttonY = SCREEN_HEIGHT / 2 - 100;
		int buttonWidth = 100;
		int buttonHeight = 30;

		return (mx >= buttonX && mx <= buttonX + buttonWidth &&
				my >= buttonY && my <= buttonY + buttonHeight);
	}

	bool isSettingsButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - 50;
		int buttonY = SCREEN_HEIGHT / 2 - 50;
		int buttonWidth = 100;
		int buttonHeight = 30;

		return (mx >= buttonX && mx <= buttonX + buttonWidth &&
				my >= buttonY && my <= buttonY + buttonHeight);
	}

	bool isPlayButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - 50;
		int buttonY = SCREEN_HEIGHT / 2;
		int buttonWidth = 100;
		int buttonHeight = 30;

		return (mx >= buttonX && mx <= buttonX + buttonWidth &&
				my >= buttonY && my <= buttonY + buttonHeight);
	}
};
#endif