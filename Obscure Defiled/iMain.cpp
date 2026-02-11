#include <stdio.h>
#include "iGraphics.h"
#include "Screens\menu_screen.hpp"
#include "Screens\setting_screen.hpp"
#include "Screens\game_screen.hpp"
#include <vector>
#include <stack>
#include <string>
#include <iostream>
using namespace std;
/* -------------------- CONSTANTS -------------------- */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCROLL_SPEED 20

/* -------------------- GLOBALS -------------------- */
//vector<int> menu_images;
stack<string> screens;

MenuScreen menu;
GameScreen game;
Setting_screen setting;
int bgm_audio = -1;
vector<int> menu_images;
/* -------------------- DRAW -------------------- */
void iDraw()
{
	iClear();
	iSetColor(255, 255, 255);

	if (screens.top() == "Menu")
	{
		//
		menu.drawMenuScreen();
	}
	else if (screens.top() == "Game")
	{
		// Draw game screen
		cout << "In Game Screen" << endl;
		game.initgame_screen();
		game.drawgame_screen();

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
	//cout << mx << "**" << my << endl;
	if (screens.top() == "Menu"){
		menu.checkButtonHover(mx, my);
	}
	else if (screens.top() == "Settings"){
		setting.checkButtonHover(mx, my);
	}
	
}
void iMouse(int button, int state, int mx, int my)
{
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	if (state == GLUT_DOWN && screens.top() == "Menu")
	{
		cout << mx << " " << my << endl;
		//Handle menu selection based on mouse position
		if (menu.isPlayButtonClicked(mx, my))
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			mciSendString("play gamebg repeat", NULL, 0, NULL);
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
		}else if (menu.isCreditsButtonClicked(mx, my))
		{
			// Handle credits button click
			cout << "Credits Button Clicked" << endl;
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
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	if (key == 27) // ESC key
	{
		if (screens.size() > 1)
		{
			screens.pop();
			if (screens.top() == "Menu")
			{
				mciSendString("close gamebg", NULL, 0, NULL);
				mciSendString("play bgsong repeat", NULL, 0, NULL);
			}
		}
	}
	else if (key == 13 && screens.top() == "Menu") // Enter key
	{
		// Handle selection based on currently selected button
		int buttonType = menu.getSelectedButtonType();
		
		if (buttonType == 0) // Quit
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			exit(0);
		}
		else if (buttonType == 1) // Credits
		{
			cout << "Credits Button Clicked (Keyboard)" << endl;
		}
		else if (buttonType == 2) // Settings
		{
			
			screens.push("Settings");
		}
		else if (buttonType == 3) // Play
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			mciSendString("play gamebg repeat", NULL, 0, NULL);
			screens.push("Game");
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (screens.top() == "Menu")
	{
		// Handle arrow key navigation
		if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN)
		{
			menu.handleKeyboardNavigation(key);
		}
	}else if(screens.top() == "Game"){
		// Handle game-specific special keys (e.g., arrow keys for movement)
		game.handleSpecialKeyboard(key);
	
		
	}
}

/* -------------------- INIT -------------------- */



/* -------------------- MAIN -------------------- */
int main()
{
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	// iSetTimer(50,moveBG);
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Obscure Defiled");
	menu.initmenubar();
	
	setting.initsettingbar();
	screens.push("Menu");
	// menu_images[1] = menu.initmenubar1();
	if (screens.top() == "Menu")
	{
		
		mciSendString("play bgsong repeat", NULL, 0, NULL);
	}else if(screens.top() == "Game"){
		mciSendString("play gamebg repeat", NULL, 0, NULL);
	}

	iStart();
	return 0;
}
