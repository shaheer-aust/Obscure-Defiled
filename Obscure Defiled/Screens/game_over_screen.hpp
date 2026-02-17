#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef GAME_OVER_SCREEN_HPP
#define GAME_OVER_SCREEN_HPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define BACK_BUTTON 81
#define HOVER_COOLDOWN 300 // milliseconds

#include <iostream>
#include <vector>
using namespace std;
struct Game_over_screen
{
	std::vector<int> game_over_images; // corrected name
	std::vector<int> credit_images;
	long long lastBackBlipTime = 0;
	bool lastFrameBackClicked = false;

	// Music control
	bool musicOn = true;
	const char* bgMusicAlias = "bgmusic";
	const char* buttonSoundAlias = "ggsong";

	void initsettingbar()
	{
		// load images (ensure paths exist)
		game_over_images.push_back(iLoadImage("resources//game over//game_over.png")); // index 0
		credit_images.push_back(iLoadImage("resources//menu_screen//Buttons//back.png")); // index 0

		// preload sounds (do not auto-play bg music here unless desired)
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
		mciSendString("open \"resources//music//game_over_bg.mp3\" alias bgmusic", NULL, 0, NULL);
	}

	void playBackgroundMusic()
	{
		if (!musicOn) return;
		// play bg music loop
		mciSendString("play bgmusic repeat", NULL, 0, NULL);
	}

	void stopBackgroundMusic()
	{
		mciSendString("stop bgmusic", NULL, 0, NULL);
	}

	void toggleMusic()
	{
		musicOn = !musicOn;
		if (musicOn) playBackgroundMusic();
		else stopBackgroundMusic();
	}

	void drawsetting_screen()
	{
		// draw game over background
		if (!game_over_images.empty())
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, game_over_images[0]);

		// draw back button (ensure credit_images[0] exists)
		if (!credit_images.empty())
			iShowImage(20, SCREEN_HEIGHT - BACK_BUTTON - 20, BACK_BUTTON, BACK_BUTTON, credit_images[0]);

		// optionally draw music toggle icon/text
		// e.g., draw a small icon at top-right indicating musicOn state
	}

	// back button hover and click detection for settings
	bool isBackButtonClicked(int mx, int my)
	{
		return (mx >= 20 && mx <= BACK_BUTTON + 20 &&
			my >= SCREEN_WIDTH - (BACK_BUTTON + 20) ? false : true) == false
			? false
			: (mx >= 20 && mx <= BACK_BUTTON + 20 && my >= SCREEN_HEIGHT - (BACK_BUTTON + 20) && my <= SCREEN_HEIGHT);
		// simplified below: use the clearer expression
	}

	// simpler, correct version:
	bool isBackButtonHovered(int mx, int my)
	{
		return (mx >= 20 && mx <= 20 + BACK_BUTTON &&
			my >= SCREEN_HEIGHT - (BACK_BUTTON + 20) && my <= SCREEN_HEIGHT - 20);
	}

	// hover detection
	void checkButtonHover(int mx, int my)
	{
		long long currentTime = glutGet(GLUT_ELAPSED_TIME);

		if (isBackButtonHovered(mx, my))
		{
			if (!lastFrameBackClicked)
			{
				if (currentTime - lastBackBlipTime > HOVER_COOLDOWN)
				{
					mciSendString("play ggsong from 0", NULL, 0, NULL);
					lastBackBlipTime = currentTime;
				}
				lastFrameBackClicked = true;
			}
		}
		else
		{
			lastFrameBackClicked = false;
		}
	}

	// Call this when the back button is clicked (mouse)
	void onBackButtonPressed()
	{
		// stop game over music and go to main menu
		stopBackgroundMusic();
		//currentScreen = MAIN_MENU_SCREEN; // assume you have a global or manager variable
	}

	// Keyboard handling: call this from your keyboard callback
	void handleKeyboard(unsigned char key)
	{
		if (key == 13 || key == '\r') // Enter key
		{
			// Enter returns to main menu
			stopBackgroundMusic();
			//currentScreen = MAIN_MENU_SCREEN;
		}
		else if (key == 'm' || key == 'M') // toggle music with M
		{
			toggleMusic();
		}
	}

	// Call this to transition into the game over screen (e.g., when health <= 0)
	void transitionToGameOver()
	{
		//currentScreen = GAME_OVER_SCREEN; // set the current screen
		if (musicOn) playBackgroundMusic();
		// any other initialization for game over state
	}

	// Utility: call from your game logic when health changes
	void updateHealth(int health)
	{
		if (health <= 0)
		{
			transitionToGameOver();
		}
	}
};
#endif 