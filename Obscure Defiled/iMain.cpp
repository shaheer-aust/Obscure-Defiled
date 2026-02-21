
#include <stdio.h>
#include "iGraphics.h";
#include "Screens\menu_screen.hpp";
#include "Screens\setting_screen.hpp";
#include "Screens\Level_1_game_screen.hpp";
#include "Screens\intro_screen.hpp";
#include "Screens\credit_screen.hpp";
#include "enemy_functions\enemy.hpp";
#include "Screens\credit_screen.hpp";
#include "character_functions\Hero.hpp";
#include "Screens\option_screen.hpp";
#include "Screens\game_over_screen.hpp";
#include "Screens\Score_Screen.hpp";
#include <vector>
#include <stack>
#include <string>
#include <iostream>
using namespace std;

/* -------------------- CONSTANTS -------------------- */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

/* -------------------- GLOBALS -------------------- */
// vector<int> menu_images;
stack<string> screens; //standard template library stack for screen management

MenuScreen menu;
Lvl_1_GameScreen level_1_screen;
GameOverScreen gameOverScreen;
Credit_screen credit;
Option_screen setting;
ScoreScreen scoreScreen;

int bgm_audio = -1;
vector<int> menu_images;


/* -------------------- DRAW -------------------- */
void iDraw()
{
	iClear();
	iSetColor(255, 255, 255);

	if (screens.top() == "Menu")
	{
		menu.drawMenuScreen();
	}
	else if (screens.top() == "gameOver"){
		gameOverScreen.draw_game_over_screen();
	}
	else if (screens.top() == "level_1_screen")
	{

		level_1_screen.drawgame_screen();
	}
	else if (screens.top() == "Settings")
	{

		setting.drawsetting_screen();
	}
	else if (screens.top() == "Score")
	{

		scoreScreen.draw_score_board();
	}
	else if (screens.top() == "Intro")
	{
		drawIntroScreen();
	}
	else if (screens.top() == "Credits")
	{

		credit.drawcredit_screen();
	}
}

/* -------------------- INPUT -------------------- */
void iMouseMove(int mx, int my)
{
	if (screens.top() == "Menu")
	{
		// cout << mx << " " << my << endl;
	}
}
void iPassiveMouseMove(int mx, int my)
{
	// cout << mx << "**" << my << endl;
	if (screens.top() == "Menu")
	{
		menu.checkButtonHover(mx, my);
	}
	else if (screens.top() == "Settings")
	{
		setting.checkButtonHover(mx, my);
	}
	else if (screens.top() == "Credits")
	{
		credit.checkButtonHover(mx, my);
	}
	// printf("co-ordinates: %dx%d/n", mx, my);
}
void iMouse(int button, int state, int mx, int my)
{
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	if (state == GLUT_DOWN && screens.top() == "Menu")
	{
		// Handle menu selection based on mouse position
		if (menu.isPlayButtonClicked(mx, my))
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			mciSendString("play gamebg repeat", NULL, 0, NULL);
			screens.push("level_1_screen");
			screens.push("Intro");
		}
		else if (menu.isSettingsButtonClicked(mx, my))
		{
			screens.push("Settings");
		}
		else if (menu.isQuitButtonClicked(mx, my))
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			exit(0);
		}
		else if (menu.isCreditsButtonClicked(mx, my))
		{
			screens.push("Credits");
		}
	}
	else if (state == GLUT_DOWN && screens.top() == "Settings")
	{
		// Handle settings selection based on mouse position
		if (setting.isBackButtonClicked(mx, my))
		{
			screens.pop();
			// if (screens.top() == "Menu")
			// {
			// 	mciSendString("play bgsong repeat", NULL, 0, NULL);
			// }
		}
		else if (setting.isScoreButtonClicked(mx, my))
		{
			screens.push("Score");
		}
	}
	else if (state == GLUT_DOWN && screens.top() == "Intro")
	{
		if (introMouseHandler(button, state, mx, my))
		{
			currentPic = 0;
			screens.pop(); // Exit intro screen
		}
	}
	else if (state == GLUT_DOWN && screens.top() == "level_1_screen" && button == GLUT_LEFT_BUTTON)
	{
		// Handle left mouse click for attack
		level_1_screen.hero1.startAttack();
	}
	else if (state == GLUT_DOWN && screens.top() == "Credits")
	{
		if (credit.isBackButtonClicked(mx, my))
		{
			screens.pop();
		}
	}
}
void iKeyboard(unsigned char key)
{
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	if (key == 27) // ESC key
	{
		if (screens.size() > 1)
		{
			screens.pop();
			if (screens.top() == "Menu")
			{
				//stop credit bgm if going back to menu from credits
				mciSendString("close gamebg", NULL, 0, NULL);
				mciSendString("play bgsong repeat", NULL, 0, NULL);
			}
		}
	}
	else if (key == 13 && screens.top() == "Menu") // Enter key
	{

		int buttonType = menu.getSelectedButtonType();

		if (buttonType == 0) // Quit
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			exit(0);
		}
		else if (buttonType == 1) // Credits
		{
			cout << "Credits Button Clicked (Keyboard)" << endl;
			screens.push("Credits");
		}
		else if (buttonType == 2) // Settings
		{

			screens.push("Settings");
		}
		else if (buttonType == 3) // Play
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			mciSendString("play gamebg repeat", NULL, 0, NULL);
			screens.push("level_1_screen");
			screens.push("Intro");
		}
	}
	else if (key == 32 && screens.top() == "level_1_screen")
	{ // SPACE key to jump
		level_1_screen.startJump();
	}
	else if (screens.top() == "level_1_screen")
	{
		// Handle WASD keys for game movement
		if (key == 'w' || key == 'W')
		{
			level_1_screen.startJump(); // W key to jump
		}
		else if (key == 'a' || key == 'A')
		{
			level_1_screen.leftPressed = true;
			level_1_screen.hero1.isMoving = true;
			level_1_screen.hero1.isright = false;
		}
		else if (key == 'd' || key == 'D')
		{
			level_1_screen.rightPressed = true;
			level_1_screen.hero1.isright = true;
			level_1_screen.hero1.isMoving = true;
		}
	}
}
void iKeyboardUp(unsigned char key)
{
	if (screens.top() == "level_1_screen")
	{
		if (key == 32) // Space key released
		{
			level_1_screen.spacePressed = false; // Stop jump when space key is released
		}
		else if (key == 'a' || key == 'A') // A key released
		{
			level_1_screen.leftPressed = false; // Stop moving left
		}
		else if (key == 'd' || key == 'D') // D key released
		{
			level_1_screen.rightPressed = false; // Stop moving right
		}
		else if (key == 'w' || key == 'W') // W key released
		{
			level_1_screen.spacePressed = false; // Stop jump when W key is released
		}
	}
}
void iSpecialKeyboardUp(unsigned char key)
{
	if (screens.top() == "level_1_screen")
	{
		if (key == GLUT_KEY_RIGHT) // Right arrow key released
		{
			level_1_screen.rightPressed = false; // Stop moving right
		}
		else if (key == GLUT_KEY_LEFT) // Left arrow key released
		{
			level_1_screen.leftPressed = false; // Stop moving left
		}
		else if (key == GLUT_KEY_UP) // Up arrow key released
		{
			level_1_screen.spacePressed = false; // Stop jump when up arrow key is released
		}
	}
}
void iSpecialKeyboard(unsigned char key)
{
	if (screens.top() == "Menu")
	{
		// Handle arrow key navigation
		if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN)
		{
			menu.handleKeyboardNavigation(key);
		}
	}
	else if (screens.top() == "level_1_screen")
	{
		// Handle game-specific special keys (e.g., arrow keys for movement)
		level_1_screen.handleSpecialKeyboard(key);
	}
	else if (screens.top() == "Intro")
	{
		// Handle intro screen navigation (e.g., arrow keys to switch pictures)
		bool isend = introKeyboardHandler(key);
		if (isend)
		{
			// cout << "jfjhg";
			currentPic = 0;
			screens.pop();
		}
	}
}

/* -------------------- INIT -------------------- */

void physics_update()
{
	level_1_screen.updateJumpPhysics();
}

void character_movement()
{
	if (level_1_screen.rightPressed && !level_1_screen.hero1.isJumping)
	{
		level_1_screen.x -= level_1_screen.bg_speed;

		if (level_1_screen.x <= -SCREEN_WIDTH)
		{
			level_1_screen.x = 0;
		}
		level_1_screen.hero1.isMoving = true;
		level_1_screen.hero1.movement_index++;
		level_1_screen.hero1.characterPosition_X += level_1_screen.hero1.character_speed;
		if (level_1_screen.hero1.characterPosition_X >= SCREEN_WIDTH - 70)
		{
			level_1_screen.hero1.characterPosition_X = SCREEN_WIDTH - 70;
		}
	}
	else if (level_1_screen.leftPressed && !level_1_screen.hero1.isJumping)
	{
		level_1_screen.x += level_1_screen.bg_speed;

		if (level_1_screen.x >= SCREEN_WIDTH)
		{
			level_1_screen.x = 0;
		}
		level_1_screen.hero1.isMoving = true;
		level_1_screen.hero1.movement_index++;
		level_1_screen.hero1.characterPosition_X -= level_1_screen.hero1.character_speed;
		if (level_1_screen.hero1.characterPosition_X < 0)
		{
			level_1_screen.hero1.characterPosition_X = 0;
		}
	}
	else if (level_1_screen.hero1.isJumping)
	{
		level_1_screen.hero1.isMoving = false;
	}
	else
	{
		level_1_screen.hero1.isMoving = false;
	}
}
void enemy_movement()
{
	if (screens.top() == "level_1_screen")
	{
		if (level_1_screen.rightPressed && !level_1_screen.hero1.isJumping)
		{
			if (level_1_screen.enemy1.isActive)
			{
				level_1_screen.enemy1.enemyPosition_X -= level_1_screen.bg_speed;
			}
			if (level_1_screen.enemy2.isActive)
			{
				level_1_screen.enemy2.enemyPosition_X -= level_1_screen.bg_speed;
			}
			if (level_1_screen.boss.isActive || level_1_screen.boss.bossHealth <= 0)
			{
				level_1_screen.boss.bossPosition_X -= level_1_screen.bg_speed;
			}
		}
		if (level_1_screen.leftPressed && !level_1_screen.hero1.isJumping)
		{
			if (level_1_screen.enemy1.isActive)
			{
				level_1_screen.enemy1.enemyPosition_X += level_1_screen.bg_speed;
			}
			if (level_1_screen.enemy2.isActive)
			{
				level_1_screen.enemy2.enemyPosition_X += level_1_screen.bg_speed;
			}
			if (level_1_screen.boss.isActive || level_1_screen.boss.bossHealth <= 0)
			{
				level_1_screen.boss.bossPosition_X += level_1_screen.bg_speed;
			}
		}
		// Spawn enemy2 when hero reaches halfway across the screen
		if (!level_1_screen.enemy2Spawned && level_1_screen.hero1.characterPosition_X >= SCREEN_WIDTH / 2)
		{
			level_1_screen.enemy2.isActive = true;
			level_1_screen.enemy2Spawned = true;
		}

		// Spawn boss when hero reaches 75% across the screen
		if (!level_1_screen.bossSpawned && level_1_screen.hero1.characterPosition_X >= (SCREEN_WIDTH * 0.75))
		{
			level_1_screen.boss.isActive = true;
			level_1_screen.bossSpawned = true;
		}

		level_1_screen.enemy1.move_enemy(level_1_screen.hero1);
		level_1_screen.enemy2.move_enemy(level_1_screen.hero1);
		level_1_screen.boss.move_boss(level_1_screen.hero1);
	}
}
void update_attack_animation()
{
	if (screens.top() == "level_1_screen")
	{
		level_1_screen.hero1.update_attack();
		level_1_screen.hero1.update_dead();
		level_1_screen.boss.update_attack();
		level_1_screen.boss.update_dead();
		level_1_screen.boss.boss_hit_loop();
	}
}
void hero_hit_loop()
{
	if (level_1_screen.hero1.gettingHit)
	{
		level_1_screen.hero1.hit_index++;
		if (level_1_screen.hero1.hit_index >= level_1_screen.hero1.character_idle_hit_R_images.size())
		{
			level_1_screen.hero1.hit_index = 0;
			// level_1_screen.hero1.gettingHit = false;
		}
	}
}
void all_50_ms_ticks(){
	if (screens.top() == "level_1_screen")
	{
		if (level_1_screen.hero1.isDead){
			screens.pop();
			screens.push("gameOver");
		}
		character_movement();
		enemy_movement();
		update_attack_animation();
		hero_hit_loop();
	}
}
void character_idle_animation()
{
	if (screens.top() == "level_1_screen")
	{
		level_1_screen.hero1.idle_animation();
	}
}
/* -------------------- MAIN -------------------- */

int main()
{
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//credit//credit_bg.mp3\" alias creditbg", NULL, 0, NULL);
	// iSetTimer(50,moveBG);
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Obscure Defiled");

	// Only initialize menu screen at startup - others load on-demand
	menu.initmenubar();
	setting.initsettingbar();
	initIntroScreen();
	credit.initcreditbar();
	initIntroScreen();
	level_1_screen.initgame_screen();

	gameOverScreen.initGameOverScreen();

	iSetTimer(200, character_idle_animation);
	iSetTimer(50, all_50_ms_ticks);
	// iSetTimer(1000, reset_movement);
	iSetTimer(20, physics_update);
	//iSetTimer(80, character_movement);
	//iSetTimer(100, enemy_movement);
	//iSetTimer(50, update_attack_animation);
	//iSetTimer(100, hero_hit_loop);
	// iSetTimer(100, boss_hit_loop);


	screens.push("Menu");
	// menu_images[1] = menu.initmenubar1();
	if (screens.top() == "Menu")
	{

		mciSendString("play bgsong repeat", NULL, 0, NULL);
	}
	else if (screens.top() == "level_1_screen")
	{
		mciSendString("play gamebg repeat", NULL, 0, NULL);
	}
	else if (screens.top() == "Credits")
	{
		mciSendString("play creditbg repeat", NULL, 0, NULL);
	}
	iStart();
	return 0;
}
