#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include<iostream>
#include<vector>
using namespace std;
struct MenuScreen{

	vector<int> initmenubar()
	{
		 vector<int> images(2);
		 images[0]=iLoadImage("resources//menu_screen//menu.jpg");
		 images[1]=(iLoadImage("resources//menu_screen//title.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//play_button.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//settings_button.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//exit_button.png"));
		 return images;
	}
	void drawMenuScreen(vector<int> images,int SCREEN_WIDTH=1280,int SCREEN_HEIGHT=720)
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, images[0]);
    	iShowImage(SCREEN_WIDTH / 2 - (SCREEN_WIDTH * 0.4 / 2), SCREEN_HEIGHT / 2 +SCREEN_HEIGHT*0.1, SCREEN_WIDTH * 0.4, SCREEN_HEIGHT * 0.4, images[1]);
	}
};
#endif