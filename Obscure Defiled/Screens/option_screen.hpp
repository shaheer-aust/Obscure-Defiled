#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef OPTION_SCREEN_HPP
#define OPTION_SCREEN_HPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define BACK_BUTTON 81
#define HOVER_COOLDOWN 300 // milliseconds
#define FRAME_COUNT 4 // number of vertical frames to draw

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
struct Option_screen
{
	string menu_items = "Current-Profile Create-New ScoreBoard Controls";
	vector<int> credit_images; // holds the credit picture
	int bgImg;
	int button_button_frame;
	long long lastBackBlipTime = 0;
	bool lastFrameBackClicked = false;
	void initsettingbar(int & bg)
	{
		bgImg=bg;
		//credit_images.push_back(iLoadImage("resources//option//option.png"));
		credit_images.push_back(iLoadImage("resources//menu_screen//Buttons//back.png"));
		// score button (top-right)
		//credit_images.push_back(iLoadImage("resources//menu_screen//Buttons//back.png"));
		// Load images or resources needed for the credit screen
		button_button_frame=iLoadImage("resources/option/button_frame.png");
	}
	void drawsetting_screen()
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgImg);
		iShowImage(20, SCREEN_HEIGHT - BACK_BUTTON - 20, BACK_BUTTON, BACK_BUTTON, credit_images[0]);
		
		// draw four button frames vertically centered
		{ // scoped block for calculations
			string word;
			stringstream ss(menu_items);
			int frameW = BUTTON_WIDTH;
			int frameH = BUTTON_HEIGHT;
			int centerX = SCREEN_WIDTH / 2 - frameW / 2;
			int totalHeight = FRAME_COUNT * frameH;
			int startY = SCREEN_HEIGHT / 2 + totalHeight / 2 - frameH; // y coordinate of top frame
			for (int i = 0; i < FRAME_COUNT; ++i) {
				ss >> word;
				int y = startY - i * frameH;
				char a[30];
				sprintf_s(a,"%s",word.c_str());

				iShowImage(centerX, y, frameW, frameH, button_button_frame);
				iText(centerX+80+i*10,y+40,a,GLUT_BITMAP_HELVETICA_18);
			}
		}
		// Additional drawing code for credits can be added here
		
	}
	// back button hover and click detection for settings
	bool isBackButtonClicked(int mx, int my)
	{
		return (mx >= 20 && mx <= BACK_BUTTON + 20 && my >= SCREEN_HEIGHT - (BACK_BUTTON + 20) && my <= SCREEN_HEIGHT);
	}
	// profile button click detection (1st from top in menu)
	bool isProfileButtonClicked(int mx, int my)
	{
		int centerX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int totalHeight = FRAME_COUNT * BUTTON_HEIGHT;
		int startY = SCREEN_HEIGHT / 2 + totalHeight / 2 - BUTTON_HEIGHT;
		int profileY = startY - 0 * BUTTON_HEIGHT; // 1st button from top
		
		return (mx >= centerX && mx <= centerX + BUTTON_WIDTH && 
		        my >= profileY && my <= profileY + BUTTON_HEIGHT);
	}
	// create new button click detection (2nd from top in menu)
	bool isCreateNewButtonClicked(int mx, int my)
	{
		int centerX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int totalHeight = FRAME_COUNT * BUTTON_HEIGHT;
		int startY = SCREEN_HEIGHT / 2 + totalHeight / 2 - BUTTON_HEIGHT;
		int createNewY = startY - 1 * BUTTON_HEIGHT; // 2nd button from top
		
		return (mx >= centerX && mx <= centerX + BUTTON_WIDTH && 
		        my >= createNewY && my <= createNewY + BUTTON_HEIGHT);
	}
	// scoreboard button click detection (3rd from top in menu)
	bool isScoreButtonClicked(int mx, int my)
	{
		int centerX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int totalHeight = FRAME_COUNT * BUTTON_HEIGHT;
		int startY = SCREEN_HEIGHT / 2 + totalHeight / 2 - BUTTON_HEIGHT;
		int scoreboardY = startY - 2 * BUTTON_HEIGHT; // 3rd button from top
		
		return (mx >= centerX && mx <= centerX + BUTTON_WIDTH && 
		        my >= scoreboardY && my <= scoreboardY + BUTTON_HEIGHT);
	}
	// controls button click detection (4th from top in menu)
	bool isControlsButtonClicked(int mx, int my)
	{
		int centerX = SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2;
		int totalHeight = FRAME_COUNT * BUTTON_HEIGHT;
		int startY = SCREEN_HEIGHT / 2 + totalHeight / 2 - BUTTON_HEIGHT;
		int controlsY = startY - 3 * BUTTON_HEIGHT; // 4th button from top
		
		return (mx >= centerX && mx <= centerX + BUTTON_WIDTH && 
		        my >= controlsY && my <= controlsY + BUTTON_HEIGHT);
	}
	// hover detection
	void checkButtonHover(int mx, int my)
	{
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
		long long currentTime = glutGet(GLUT_ELAPSED_TIME);

		if (isBackButtonClicked(mx, my) || isProfileButtonClicked(mx, my) || 
		    isCreateNewButtonClicked(mx, my) || isScoreButtonClicked(mx, my) || 
		    isControlsButtonClicked(mx, my))
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
}

;
#endif
