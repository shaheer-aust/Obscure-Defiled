#include <stdio.h>
#include "iGraphics.h"
#include "Screens\menu_screen.hpp"
#include "Screens\setting_screen.hpp"
#include <vector> 
#include <stack>
#include <string>
#include <iostream>
using namespace std;
/* -------------------- CONSTANTS -------------------- */
#define SCROLL_SPEED 20

/* -------------------- GLOBALS -------------------- */
vector<int> menu_images;
stack<string> screens;
int currentScreenWidth = 1280;
int currentScreenHeight = 720;

MenuScreen menu;
Setting_screen setting;
int bgm_audio = -1;

/* -------------------- DRAW -------------------- */
void iDraw()
{
	// Update screen dimensions dynamically
	int currentWidth = glutGet(GLUT_WINDOW_WIDTH);
	int currentHeight = glutGet(GLUT_WINDOW_HEIGHT);
	currentScreenWidth = currentWidth;
	currentScreenHeight = currentHeight;
	menu.updateScreenDimensions(currentWidth, currentHeight);
	setting.updateScreenDimensions(currentWidth, currentHeight);
	
	iClear();
	iSetColor(255, 255, 255);

	if (screens.top() == "Menu")
	{
		menu.drawMenuScreen(menu_images);
	}
	else if (screens.top() == "Game")
	{
		// Draw game screen
		cout << "In Game Screen" << endl;
	}
	else if (screens.top() == "Settings")
	{
		// Draw settings screen
		setting.drawsetting_screen();
	}
}

/* -------------------- INPUT -------------------- */
void iMouseMove(int mx, int my) {
	if (screens.top() == "Menu")
	{
		//cout << mx << " " << my << endl;
		
	}
}
void iPassiveMouseMove(int mx, int my) {
	cout << mx << "**" << my << endl;
	if (screens.top() == "Menu"){
		menu.checkButtonHover(mx, my);
	}
	else if (screens.top() == "Settings"){
		setting.checkButtonHover(mx, my);
	}
	
}
void iMouse(int button, int state, int mx, int my)
{
	if (state == GLUT_DOWN && screens.top() == "Menu")
	{
		// Handle menu selection based on mouse position
		if (menu.isPlayButtonClicked(mx, my))
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			screens.push("Game");
		}
		else if (menu.isSettingsButtonClicked(mx, my))
		{
			screens.push("Settings");
		}
		else if (menu.isQuitButtonClicked(mx, my))
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			exit(0);
		}
	}
	else if (state == GLUT_DOWN && screens.top() == "Settings")
	{
		// Handle settings selection based on mouse position
		if (setting.isBackButtonClicked(mx, my))
		{
			screens.pop();
			// if (screens.top() == "Menu")
			// {
			// 	mciSendString("play bgsong repeat", NULL, 0, NULL);
			// }
		}
	}
}
void iKeyboard(unsigned char key)
{
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	if (key == 27) // ESC key
	{
		if (screens.size() > 1)
		{
			screens.pop();
			if (screens.top() == "Menu")
			{
				//PlaySound("resources//menu_screen//bg_audio//menu_bg.wav", NULL, SND_LOOP | SND_ASYNC);
				mciSendString("play bgsong repeat", NULL, 0, NULL);
			}
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_RIGHT)
	{
		cout << screens.top() << endl;
		printf("%d", screens.top());
		// bgX -= SCROLL_SPEED;  // move background left
		// charX +=10;
		// idx+=1;
		// if(idx==8)
		// idx = 0;
	}
}

/* -------------------- INIT -------------------- */



/* -------------------- MAIN -------------------- */
int main()
{
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
	// iSetTimer(50,moveBG);
	iInitialize(currentScreenWidth, currentScreenHeight, "Obscure Defiled");
	
	menu_images = menu.initmenubar();
	setting.initsettingbar();
	screens.push("Menu");
	// menu_images[1] = menu.initmenubar1();
	if (screens.top() == "Menu")
	{
		
		mciSendString("play bgsong repeat", NULL, 0, NULL);
	}

	iStart();
	return 0;
}
