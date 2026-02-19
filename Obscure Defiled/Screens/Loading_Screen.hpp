#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <iostream>

#include <vector>
using namespace std;
// Global state
//loading bar dimension 938 × 90
vector<int> loading_bar_images;
int loading_bg=1;

int loading_index = 0;
bool isLoading = false;
void initLoadingScreen()
{
    for (int i = 1; i <= 9; i++)
    {
        char a[200];
        sprintf_s(a, "resources/loading Screen/loading bar/%d.png", i);
        loading_bar_images.push_back(iLoadImage(a));
    }
    loading_bg = iLoadImage("resources/loading Screen/bg/bg.png");
}
void drawLoadingScreen()
{
    iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loading_bg);
    int x = (SCREEN_WIDTH - 938) / 2;
    int y = (SCREEN_HEIGHT - 90) / 2;
    iShowImage(x, y, 938, 90, loading_bar_images[loading_index]);
}
void updateLoadingIndex(int value)
{
    loading_index= value;
    if (loading_index >= loading_bar_images.size())
    {
        loading_index = 8; // Reset to loop the animation
    }
}
void resetLoadingIndex()
{
    loading_index = 0;
}


#endif