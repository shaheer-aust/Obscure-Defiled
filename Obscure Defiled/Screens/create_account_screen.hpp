#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef CREATE_ACCOUNT_SCREEN_HPP
#define CREATE_ACCOUNT_SCREEN_HPP

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 294
#define BUTTON_HEIGHT 90
#define BACK_BUTTON 81
#define INPUT_BOX_WIDTH 400
#define INPUT_BOX_HEIGHT 50
#define MAX_NAME_LENGTH 20
#define HOVER_COOLDOWN 300
#include "GameScreen.hpp";
#include <iostream>
#include <string>
#include <vector>
#include "../level_handler.hpp"
using namespace std;

struct CreateAccount_screen
{
	int bgImg;
	int inputBoxImg;
	int createButtonImg;
	vector<int> button_images;
	string playerNameInput = "";
	bool isInputActive = false;
	long long lastHoverTime = 0;
	bool lastFrameHovered = false;

	void initCreateAccountScreen(int & bg)
	{
		bgImg = bg;
		button_images.push_back(iLoadImage("resources//menu_screen//Buttons//back.png"));
		// Load button frame for create button
		createButtonImg = iLoadImage("resources/option/button_frame.png");
	}

	void drawCreateAccountScreen()
	{
		// Draw background
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgImg);
		
		// Draw back button (top-left corner)
		iShowImage(20, SCREEN_HEIGHT - BACK_BUTTON - 20, BACK_BUTTON, BACK_BUTTON, button_images[0]);
		
		// Draw title text
		iSetColor(255, 255, 255);
		iText(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT - 100, "Create New Profile", GLUT_BITMAP_TIMES_ROMAN_24);
		
		// Draw input label
		iSetColor(255, 255, 255);
		iText(SCREEN_WIDTH/2 - INPUT_BOX_WIDTH/2, SCREEN_HEIGHT/2 + 80, "Enter Player Name:", GLUT_BITMAP_HELVETICA_18);
		
		// Draw input box
		int inputX = SCREEN_WIDTH/2 - INPUT_BOX_WIDTH/2;
		int inputY = SCREEN_HEIGHT/2 + 20;
		
		// Input box border
		if (isInputActive) {
			iSetColor(100, 200, 255); // Highlight when active
		} else {
			iSetColor(150, 150, 150);
		}
		iRectangle(inputX, inputY, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT);
		
		// Input box background
		iSetColor(30, 30, 30);
		iFilledRectangle(inputX + 2, inputY + 2, INPUT_BOX_WIDTH - 4, INPUT_BOX_HEIGHT - 4);
		
		// Draw input text
		iSetColor(255, 255, 255);
		char displayText[MAX_NAME_LENGTH + 2];
		sprintf_s(displayText, "%s", playerNameInput.c_str());
		iText(inputX + 10, inputY + 20, displayText, GLUT_BITMAP_HELVETICA_18);
		
		// Draw cursor if input is active
		if (isInputActive) {
			int cursorX = inputX + 10 + (playerNameInput.length() * 9);
			iSetColor(255, 255, 255);
			iLine(cursorX, inputY + 10, cursorX, inputY + 40);
		}
		
		// Draw create button
		int buttonX = SCREEN_WIDTH/2 - BUTTON_WIDTH/2;
		int buttonY = SCREEN_HEIGHT/2 - 80;
		iShowImage(buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT, createButtonImg);
		
		// Draw button text
		iSetColor(255, 255, 255);
		iText(buttonX + 70, buttonY + 25, "Create Profile", GLUT_BITMAP_HELVETICA_18);
		
		// Draw instruction text
		iSetColor(200, 200, 200);
		iText(SCREEN_WIDTH/2 - 150, 50, "Click the input box to start typing", GLUT_BITMAP_HELVETICA_12);
	}

	// Back button click detection
	bool isBackButtonClicked(int mx, int my)
	{
		return (mx >= 20 && mx <= BACK_BUTTON + 20 && 
		        my >= SCREEN_HEIGHT - (BACK_BUTTON + 20) && my <= SCREEN_HEIGHT);
	}

	// Input box click detection
	bool isInputBoxClicked(int mx, int my)
	{
		int inputX = SCREEN_WIDTH/2 - INPUT_BOX_WIDTH/2;
		int inputY = SCREEN_HEIGHT/2 + 20;
		return (mx >= inputX && mx <= inputX + INPUT_BOX_WIDTH && 
		        my >= inputY && my <= inputY + INPUT_BOX_HEIGHT);
	}

	// Create button click detection
	bool isCreateButtonClicked(int mx, int my)
	{
		int buttonX = SCREEN_WIDTH/2 - BUTTON_WIDTH/2;
		int buttonY = SCREEN_HEIGHT/2 - 80;
		return (mx >= buttonX && mx <= buttonX + BUTTON_WIDTH && 
		        my >= buttonY && my <= buttonY + BUTTON_HEIGHT);
	}

	// Handle mouse click
	void handleMouseClick(int mx, int my,GameScreen* game)
	{
		if (isInputBoxClicked(mx, my)) {
			isInputActive = true;
		} else {
			isInputActive = false;
		}
		
		if (isCreateButtonClicked(mx, my)) {
			// Create new player profile with default values
			playerInfo newPlayer;
			newPlayer.playerName = playerNameInput.empty()?"Unknown Player":playerNameInput;
			newPlayer.levelReached = 1;
			newPlayer.kills = 0;
			newPlayer.totalScore = 0;
			
			// Save the profile
			game->initgame_screen(1);
			savePlayerProfile(newPlayer);
			
			// Reset input
			playerNameInput = "";
			isInputActive = false;
		}
	}

	// Handle keyboard input
	void handleKeyInput(unsigned char key)
	{
		if (!isInputActive) return;
		
		if (key == '\b') { // Backspace
			if (!playerNameInput.empty()) {
				playerNameInput.pop_back();
			}
		}
		else if (key == '\r' || key == '\n') { // Enter key
		
				// Create profile on Enter
				playerInfo newPlayer;
				newPlayer.playerName = playerNameInput.empty()?"Unknown Player": playerNameInput;
				newPlayer.levelReached = 1;
				newPlayer.kills = 0;
				newPlayer.totalScore = 0;
				
				savePlayerProfile(newPlayer);
				
				playerNameInput = "";
				isInputActive = false;
			
		}
		else if (playerNameInput.length() < MAX_NAME_LENGTH && 
		         ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || 
		          (key >= '0' && key <= '9') || key == ' ' || key == '_')) {
			playerNameInput += key;
		}
	}

	// Hover detection for sound effects
	void checkButtonHover(int mx, int my)
	{
		mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias createHoverSound", NULL, 0, NULL);
		long long currentTime = glutGet(GLUT_ELAPSED_TIME);

		if (isBackButtonClicked(mx, my) || isCreateButtonClicked(mx, my))
		{
			if (!lastFrameHovered)
			{
				if (currentTime - lastHoverTime > HOVER_COOLDOWN)
				{
					mciSendString("play createHoverSound from 0", NULL, 0, NULL);
					lastHoverTime = currentTime;
				}
				lastFrameHovered = true;
			}
		}
		else
		{
			lastFrameHovered = false;
		}
	}
};

#endif
