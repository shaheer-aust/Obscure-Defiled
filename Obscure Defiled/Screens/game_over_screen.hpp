#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#ifndef GAME_OVER_SCREEN_HPP
#define GAME_OVER_SCREEN_HPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define BACK_BUTTON 81
#define HOVER_COOLDOWN 300 // milliseconds
#include <stack>
#include <string>
#include <iostream>
#include <vector>
using namespace std;
struct GameOverScreen
{
	vector<int> images;
	void initGameOverScreen()
	{
		images.push_back(iLoadImage("resources/game over/game_over.png"));
	}
	void draw_game_over_screen()
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
		//iSetColor(255, 255, 255);
		//iText(SCREEN_WIDTH / 2 - 120, 50, "press Esc to go back to Menu");
	}
};
#endif