#ifndef CREDIT_SCREEN_HPP
#define CREDIT_SCREEN_HPP

#include "iGraphics.h"
#include "main.hpp"        // for setCurrentScreen()
#include "menu_screen.hpp" // assuming you have a main menu header
#include "stb_image.h"     // lightweight PNG/JPG loader

// Credit screen texture
GLuint creditTexture;
int creditWidth, creditHeight, creditChannels;

// Button dimensions (top right corner)
int backBtnX = 700;   // adjust based on your window width
int backBtnY = 550;   // adjust based on your window height
int backBtnW = 80;
int backBtnH = 30;

// Load PNG into OpenGL texture
void loadCreditTexture(const char* filename) {
	unsigned char* data = stbi_load(filename, &creditWidth, &creditHeight, &creditChannels, 4);
	if (data) {
		glGenTextures(1, &creditTexture);
		glBindTexture(GL_TEXTURE_2D, creditTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, creditWidth, creditHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
	}
}

// Draw credit screen
void drawCreditScreen() {
	// Draw credit PNG as texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, creditTexture);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(0, 0);
	glTexCoord2f(1, 0); glVertex2f(creditWidth, 0);
	glTexCoord2f(1, 1); glVertex2f(creditWidth, creditHeight);
	glTexCoord2f(0, 1); glVertex2f(0, creditHeight);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Draw back button
	iSetColor(0, 0, 200);
	iRectangle(backBtnX, backBtnY, backBtnW, backBtnH);
	iText(backBtnX + 10, backBtnY + 10, "Back", GLUT_BITMAP_HELVETICA_18);
}

// Mouse handler
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