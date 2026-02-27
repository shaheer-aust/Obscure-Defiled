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
#include <vector>
using namespace std;
struct Option_screen
{
	list<string> menu_items={"Create Profile","ScoreBoard","Controls","Back"} 
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
		// draw score button at top-right
		iShowImage(SCREEN_WIDTH - BACK_BUTTON - 20, SCREEN_HEIGHT - BACK_BUTTON - 20, BACK_BUTTON, BACK_BUTTON, credit_images[0]);
		// draw four button frames vertically centered
		{ // scoped block for calculations
		
			int frameW = BUTTON_WIDTH;
			int frameH = BUTTON_HEIGHT;
			int centerX = SCREEN_WIDTH / 2 - frameW / 2;
			int totalHeight = FRAME_COUNT * frameH;
			int startY = SCREEN_HEIGHT / 2 + totalHeight / 2 - frameH; // y coordinate of top frame
			for (int i = 0; i < FRAME_COUNT; ++i) {
				int y = startY - i * frameH;
				char a[30];
				sprintf_s(a,"%s",menu_items[i]);

				iShowImage(centerX, y, frameW, frameH, button_button_frame);
				iText(centerX+10,y+10,a);
			}
		}
		// Additional drawing code for credits can be added here
		
	}
	// back button hover and click detection for settings
	bool isBackButtonClicked(int mx, int my)
	{
		return (mx >= 20 && mx <= BACK_BUTTON + 20 && my >= SCREEN_HEIGHT - (BACK_BUTTON + 20) && my <= SCREEN_HEIGHT);
	}
	// score button click detection (top-right)
	bool isScoreButtonClicked(int mx, int my)
	{
		int left = SCREEN_WIDTH - BACK_BUTTON - 20;
		int right = SCREEN_WIDTH - 20;
		int top = SCREEN_HEIGHT;
		int bottom = SCREEN_HEIGHT - (BACK_BUTTON + 20);
		return (mx >= left && mx <= right && my >= bottom && my <= top);
	}
	// hover detection
	void checkButtonHover(int mx, int my)
	{
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
		long long currentTime = glutGet(GLUT_ELAPSED_TIME);

		if (isBackButtonClicked(mx, my) || isScoreButtonClicked(mx, my))
		{
			//hoveredButton = 0;
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
