#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef CONTROLS_SCREEN_HPP
#define CONTROLS_SCREEN_HPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#include <iostream>
#include <vector>
using namespace std;

struct ControlsScreen
{
	int controlsImage;

	void initControlsScreen()
	{
		// Load the controls image
		controlsImage = iLoadImage("resources/option/option.png");
	}

	void drawControlsScreen()
	{
		// Draw the controls image full screen
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, controlsImage);
	}
};

#endif
