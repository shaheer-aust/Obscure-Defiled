#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef PROFILE_SCREEN_HPP
#define PROFILE_SCREEN_HPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BACK_BUTTON 81
#define HOVER_COOLDOWN 300

#include <iostream>
#include <string>
#include <vector>
#include "../level_handler.hpp"
using namespace std;

struct ProfileScreen
{
	int bgImg;
	vector<int> button_images;
	long long lastHoverTime = 0;
	bool lastFrameHovered = false;

	void initProfileScreen(int & bg)
	{
		bgImg = bg;
		button_images.push_back(iLoadImage("resources//menu_screen//Buttons//back.png"));
	}

	void drawProfileScreen(const playerInfo& player)
	{
		// Draw background
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgImg);
		
		// Draw back button (top-left corner)
		iShowImage(20, SCREEN_HEIGHT - BACK_BUTTON - 20, BACK_BUTTON, BACK_BUTTON, button_images[0]);
		
		// Draw title
		iSetColor(255, 255, 255);
		iText(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 80, "Player Profile", GLUT_BITMAP_TIMES_ROMAN_24);
		
		// Draw player information with labels
		int startY = SCREEN_HEIGHT - 200;
		int lineHeight = 70;
		
		iSetColor(200, 200, 200);
		
		// Player Name
		char nameText[100];
		sprintf_s(nameText, "Player Name: %s", player.playerName.c_str());
		iText(SCREEN_WIDTH / 2 - 200, startY, nameText, GLUT_BITMAP_HELVETICA_18);
		
		// Level
		char levelText[100];
		sprintf_s(levelText, "Level Reached: %d", player.levelReached);
		iText(SCREEN_WIDTH / 2 - 200, startY - lineHeight, levelText, GLUT_BITMAP_HELVETICA_18);
		
		// Kills
		char killsText[100];
		sprintf_s(killsText, "Total Kills: %d", player.kills);
		iText(SCREEN_WIDTH / 2 - 200, startY - lineHeight * 2, killsText, GLUT_BITMAP_HELVETICA_18);
		
		// Score
		char scoreText[100];
		sprintf_s(scoreText, "Total Score: %d", player.totalScore);
		iText(SCREEN_WIDTH / 2 - 200, startY - lineHeight * 3, scoreText, GLUT_BITMAP_HELVETICA_18);
		
		// Draw instruction text
		iSetColor(150, 150, 150);
		iText(SCREEN_WIDTH / 2 - 100, 50, "Click back button to return", GLUT_BITMAP_HELVETICA_12);
	}

	// Back button click detection
	bool isBackButtonClicked(int mx, int my)
	{
		return (mx >= 20 && mx <= BACK_BUTTON + 20 && 
		        my >= SCREEN_HEIGHT - (BACK_BUTTON + 20) && my <= SCREEN_HEIGHT);
	}

	// Hover detection for sound effects
	void checkButtonHover(int mx, int my)
	{
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias profileHoverSound", NULL, 0, NULL);
		long long currentTime = glutGet(GLUT_ELAPSED_TIME);

		if (isBackButtonClicked(mx, my))
		{
			if (!lastFrameHovered)
			{
				if (currentTime - lastHoverTime > HOVER_COOLDOWN)
				{
					mciSendString("play profileHoverSound from 0", NULL, 0, NULL);
					lastHoverTime = currentTime;
				}
				lastFrameHovered = true;
			}
		}
		else
		{
			lastFrameHovered = false;
		}
	}
};

#endif
