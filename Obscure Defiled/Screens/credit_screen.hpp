#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef CREDIT_SCREEN_HPP
#define CREDIT_SCREEN_HPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define BACK_BUTTON 81
#define HOVER_COOLDOWN 300 // milliseconds

#include <iostream>
#include <vector>
using namespace std;

vector<int> credit_image; // holds the credit picture

struct Credit_screen
{
	int backButtonImage;
	int backBtnX, backBtnY;
	int backBtnW, backBtnH;

	Credit_screen()
		: backButtonImage(-1),
		backBtnX(10), backBtnY(10),
		backBtnW(50), backBtnH(50) {}

	// Load credit image and back button
	void initCreditScreen(const char* creditImgPath,
		const char* backBtnImgPath,
		const char* musicPath)
	{
		credit_image.push_back(iLoadImage(creditImgPath));
		backButtonImage = iLoadImage(backBtnImgPath);

		// play background music in loop
		string cmd = "open \"" + string(musicPath) + "\" alias creditsong";
		mciSendString(cmd.c_str(), NULL, 0, NULL);
		mciSendString("play creditsong repeat", NULL, 0, NULL);
	}

	// Draw the credit screen
	void showCreditScreen()
	{
		if (!credit_image.empty())
		{
			iDrawImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, credit_image[0]);
		}
		iDrawImage(backBtnX, backBtnY, backBtnW, backBtnH, backButtonImage);
	}

	// Handle back button click
	bool isBackButtonClicked(int mx, int my)
	{
		return (mx >= backBtnX && mx <= backBtnX + backBtnW &&
			my >= backBtnY && my <= backBtnY + backBtnH);
	}

	// Stop music
	void stopMusic()
	{
		mciSendString("close creditsong", NULL, 0, NULL);
	}
};

#endif // CREDIT_SCREEN_HPP