#ifndef INTRO_SCREEN_HPP
#define INTRO_SCREEN_HPP

#include "iGraphics.h"
#include "main.hpp"       // Assuming this header manages screen transitions
#include "game_screen.hpp"

#define TOTAL_PICS 4

// Global state
int currentPic = 0;
char* storyPics[TOTAL_PICS] = {
	"resources//Level_1//Panels//Intro//intro_1.png",
	"resources//Level_1//Panels//Intro//intro_2.png",
	"resources//Level_1//Panels//Intro//intro_3.png",
	"resources//Level_1//Panels//Intro//intro_4.png"
};

char* captions[TOTAL_PICS] = {
	"During the great war A knight, torn apart fighting an eastern Overlord.Thou doesn't know when the fight would end.Suddenly!?",
	"A mysterious circle like magic warp appears. It succumbed both the Knight and the Overlord who was getting dragged by some monster-like eldrich trees. ",
	"After landing on the ground The Knight found a glowing knife which is being DEFILED by the forest.",
	"Then thou decided to venture the forest to get back to this hometown"
};

// Button dimensions
int skipBtnX = 1160, skipBtnY = 57;
int skipBtnW = 100, skipBtnH = 40;

void drawIntroScreen() {
	// Draw current picture
	iShowBMP(645, 533, storyPics[currentPic]);

	// Draw caption
	iSetColor(255, 255, 255);
	iText(348, 117, captions[currentPic], GLUT_BITMAP_HELVETICA_18);

	// Draw skip button
	iSetColor(200, 0, 0);
	iRectangle(skipBtnX, skipBtnY, skipBtnW, skipBtnH);
	iText(skipBtnX + 20, skipBtnY + 15, "Skip", GLUT_BITMAP_HELVETICA_18);
}

void introKeyboardHandler(unsigned char key) {
	if (key == GLUT_KEY_RIGHT) {
		currentPic = (currentPic + 1) % TOTAL_PICS;
	}
	else if (key == GLUT_KEY_LEFT) {
		currentPic = (currentPic - 1 + TOTAL_PICS) % TOTAL_PICS;
	}
}

void introMouseHandler(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mx >= skipBtnX && mx <= skipBtnX + skipBtnW &&
			my >= skipBtnY && my <= skipBtnY + skipBtnH) {
			// Transition to game screen
			setCurrentScreen(game_screen);
		}
	}
}

#endif // INTRO_SCREEN_HPP