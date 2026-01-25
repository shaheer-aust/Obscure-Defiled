#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include<iostream>
using namespace std;
struct MenuScreen{

	int initmenubar()
	{
		int images[2];
		 return (iLoadImage("resources//menu_screen//menu.jpg"));
		 //images[1]=(iLoadImage("resources//menu_screen//title.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//play_button.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//settings_button.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//exit_button.png"));
		
		
		

	}


	int initmenubar1()
	{
		int images[2];
		//return (iLoadImage("resources//menu_screen//menu.jpg"));
		return (iLoadImage("resources//menu_screen//title.png"));
		//images->push_back(iLoadImage("resources//menu_screen//play_button.png"));
		//images->push_back(iLoadImage("resources//menu_screen//settings_button.png"));
		//images->push_back(iLoadImage("resources//menu_screen//exit_button.png"));

	}
};
#endif