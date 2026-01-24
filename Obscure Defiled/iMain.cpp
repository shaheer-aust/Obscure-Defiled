#include <cstdio>
#include "iGraphics.h";
#include <menu_screen.hpp>

/* -------------------- CONSTANTS -------------------- */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCROLL_SPEED 20



/* -------------------- GLOBALS -------------------- */

/* -------------------- DRAW -------------------- */
void iDraw()
{
    iClear();
    iSetColor(255, 255, 255);
    menu_screen.draw();
}

/* -------------------- INPUT -------------------- */
void iMouseMove(int mx, int my) {}
void iPassiveMouseMove(int mx, int my) {}
void iMouse(int button, int state, int mx, int my) {}
void iKeyboard(unsigned char key) {}

// void iSpecialKeyboard(unsigned char key)
// {
//     if (key == GLUT_KEY_RIGHT)
//     {
//         bgX -= SCROLL_SPEED;  // move background left
// 		charX +=10;
// 		idx+=1;
// 		if(idx==8)
// 			idx = 0;

//     }
// }

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
	bgX -= 1;
}
/* -------------------- MAIN -------------------- */
int main()
{	
    //iSetTimer(50,moveBG);
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Connected Background Scroll");

    initBackground();

    iStart();
    return 0;
}
