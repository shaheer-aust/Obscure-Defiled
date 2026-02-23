#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef INTRO_SCREEN_H
#define INTRO_SCREEN_H
#define TOTAL_PICS 4
#include <iostream>

#include <vector>
using namespace std;
// Global state
int currentPic = 0;
vector<int> intro_images;
void initIntroScreen()
{
	for (int i = 1; i <= TOTAL_PICS; i++)
	{
		char a[200];
		sprintf_s(a, "resources//Level_1//Panels//Intro//intro_%d.png", i);
		intro_images.push_back(iLoadImage(a));
	}
}

// Button dimensions
int skipBtnX = 1160, skipBtnY = 57;
int skipBtnW = 100, skipBtnH = 40;

void drawIntroScreen()
{
	// Draw current picture
	//iShowBMP(645, 533, storyPics[currentPic]);
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, intro_images[currentPic]);

	// Draw skip button
	iSetColor(142, 142, 142);
	iFilledRectangle(skipBtnX, skipBtnY, skipBtnW, skipBtnH);
	iSetColor(0,0,0);
	iText(skipBtnX + 28, skipBtnY + 15, "Skip", GLUT_BITMAP_TIMES_ROMAN_24 );
}

bool introKeyboardHandler(unsigned char key)
{
	if (key == GLUT_KEY_RIGHT || key == 'd')
	{
		currentPic++;
		
	}
	else if (key == GLUT_KEY_LEFT || key == 'a')
	{
		currentPic--;
		if (currentPic < 0)
		{
			currentPic = 0;
		}
	}
	if (currentPic > 3){
		return true;
	}
	return false;
}

//'a' and 'd' dont work in introKeyboardHandler

bool introMouseHandler(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (mx >= skipBtnX && mx <= skipBtnX + skipBtnW &&
			my >= skipBtnY && my <= skipBtnY + skipBtnH)
		{
			// Skip button clicked
			return true; // Signal to skip intro
		}
	}
	return false; // Continue showing intro
				  // Transition to game screen
				  // setCurrentScreen(game_screen);
}

#endif // INTRO_SCREEN_HPP