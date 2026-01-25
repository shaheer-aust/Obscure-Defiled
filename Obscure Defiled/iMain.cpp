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

/* -------------------- DRAW -------------------- */
void iDraw()
{
    iClear();
    iSetColor(255, 255, 255);
	if(screens.top()=="Menu")
	{
		menu.drawMenuScreen(menu_images,SCREEN_WIDTH,SCREEN_HEIGHT);
	}
	//
	
}

/* -------------------- INPUT -------------------- */
void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}
void iMouse(int button, int state, int mx, int my) {}
void iKeyboard(unsigned char key) {}

void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_RIGHT)
    {
        cout << sc.top() << endl;
		printf("%d",sc.top());
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
	MenuScreen menu;
	menu_images=menu.initmenubar();
	screens.push("Menu");
	//menu_images[1] = menu.initmenubar1();

    iStart();
    return 0;
}
