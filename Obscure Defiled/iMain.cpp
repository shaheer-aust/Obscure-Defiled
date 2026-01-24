#include <cstdio>
#include "iGraphics.h"

/* -------------------- CONSTANTS -------------------- */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCROLL_SPEED 20

/* -------------------- GLOBALS -------------------- */
int bg1, bg2;
int bgX = 0;   // scrolling offset
int charX = 0;
int idx = 0;
int charImg[8];
/* -------------------- DRAW -------------------- */
void iDraw()
{
    iClear();
    iSetColor(255, 255, 255);

    // Draw connected backgrounds
    iShowImage(bgX, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg1);
    iShowImage(bgX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bg2);
	iShowImage(charX, 100, 50, 100, charImg[idx]);

    // Wrap background for continuous effect
    if (bgX <= -SCREEN_WIDTH)
        bgX = 0;
	if(charX>=SCREEN_WIDTH-10)
		charX=0;
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
        bgX -= SCROLL_SPEED;  // move background left
		charX +=10;
		idx+=1;
		if(idx==8)
			idx = 0;

    }
}

/* -------------------- INIT -------------------- */
void initBackground()
{
    bg1 = iLoadImage("Images//bg1.jpg");
    bg2 = iLoadImage("Images//bg2.jpg");
	for(int i =0;i<8;i++)
	{
		char a[100];
		sprintf_s(a,"Images//c%d.png",i+1);
		printf("%s",a);
		charImg[i]=iLoadImage(a); 
	}
}
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
