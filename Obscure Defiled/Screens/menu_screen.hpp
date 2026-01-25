#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include<iostream>
using namespace std;
struct MenuScreen{

	vector<int> initmenubar()
	{
		vector<int>* images=new vector<int>();
		 images->push_back(iLoadImage("resources//menu_screen//menu.jpg"));
		 images->push_back(iLoadImage("resources//menu_screen//title.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//play_button.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//settings_button.png"));
		 //images->push_back(iLoadImage("resources//menu_screen//exit_button.png"));
		 return *images;
		
		

	}
};
#endif