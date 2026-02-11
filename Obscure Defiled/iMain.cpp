#include <stdio.h>
#include "iGraphics.h"
#include "Screens\menu_screen.hpp"
#include "Screens\setting_screen.hpp"
#include "Screens\game_screen.hpp"
#include "Screens\intro_screen.hpp"
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
		
		game.drawgame_screen();

	}
	else if (screens.top() == "Settings")
	{
		// Draw settings screen
		setting.drawsetting_screen();
	}else if (screens.top() == "Intro")
	{
		drawIntroScreen();
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
	//printf("co-ordinates: %dx%d/n", mx, my);
	
}
void iMouse(int button, int state, int mx, int my)
{
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	if (state == GLUT_DOWN && screens.top() == "Menu")
	{
		//Handle menu selection based on mouse position
		if (menu.isPlayButtonClicked(mx, my))
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			mciSendString("play gamebg repeat", NULL, 0, NULL);
			screens.push("Game");
			screens.push("Intro");
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
	}else if (state == GLUT_DOWN && screens.top() == "Intro")
	{
		if (introMouseHandler(button, state, mx, my))
		{
			screens.pop(); // Exit intro screen
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
			screens.push("Intro");
		}
	}else if(key == 32 && screens.top() == "Game"){// SPACE key to jump
		game.startJump();
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
	
	}else if(screens.top() == "Intro"){
		// Handle intro screen navigation (e.g., arrow keys to switch pictures)
		bool isend=introKeyboardHandler(key);
		if(isend){
			//cout << "jfjhg";
			screens.pop();
		}
	}
}

/* -------------------- INIT -------------------- */
int idle_index = 0;
void idle_animation()
{
	idle_index++;
	if (idle_index >= 3)
	{
		idle_index = 0;
	}
}
void reset_movement()
{
	game.resetMovement();
	// Reset direction flags after movement is processed
	game.rightPressed = false;
	game.leftPressed = false;
	game.spacePressed = false;
}
void physics_update()
{
	game.updatePhysics();
}
int getIdleIndex(){
	return idle_index;
}


/* -------------------- MAIN -------------------- */
int main()
{
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	// iSetTimer(50,moveBG);
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Obscure Defiled");
	
	menu.initmenubar();
	initIntroScreen();
	iSetTimer(200, idle_animation);
	iSetTimer(1000, reset_movement);
	iSetTimer(50, physics_update);
	setting.initsettingbar();
	// initialize game assets once
	game.initgame_screen();
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
