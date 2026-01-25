#include <stdio.h>
#include "iGraphics.h"
#include "Screens\menu_screen.hpp"
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
vector<int> menu_images;
stack<string> screens;
MenuScreen menu;
int bgm_audio = -1;
mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.wav\" alias bgsong", NULL, 0, NULL);
/* -------------------- DRAW -------------------- */
void iDraw()
{
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
		cout << "In Settings Screen" << endl;
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
	menu.checkButtonHover(mx, my);
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
}
void iKeyboard(unsigned char key)
{
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
// void initBackground()
// {
//     bg1 = iLoadImage("Images//bg1.jpg");
//     bg2 = iLoadImage("Images//bg2.jpg");
// 	for(int i =0;i<8;i++)
// 	{
// 		char a[100];
// 		sprintf_s(a,"Images//c%d.png",i+1);
// 		printf("%s",a);
// 		charImg[i]=iLoadImage(a);
// 	}
// }

void moveBG()
{
	// bgX -= 1;
}
/* -------------------- MAIN -------------------- */
int main()
{
	// iSetTimer(50,moveBG);
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Obscure Defiled");
	
	menu_images = menu.initmenubar();
	screens.push("Menu");
	// menu_images[1] = menu.initmenubar1();
	if (screens.top() == "Menu")
	{
		
		mciSendString("play bgsong repeat", NULL, 0, NULL);
	}

	iStart();
	return 0;
}
