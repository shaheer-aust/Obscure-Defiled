#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H
#include "iGraphics.h"
#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct menu_screen
{
    string bgImage="resources//menu_screen//menu.jpg";
    std::vector<std::string> options={"Start Game", "Options", "Exit"};
    int selectedOption;

    menu_screen(string& bgPath, const vector<string>& opts)
        : options(opts), selectedOption(-1)
    {
        bgImage = iLoadImage(bgPath);
    }

    void draw()
    {
        iShowImage(0, 0, 1280, 720, bgImage);
        for (size_t i = 0; i < options.size(); ++i)
        {
            if (static_cast<int>(i) == selectedOption)
                iSetColor(255, 0, 0); // Highlight selected option
            else
                iSetColor(255, 255, 255);

            iText(100, 600 - (i * 50), options[i].c_str(), GLUT_BITMAP_HELVETICA_18);
        }
    }

    void selectOption(int index)
    {
        if (index >= 0 && index < static_cast<int>(options.size()))
            selectedOption = index;
    }
    
};
#endif