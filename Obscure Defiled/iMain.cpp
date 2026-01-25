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
MenuScreen menu;
/* -------------------- GLOBALS -------------------- */
vector<int> menu_images;
stack<string> screens;

/* -------------------- DRAW -------------------- */
void iDraw()
{
    iClear();
    iSetColor(255, 255, 255);
    
    if (screens.top() == "Menu")
    {
        menu.drawMenuScreen(menu_images, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
    else if (screens.top() == "Game")
    {
        // Draw game screen
    }
    else if (screens.top() == "Settings")
    {
        // Draw settings screen
    }
}

/* -------------------- INPUT -------------------- */
void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}
void iMouse(int button, int state, int mx, int my)
{
    if (state == GLUT_DOWN && screens.top() == "Menu")
    {
        // Handle menu selection based on mouse position
        if (menu.isPlayButtonClicked(mx, my))
        {
            screens.push("Game");
        }
        else if (menu.isSettingsButtonClicked(mx, my))
        {
            screens.push("Settings");
        }
        else if (menu.isQuitButtonClicked(mx, my))
        {
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
            screens.pop(); // Go back to previous screen
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_RIGHT)
    {
        cout << screens.top() << endl;
		printf("%d",screens.top());
        //bgX -= SCROLL_SPEED;  // move background left
		//charX +=10;
		//idx+=1;
		//if(idx==8)
			//idx = 0;

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
	//bgX -= 1;
}
/* -------------------- MAIN -------------------- */
int main()
{	
    //iSetTimer(50,moveBG);
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Connected Background Scroll");
	
	menu_images=menu.initmenubar();
	screens.push("Menu");
	//menu_images[1] = menu.initmenubar1();

    iStart();
    return 0;
}
