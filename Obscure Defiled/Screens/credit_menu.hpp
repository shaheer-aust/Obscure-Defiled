#ifndef CREDIT_SCREEN_HPP
#define CREDIT_SCREEN_HPP

#include "iGraphics.h"
#include "main.hpp"       // for setCurrentScreen()
#include "menu_screen.hpp" // assuming you have a main menu header

// Credit screen image
const char* creditPic = "resources//credits//resized//credits.png";

// Button dimensions (top right corner)
int backBtnX = 700;   // adjust based on your window width
int backBtnY = 550;   // adjust based on your window height
int backBtnW = 80;
int backBtnH = 30;

void drawCreditScreen() {
	// Draw credit picture
	iShowBMP(0, 0, creditPic);

	// Draw back button
	iSetColor(0, 0, 200);
	iRectangle(backBtnX, backBtnY, backBtnW, backBtnH);
	iText(backBtnX + 10, backBtnY + 10, "Back", GLUT_BITMAP_HELVETICA_18);
}

void creditMouseHandler(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (mx >= backBtnX && mx <= backBtnX + backBtnW &&
			my >= backBtnY && my <= backBtnY + backBtnH) {
			// Go back to main menu
			setCurrentScreen(MENU_SCREEN);
		}
	}
}

#endif // CREDIT_SCREEN_HPP