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
	enum ButtonSelection { QUIT = 0, CREDITS = 1, PLAY = 3, SETTINGS = 2 };

	bool lastFramePlayClicked = false;
	bool lastFrameSettingsClicked = false;
	bool lastFrameQuitClicked = false;
	bool lastFrameCreditsClicked = false;
	long long lastPlayBlipTime = 0;
	long long lastSettingsBlipTime = 0;
	long long lastQuitBlipTime = 0;
	long long lastCreditsBlipTime = 0;
	ButtonSelection currentSelectedButton = PLAY;
	int hoveredButton = -1; // -1 = none, 0 = quit, 1 = credits, 2 = play, 3 = settings
	vector<int> images;
	void initmenubar()
	{
		
		images.push_back(iLoadImage("resources//menu_screen//menu.jpg"));
		images.push_back(iLoadImage("resources//menu_screen//title.png"));
		// Regular button images
		images.push_back(iLoadImage("resources//menu_screen//Buttons//exit.png"));
		images.push_back(iLoadImage("resources//menu_screen//Buttons//option.png"));
		images.push_back(iLoadImage("resources//menu_screen//Buttons//play.png"));
		images.push_back(iLoadImage("resources//menu_screen//Buttons//credits.png"));
		// Active button images
		images.push_back(iLoadImage("resources//menu_screen//Buttons//exit_active.png"));
		images.push_back(iLoadImage("resources//menu_screen//Buttons//option_active.png"));
		images.push_back(iLoadImage("resources//menu_screen//Buttons//play_active.png"));
		images.push_back(iLoadImage("resources//menu_screen//Buttons//credits_active.png"));
		
	}

	void drawMenuScreen()
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
		iShowImage(SCREEN_WIDTH / 2 - (SCREEN_WIDTH * 0.4 / 2), SCREEN_HEIGHT / 2 + SCREEN_HEIGHT * 0.1, SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.4, images[1]);
		
		// Draw quit button
		int quitImg = (hoveredButton == 0 || currentSelectedButton == QUIT) ? images[6] : images[2];
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 250, BUTTON_WIDTH, BUTTON_HEIGHT, quitImg);
		
		// Draw credits button
		int creditsImg = (hoveredButton == 1 || currentSelectedButton == CREDITS) ? images[9] : images[5];
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 170, BUTTON_WIDTH, BUTTON_HEIGHT, creditsImg);
		
		// Draw play button
		int playImg = (hoveredButton == 3 || currentSelectedButton == PLAY) ? images[8] : images[4];
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 10, BUTTON_WIDTH, BUTTON_HEIGHT, playImg);
		
		// Draw settings button
		int settingsImg = (hoveredButton == 2 || currentSelectedButton == SETTINGS) ? images[7] : images[3];
		iShowImage(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - 90, BUTTON_WIDTH, BUTTON_HEIGHT, settingsImg);
	}
	// hover and click detection for menu
	void checkButtonHover(int mx, int my)
	{
		// Reset hovered button
		hoveredButton = -1;
		
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
		long long currentTime = glutGet(GLUT_ELAPSED_TIME);

		if (isQuitButtonClicked(mx, my))
		{
			hoveredButton = 0;
			if (!lastFrameQuitClicked)
			{
				if (currentTime - lastQuitBlipTime > HOVER_COOLDOWN)
				{
					mciSendString("play ggsong from 0", NULL, 0, NULL);
					lastQuitBlipTime = currentTime;
				}
				lastFrameQuitClicked = true;
			}
		}
		else
		{
			lastFrameQuitClicked = false;
		}

		if (isSettingsButtonClicked(mx, my))
		{
			hoveredButton = 2;
			if (!lastFrameSettingsClicked)
			{
				if (currentTime - lastSettingsBlipTime > HOVER_COOLDOWN)
				{
					mciSendString("play ggsong from 0", NULL, 0, NULL);
					lastSettingsBlipTime = currentTime;
				}
				lastFrameSettingsClicked = true;
			}
		}
		else
		{
			lastFrameSettingsClicked = false;
		}

		if (isPlayButtonClicked(mx, my))
		{
			hoveredButton = 3;
			if (!lastFramePlayClicked)
			{
				if (currentTime - lastPlayBlipTime > HOVER_COOLDOWN)
				{
					mciSendString("play ggsong from 0", NULL, 0, NULL);
					lastPlayBlipTime = currentTime;
				}
				lastFramePlayClicked = true;
			}
		}
		else
		{
			lastFramePlayClicked = false;
		}

		if (isCreditsButtonClicked(mx, my))
		{
			hoveredButton = 1;
			if (!lastFrameCreditsClicked)
			{
				if (currentTime - lastCreditsBlipTime > HOVER_COOLDOWN)
				{
					mciSendString("play ggsong from 0", NULL, 0, NULL);
					lastCreditsBlipTime = currentTime;
				}
				lastFrameCreditsClicked = true;
			}
		}
		else
		{
			lastFrameCreditsClicked = false;
		}
	}
	// Keyboard navigation
	void handleKeyboardNavigation(int specialKey)
	{
		// UP arrow - move to previous button
		if (specialKey == GLUT_KEY_UP || specialKey == 'w')
		{
			if (currentSelectedButton == QUIT)
				currentSelectedButton = CREDITS;
			else if (currentSelectedButton == CREDITS)
				currentSelectedButton = SETTINGS;
			else if (currentSelectedButton == PLAY)
				currentSelectedButton = QUIT;
			else if (currentSelectedButton == SETTINGS)
				currentSelectedButton = PLAY;
		}
		// DOWN arrow - move to next button
		else if (specialKey == GLUT_KEY_DOWN || specialKey == 's')
		{
			if (currentSelectedButton == QUIT)
				currentSelectedButton = PLAY;
			else if (currentSelectedButton == CREDITS)
				currentSelectedButton = QUIT;
			else if (currentSelectedButton == PLAY)
				currentSelectedButton = SETTINGS;
			else if (currentSelectedButton == SETTINGS)
				currentSelectedButton = CREDITS;
		}
		
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
		mciSendString("play ggsong from 0", NULL, 0, NULL);
	}
	
	// Get currently selected button type (0=quit, 1=credits, 2=play, 3=settings)
	int getSelectedButtonType()
	{
		return (int)currentSelectedButton;
	}
	// butoons
	bool isQuitButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int buttonY = SCREEN_HEIGHT / 2 - 250;

		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	bool isSettingsButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int buttonY = SCREEN_HEIGHT / 2 - 90;
		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	bool isPlayButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int buttonY = SCREEN_HEIGHT / 2 - 10;

		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	bool isCreditsButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int buttonY = SCREEN_HEIGHT / 2 - 170;

		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
				my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}
};
#endif
