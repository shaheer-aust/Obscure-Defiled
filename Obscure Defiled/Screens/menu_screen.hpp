#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "iGraphics.h"
#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct menu_screen
{
    void draw()
    {
        int background = iLoadImage("resources//menu_screen//menu.jpg");
        iShowImage(0, 0, 1280, 720, background);
       
    }
    
};
#endif