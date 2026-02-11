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

char *captions[TOTAL_PICS] = {
	"During the great war A knight, torn apart fighting an eastern Overlord.Thou doesn't know when the fight would end.Suddenly!?",
	"A mysterious circle like magic warp appears. It succumbed both the Knight and the Overlord who was getting dragged by some monster-like eldrich trees. ",
	"After landing on the ground The Knight found a glowing knife which is being DEFILED by the forest.",
	"Then thou decided to venture the forest to get back to this hometown"};

// Button dimensions
int skipBtnX = 1160, skipBtnY = 57;
int skipBtnW = 100, skipBtnH = 40;

void drawIntroScreen()
{
	// Draw current picture
	//iShowBMP(645, 533, storyPics[currentPic]);
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, intro_images[currentPic]);
	// Draw caption
	iSetColor(255, 255, 255);
	iText(348, 117, captions[currentPic], GLUT_BITMAP_HELVETICA_18);

	// Draw skip button
	iSetColor(200, 0, 0);
	iRectangle(skipBtnX, skipBtnY, skipBtnW, skipBtnH);
	iText(skipBtnX + 20, skipBtnY + 15, "Skip", GLUT_BITMAP_HELVETICA_18);
}

bool introKeyboardHandler(unsigned char key)
{
	if (key == GLUT_KEY_RIGHT)
	{
		currentPic = (currentPic + 1) % TOTAL_PICS;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		currentPic = (currentPic - 1 + TOTAL_PICS) % TOTAL_PICS;
	}
	if(currentPic == TOTAL_PICS - 1){
		return true;
	}else{
		return false;
	}
}

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