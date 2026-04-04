#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef AFTER_LVL_2_SCREEN_H
#define AFTER_LVL_2_SCREEN_H
#define TOTAL_PICS 4
#include <iostream>

#include <vector>
using namespace std;
// Global state
struct After_level_2_screen{
	int after_level_2_pic_index = 0;
	vector<int> after_lvl_2_images;
	void initIntroScreen()
	{
		for (int i = 1; i <= TOTAL_PICS; i++)
		{
			char a[200];
			sprintf_s(a, "resources//Level_3//after lvl 2//%d.png", i);
			after_lvl_2_images.push_back(iLoadImage(a));
		}
	}


	void drawAfterLvl2Screen()
	{
		// Draw current picture
		//iShowBMP(645, 533, storyPics[after_level_2_pic_index]);
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, after_lvl_2_images[after_level_2_pic_index]);
	}

	bool introKeyboardHandler(unsigned char key)
	{
		if (key == GLUT_KEY_RIGHT || key == 'd')
		{
			after_level_2_pic_index++;

		}
		else if (key == GLUT_KEY_LEFT || key == 'a')
		{
			after_level_2_pic_index--;
			if (after_level_2_pic_index < 0)
			{
				after_level_2_pic_index = 0;
			}
		}
		else if (key == 13){
			return true;// 13 is for Enter button to input
		}
		if (after_level_2_pic_index > 3){
			return true;
		}
		return false;
	}



};
#endif // AFTER_LVL_2_SCREEN_H