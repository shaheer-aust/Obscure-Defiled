#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef AFTER_LVL_1_SCREEN_H
#define AFTER_LVL_1_SCREEN_H
#define TOTAL_PICS 2
#include <iostream>

#include <vector>
using namespace std;
// Global state
int currentPic = 0;
vector<int> after_lvl_1_images;
void initIntroScreen()
{
	for (int i = 1; i <= TOTAL_PICS; i++)
	{
		char a[200];
		sprintf_s(a, "resources//Level_2//after_lvl_1//frame0%d", i+1);
		after_lvl_1_images.push_back(iLoadImage(a));
	}
}


  void drawAfterLvl1Screen()
{
	// Draw current picture
	//iShowBMP(645, 533, storyPics[currentPic]);
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, intro_images[currentPic]);
}

bool introKeyboardHandler(unsigned char key)
{
	if (key == GLUT_KEY_RIGHT || key == 'd')
	{
		currentPic++;

	}
	else if (key == GLUT_KEY_LEFT || key == 'a')
	{
		currentPic--;
		if (currentPic < 0)
		{
			currentPic = 0;
		}
	}
	else if (key == 13){
		return true;// 13 is for Enter button to input
	}
	if (currentPic > 1){
		return true;
	}
	
	return false;


}


#endif // AFTER_LVL_1_SCREEN_HPP