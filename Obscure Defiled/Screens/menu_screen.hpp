#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include<iostream>
using namespace std;
struct MenuScreen{

	int initmenubar()
	{
		return iLoadImage("resources//menu_screen//menu.jpg");

	}
};
#endif