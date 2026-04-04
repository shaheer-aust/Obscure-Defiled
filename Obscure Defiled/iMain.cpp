#include <stdio.h>
#include "iGraphics.h"
#include "Screens\menu_screen.hpp"
#include "Screens\setting_screen.hpp"
#include "Screens\intro_screen.hpp"
#include "Screens\credit_screen.hpp"
#include "enemy_functions\enemy.hpp"
#include "character_functions\Hero.hpp"
#include "Screens\option_screen.hpp"
#include "Screens\game_over_screen.hpp"
#include "Screens\Score_Screen.hpp"
#include "Screens\after_lvl_1_screen.hpp"
#include "Screens\after_lvl_2_screen.hpp"
#include "level_handler.hpp"
#include "Screens\create_account_screen.hpp"
#include "Screens\profile_screen.hpp"
#include "Screens\controls_screen.hpp"
#include "Screens\GameScreen.hpp"
#include <vector>
#include <stack>
#include <string>
#include <iostream>
using namespace std;

/* -------------------- CONSTANTS -------------------- */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

/* -------------------- GLOBALS -------------------- */
stack<string> screens;

MenuScreen menu;
GameScreen game_screen;
After_level_1_screen after_level_1_intro_screen;
After_level_2_screen after_level_2_intro_screen;
GameOverScreen gameOverScreen;
Credit_screen credit;
Option_screen setting;
ScoreScreen scoreScreen;
CreateAccount_screen createAccountScreen;
ProfileScreen profileScreen;
ControlsScreen controlsScreen;
playerInfo playerProfile;

int bgm_audio = -1;
vector<int> menu_images;
int lastStoredWinLevel = 0;

/* -------------------- DRAW -------------------- */
void iDraw()
{
	iClear();
	iSetColor(255, 255, 255);

	if (screens.top() == "Menu")
	{
		menu.drawMenuScreen();
		char playerName[100];
		sprintf_s(playerName, "hello, %s", playerProfile.playerName.c_str());
		iText(100, 75, playerName, GLUT_BITMAP_HELVETICA_18);
	}
	else if (screens.top() == "gameOver")
	{
		gameOverScreen.draw_game_over_screen();
	}
	else if (screens.top() == "victory")
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, game_screen.victoryImage);
	}
	else if (screens.top() == "game_screen")
	{
		game_screen.drawgame_screen();
	}
	else if (screens.top() == "Settings")
	{
		setting.drawsetting_screen();
	}
	else if (screens.top() == "Score")
	{
		scoreScreen.draw_score_board();
	}
	else if (screens.top() == "CreateAccount")
	{
		createAccountScreen.drawCreateAccountScreen();
	}
	else if (screens.top() == "Profile")
	{
		profileScreen.drawProfileScreen(playerProfile);
	}
	else if (screens.top() == "Controls")
	{
		controlsScreen.drawControlsScreen();
	}
	else if (screens.top() == "Intro")
	{
		drawIntroScreen();
	}
	else if (screens.top() == "Credits")
	{
		credit.drawcredit_screen();
	}
	else if (screens.top() == "After_lvl_1")
	{
		after_level_1_intro_screen.drawAfterLvl1Screen();
	}
	else if (screens.top() == "After_lvl_2")
	{
		after_level_2_intro_screen.drawAfterLvl2Screen();
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
	else if (screens.top() == "CreateAccount")
	{
		createAccountScreen.checkButtonHover(mx, my);
	}
	else if (screens.top() == "Profile")
	{
		profileScreen.checkButtonHover(mx, my);
	}
}
void iMouse(int button, int state, int mx, int my)
{
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_2//bg_2//song.mp3\" alias gamebg2", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_3//bg_3//bgm_for_final_round.mp3\" alias gamebg3", NULL, 0, NULL);
	mciSendString("open \"resources//sounds//knife.mp3\" alias knifesound", NULL, 0, NULL);
	mciSendString("open \"resources//sounds//pistol.mp3\" alias pistolsound", NULL, 0, NULL);

	if (state == GLUT_DOWN && screens.top() == "Menu")
	{
		if (menu.isPlayButtonClicked(mx, my))
		{
			lastStoredWinLevel = 0;
			mciSendString("close bgsong", NULL, 0, NULL);
			screens.push("game_screen");
			if (playerProfile.levelReached == 1)
			{
				mciSendString("play gamebg repeat", NULL, 0, NULL);
				screens.push("Intro");
			}
			else if (playerProfile.levelReached == 2)
			{
				mciSendString("play gamebg2 repeat", NULL, 0, NULL);
				screens.push("After_lvl_1");
			}
			else if (playerProfile.levelReached >= 3)
			{
				mciSendString("play gamebg3 repeat", NULL, 0, NULL);
				screens.push("After_lvl_2");
			}
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
		if (setting.isBackButtonClicked(mx, my))
		{
			screens.pop();
		}
		else if (setting.isScoreButtonClicked(mx, my))
		{
			screens.push("Score");
		}
		else if (setting.isControlsButtonClicked(mx, my))
		{
			screens.push("Controls");
		}
		else if (setting.isCreateNewButtonClicked(mx, my))
		{
			screens.push("CreateAccount");
		}
		else if (setting.isProfileButtonClicked(mx, my))
		{
			screens.push("Profile");
		}
	}
	else if (state == GLUT_DOWN && screens.top() == "CreateAccount")
	{
		if (createAccountScreen.isBackButtonClicked(mx, my))
		{
			screens.pop();
		}
		else
		{
			createAccountScreen.handleMouseClick(mx, my, &game_screen);
			if (createAccountScreen.isCreateButtonClicked(mx, my))
			{
				cout << "account created!" << endl;
				initPlayerProfile(playerProfile);
				screens.pop();
			}
		}
	}
	else if (state == GLUT_DOWN && screens.top() == "Intro")
	{
		if (introMouseHandler(button, state, mx, my))
		{
			currentPic = 0;
			screens.pop();
		}
	}
	else if (state == GLUT_DOWN && (screens.top() == "game_screen") && button == GLUT_LEFT_BUTTON)
	{
		if (game_screen.level == 1)
		{
			mciSendString("play knifesound from 0", NULL, 0, NULL);
		}
		else if (game_screen.level >= 2)
		{
			mciSendString("play pistolsound from 0", NULL, 0, NULL);
		}
		game_screen.startHeroAttack();
	}
	else if (state == GLUT_DOWN && screens.top() == "Credits")
	{
		if (credit.isBackButtonClicked(mx, my))
		{
			screens.pop();
		}
	}
	else if (state == GLUT_DOWN && screens.top() == "Profile")
	{
		if (profileScreen.isBackButtonClicked(mx, my))
		{
			screens.pop();
		}
	}
}
void iKeyboard(unsigned char key)
{
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_2//bg_2//song.mp3\" alias gamebg2", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_3//bg_3//bgm_for_final_round.mp3\" alias gamebg3", NULL, 0, NULL);

	if (key == 27) // ESC key
	{
		if (screens.size() > 1)
		{
			screens.pop();
			game_screen.resetgame();
			if (screens.top() == "Menu")
			{
				mciSendString("close gamebg", NULL, 0, NULL);
				mciSendString("close gamebg2", NULL, 0, NULL);
				mciSendString("close gamebg3", NULL, 0, NULL);
				mciSendString("play bgsong repeat", NULL, 0, NULL);
			}
		}
	}
	else if (key == 13 && (screens.top() == "victory" || screens.top() == "gameOver"))
	{
		cout << "Enter pressed on victory/gameOver screen, level=" << game_screen.level << endl;
		screens.pop();
		if (game_screen.level == 2 && screens.top() != "Menu")
		{
			screens.push("After_lvl_1");
			return;
		}
		else if (game_screen.level == 3 && screens.top() != "Menu")
		{
			screens.push("After_lvl_2");
			return;
		}
		else
		{
			if (screens.top() == "Menu")
			{
				game_screen.resetgame();
				mciSendString("play bgsong repeat", NULL, 0, NULL);
			}
		}
	}
	else if (key == 13 && screens.top() == "Menu")
	{
		int buttonType = menu.getSelectedButtonType();

		if (buttonType == 0) // Quit
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			exit(0);
		}
		else if (buttonType == 1) // Credits
		{
			screens.push("Credits");
		}
		else if (buttonType == 2) // Settings
		{
			screens.push("Settings");
		}
		else if (buttonType == 3) // Play
		{
			lastStoredWinLevel = 0;
			mciSendString("close bgsong", NULL, 0, NULL);
			screens.push("game_screen");
			if (playerProfile.levelReached == 1)
			{
				mciSendString("play gamebg repeat", NULL, 0, NULL);
				screens.push("Intro");
			}
			else if (playerProfile.levelReached == 2)
			{
				mciSendString("play gamebg2 repeat", NULL, 0, NULL);
				screens.push("After_lvl_1");
			}
			else if (playerProfile.levelReached >= 3)
			{
				mciSendString("play gamebg3 repeat", NULL, 0, NULL);
				screens.push("After_lvl_2");
			}
		}
	}
	else if (key == 32 && (screens.top() == "game_screen"))
	{
		game_screen.startJump();
	}
	else if (screens.top() == "game_screen")
	{
		if (key == 'w' || key == 'W')
		{
			game_screen.startJump();
		}
		else if (key == 'a' || key == 'A')
		{
			game_screen.leftPressed = true;
			game_screen.hero1.isMoving = true;
			game_screen.hero1.isright = false;
		}
		else if (key == 'd' || key == 'D')
		{
			game_screen.rightPressed = true;
			game_screen.hero1.isright = true;
			game_screen.hero1.isMoving = true;
		}
		else if (key == 'h' || key == 'H')
		{
			game_screen.tryUseHealthRecover();
		}
		else if (key == 'p' || key == 'P')
		{
			game_screen.lvl2PowerUp.handleKeyboard(key, game_screen.hero1);
		}
	}
	else if (screens.top() == "After_lvl_1")
	{
		bool isend = after_level_1_intro_screen.introKeyboardHandler(key);
		if (isend)
		{
			after_level_1_intro_screen.after_level_1_pic_index = 0;
			screens.pop();
		}
	}
	else if (screens.top() == "After_lvl_2")
	{
		bool isend = after_level_2_intro_screen.introKeyboardHandler(key);
		if (isend)
		{
			after_level_2_intro_screen.after_level_2_pic_index = 0;
			screens.pop();
		}
	}
	else if (screens.top() == "CreateAccount")
	{
		createAccountScreen.handleKeyInput(key);
		if ((key == '\r' || key == '\n'))
		{
			initPlayerProfile(playerProfile);
			screens.pop();
		}
	}
}
void iKeyboardUp(unsigned char key)
{
	if (screens.top() == "game_screen")
	{
		if (key == 32)
		{
			game_screen.spacePressed = false;
		}
		else if (key == 'a' || key == 'A')
		{
			game_screen.leftPressed = false;
		}
		else if (key == 'd' || key == 'D')
		{
			game_screen.rightPressed = false;
		}
		else if (key == 'w' || key == 'W')
		{
			game_screen.spacePressed = false;
		}
	}
}
void iSpecialKeyboardUp(unsigned char key)
{
	if (screens.top() == "game_screen")
	{
		if (key == GLUT_KEY_RIGHT)
		{
			game_screen.rightPressed = false;
		}
		else if (key == GLUT_KEY_LEFT)
		{
			game_screen.leftPressed = false;
		}
		else if (key == GLUT_KEY_UP)
		{
			game_screen.spacePressed = false;
		}
	}
}
void iSpecialKeyboard(unsigned char key)
{
	if (screens.top() == "Menu")
	{
		if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN)
		{
			menu.handleKeyboardNavigation(key);
		}
	}
	else if (screens.top() == "game_screen")
	{
		game_screen.handleSpecialKeyboard(key);
	}
	else if (screens.top() == "Intro")
	{
		bool isend = introKeyboardHandler(key);
		if (isend)
		{
			currentPic = 0;
			screens.pop();
		}
	}
	else if (screens.top() == "After_lvl_1")
	{
		bool isend = after_level_1_intro_screen.introKeyboardHandler(key);
		if (isend)
		{
			after_level_1_intro_screen.after_level_1_pic_index = 0;
			screens.pop();
		}
	}
	else if (screens.top() == "After_lvl_2")
	{
		bool isend = after_level_2_intro_screen.introKeyboardHandler(key);
		if (isend)
		{
			after_level_2_intro_screen.after_level_2_pic_index = 0;
			screens.pop();
		}
	}
}

/* -------------------- PHYSICS / MOVEMENT -------------------- */

void physics_update()
{
	game_screen.updateJumpPhysics();
}

void character_movement()
{
	if (game_screen.rightPressed && !game_screen.hero1.isJumping)
	{
		if (game_screen.canHeroMoveHorizontal(game_screen.hero1.character_speed))
		{
			game_screen.heroMovementBlockedByMainObstacle = false;
			game_screen.x -= game_screen.bg_speed;
			game_screen.cloudLayer2.shift(-game_screen.bg_speed);
			game_screen.shiftFloatingWall(-game_screen.bg_speed);
			game_screen.fireballSystem.shift(-game_screen.bg_speed);

			if (game_screen.x <= -SCREEN_WIDTH)
				game_screen.x = 0;

			game_screen.hero1.isMoving = true;
			game_screen.hero1.movement_index++;
			game_screen.hero1.characterPosition_X += game_screen.hero1.character_speed;
			if (game_screen.hero1.characterPosition_X >= SCREEN_WIDTH - 70)
				game_screen.hero1.characterPosition_X = SCREEN_WIDTH - 70;
		}
		else
		{
			game_screen.heroMovementBlockedByMainObstacle = true;
			game_screen.hero1.isMoving = false;
		}
	}
	else if (game_screen.leftPressed && !game_screen.hero1.isJumping)
	{
		if (game_screen.canHeroMoveHorizontal(-game_screen.hero1.character_speed))
		{
			game_screen.heroMovementBlockedByMainObstacle = false;
			game_screen.x += game_screen.bg_speed;
			game_screen.cloudLayer2.shift(game_screen.bg_speed);
			game_screen.shiftFloatingWall(game_screen.bg_speed);
			game_screen.fireballSystem.shift(game_screen.bg_speed);

			if (game_screen.x >= SCREEN_WIDTH)
				game_screen.x = 0;

			game_screen.hero1.isMoving = true;
			game_screen.hero1.movement_index++;
			game_screen.hero1.characterPosition_X -= game_screen.hero1.character_speed;
			if (game_screen.hero1.characterPosition_X < 0)
				game_screen.hero1.characterPosition_X = 0;
		}
		else
		{
			game_screen.heroMovementBlockedByMainObstacle = true;
			game_screen.hero1.isMoving = false;
		}
	}
	else if (game_screen.hero1.isJumping)
	{
		game_screen.heroMovementBlockedByMainObstacle = false;
		game_screen.hero1.isMoving = false;
	}
	else
	{
		game_screen.heroMovementBlockedByMainObstacle = false;
		game_screen.hero1.isMoving = false;
	}
}

void enemy_movement()
{
	if (screens.top() == "game_screen")
	{
		if (game_screen.rightPressed && !game_screen.hero1.isJumping && !game_screen.heroMovementBlockedByMainObstacle)
		{
			if (game_screen.enemy1.isActive) game_screen.enemy1.enemyPosition_X -= game_screen.bg_speed;
			if (game_screen.enemy2.isActive) game_screen.enemy2.enemyPosition_X -= game_screen.bg_speed;
			if (game_screen.enemy3.isActive) game_screen.enemy3.enemyPosition_X -= game_screen.bg_speed;
			if (game_screen.enemy4.isActive) game_screen.enemy4.enemyPosition_X -= game_screen.bg_speed;
			game_screen.shiftAnimatedObstacle(-game_screen.bg_speed);
			game_screen.shiftMainObstacle(-game_screen.bg_speed);
			if (game_screen.boss.isActive || game_screen.boss.bossHealth <= 0)
				game_screen.boss.bossPosition_X -= game_screen.bg_speed;
			game_screen.powerUp.shiftIcon(-game_screen.bg_speed);
			game_screen.lvl2PowerUp.shiftIcon(-game_screen.bg_speed);
		}
		if (game_screen.leftPressed && !game_screen.hero1.isJumping && !game_screen.heroMovementBlockedByMainObstacle)
		{
			if (game_screen.enemy1.isActive) game_screen.enemy1.enemyPosition_X += game_screen.bg_speed;
			if (game_screen.enemy2.isActive) game_screen.enemy2.enemyPosition_X += game_screen.bg_speed;
			if (game_screen.enemy3.isActive) game_screen.enemy3.enemyPosition_X += game_screen.bg_speed;
			if (game_screen.enemy4.isActive) game_screen.enemy4.enemyPosition_X += game_screen.bg_speed;
			game_screen.shiftAnimatedObstacle(game_screen.bg_speed);
			game_screen.shiftMainObstacle(game_screen.bg_speed);
			if (game_screen.boss.isActive || game_screen.boss.bossHealth <= 0)
				game_screen.boss.bossPosition_X += game_screen.bg_speed;
			game_screen.powerUp.shiftIcon(game_screen.bg_speed);
			game_screen.lvl2PowerUp.shiftIcon(game_screen.bg_speed);
		}

		// Level 1: kill chain e1 -> e2 -> e3 -> e4 -> boss
		if (game_screen.level == 1 && !game_screen.enemy2Spawned && game_screen.enemy1.enemyHealth <= 0)
		{
			game_screen.enemy2.isActive = true;
			game_screen.enemy2Spawned = true;
		}
		if (game_screen.level == 1 && !game_screen.enemy3Spawned && game_screen.enemy2.enemyHealth <= 0)
		{
			game_screen.enemy3.isActive = true;
			game_screen.enemy3Spawned = true;
		}
		if (game_screen.level == 1 && !game_screen.enemy4Spawned && game_screen.enemy3.enemyHealth <= 0)
		{
			game_screen.enemy4.isActive = true;
			game_screen.enemy4Spawned = true;
			game_screen.enemy4.enemyPosition_X = -15;
		}
		if (game_screen.level == 1 && !game_screen.bossSpawned && game_screen.enemy4.enemyHealth <= 0 && game_screen.enemy4Spawned)
		{
			game_screen.boss.isActive = true;
			game_screen.bossSpawned = true;
		}

		// Level 2: kill chain e1 -> e2 -> e3 -> e4 -> boss
		if (game_screen.level == 2)
		{
			if (!game_screen.enemy2Spawned && game_screen.enemy1.enemyHealth <= 0)
			{
				game_screen.enemy2.isActive = true;
				game_screen.enemy2Spawned = true;
				game_screen.enemy2.enemyPosition_X = 64;
			}
			if (!game_screen.enemy3Spawned && game_screen.enemy2.enemyHealth <= 0 && game_screen.enemy2Spawned)
			{
				game_screen.enemy3.isActive = true;
				game_screen.enemy3Spawned = true;
				game_screen.enemy3.enemyPosition_X = SCREEN_WIDTH - 220;
			}
			if (!game_screen.enemy4Spawned && game_screen.enemy3.enemyHealth <= 0 && game_screen.enemy3Spawned)
			{
				game_screen.enemy4.isActive = true;
				game_screen.enemy4Spawned = true;
				game_screen.enemy4.enemyPosition_X = SCREEN_WIDTH + 12;
			}
			if (!game_screen.bossSpawned && game_screen.enemy4.enemyHealth <= 0 && game_screen.enemy4Spawned)
			{
				game_screen.boss.isActive = true;
				game_screen.bossSpawned = true;
			}
		}
		// Level 3: e1 -> e2 -> boss -> e3 -> e4 -> alphaBoss
		else if (game_screen.level == 3)
		{
			if (!game_screen.enemy2Spawned && game_screen.enemy1.enemyHealth <= 0)
			{
				game_screen.enemy2.isActive = true;
				game_screen.enemy2Spawned = true;
				game_screen.enemy2.enemyPosition_X = 64;
			}
			if (!game_screen.bossSpawned && game_screen.enemy2.enemyHealth <= 0 && game_screen.enemy2Spawned)
			{
				game_screen.boss.isActive = true;
				game_screen.bossSpawned = true;
			}
			if (!game_screen.enemy3Spawned && game_screen.boss.bossHealth <= 0 && game_screen.bossSpawned)
			{
				game_screen.enemy3.isActive = true;
				game_screen.enemy3Spawned = true;
				game_screen.enemy3.enemyPosition_X = SCREEN_WIDTH - 220;
			}
			if (!game_screen.enemy4Spawned && game_screen.enemy3.enemyHealth <= 0 && game_screen.enemy3Spawned)
			{
				game_screen.enemy4.isActive = true;
				game_screen.enemy4Spawned = true;
				game_screen.enemy4.enemyPosition_X = SCREEN_WIDTH + 12;
			}
			if (!game_screen.alphaBossSpawned && game_screen.enemy4.enemyHealth <= 0 && game_screen.enemy4Spawned)
			{
				game_screen.alphaBoss.isActive = true;
				game_screen.alphaBossSpawned = true;
			}
		}

		double enemy1PrevX = game_screen.enemy1.enemyPosition_X;
		double enemy2PrevX = game_screen.enemy2.enemyPosition_X;
		double enemy3PrevX = game_screen.enemy3.enemyPosition_X;
		double enemy4PrevX = game_screen.enemy4.enemyPosition_X;
		double bossPrevX = game_screen.boss.bossPosition_X;

		game_screen.enemy1.move_enemy(game_screen.hero1);
		game_screen.enemy2.move_enemy(game_screen.hero1);
		game_screen.enemy3.move_enemy(game_screen.hero1);
		game_screen.enemy4.move_enemy(game_screen.hero1);
		game_screen.boss.move_boss(game_screen.hero1);
		game_screen.alphaBoss.move_alpha(game_screen.hero1);

		if (game_screen.level == 1)
		{
			game_screen.keepEnemyOutsideMainObstacle(game_screen.enemy1, enemy1PrevX);
			game_screen.keepEnemyOutsideMainObstacle(game_screen.enemy2, enemy2PrevX);
			game_screen.keepEnemyOutsideMainObstacle(game_screen.enemy3, enemy3PrevX);
		}
		else if (game_screen.level == 2)
		{
			game_screen.keepEnemyOutsideMainObstacle(game_screen.enemy1, enemy1PrevX);
		}
		else if (game_screen.level == 3)
		{
			game_screen.keepEnemyOutsideMainObstacle(game_screen.enemy1, enemy1PrevX);
		}

		// Trap movement for Level 2 and Level 3
		if (game_screen.level >= 2 && game_screen.level2Trap.isActive)
		{
			if (game_screen.rightPressed && !game_screen.hero1.isJumping)
				game_screen.level2Trap.shiftTraps(-game_screen.bg_speed);
			else if (game_screen.leftPressed && !game_screen.hero1.isJumping)
				game_screen.level2Trap.shiftTraps(game_screen.bg_speed);
		}
	}
}

void update_attack_animation()
{
	if (screens.top() == "game_screen")
	{
		game_screen.hero1.update_attack();
		game_screen.hero1.update_dead();
		game_screen.boss.update_attack();
		game_screen.boss.update_dead();
		game_screen.boss.boss_hit_loop();
		game_screen.alphaBoss.update_attack();
		game_screen.alphaBoss.update_dead();
	}
}

void hero_hit_loop()
{
	if (game_screen.hero1.gettingHit)
	{
		int hitFrameCount = game_screen.hero1.isright
			? (int)game_screen.hero1.character_idle_hit_R_images.size()
			: (int)game_screen.hero1.character_idle_hit_L_images.size();

		if (hitFrameCount <= 0)
		{
			game_screen.hero1.gettingHit = false;
			game_screen.hero1.hit_index = 0;
			return;
		}
		game_screen.hero1.hit_index++;
		if (game_screen.hero1.hit_index >= hitFrameCount - 1)
		{
			game_screen.hero1.hit_index = 0;
			game_screen.hero1.gettingHit = false;
		}
	}
}

int counter = 0;

void all_50_ms_ticks()
{
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_2//bg_2//song.mp3\" alias gamebg2", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_3//bg_3//bgm_for_final_round.mp3\" alias gamebg3", NULL, 0, NULL);
	mciSendString("open \"resources//credit//credit_bg.mp3\" alias creditbg", NULL, 0, NULL);
	mciSendString("open \"resources//sounds//gameOver.mp3\" alias gameoversound", NULL, 0, NULL);
	mciSendString("open \"resources//sounds//victory.mp3\" alias victorysound", NULL, 0, NULL);

	if (screens.top() == "game_screen" || screens.top() == "victory")
	{
		if (screens.top() == "game_screen")
		{
			game_screen.updateScoreSystem(0.05);
			game_screen.updateHitOverlayTimer();
		}

		if (game_screen.hero1.isDead)
		{
			mciSendString("close gamebg", NULL, 0, NULL);
			mciSendString("close gamebg2", NULL, 0, NULL);
			mciSendString("close gamebg3", NULL, 0, NULL);
			mciSendString("play gameoversound from 0", NULL, 0, NULL);
			screens.pop();
			screens.push("gameOver");
		}

		// ---- LEVEL 1 WIN ----
		else if (game_screen.level == 1 &&
			game_screen.enemy1.enemyHealth == 0 &&
			game_screen.enemy2.enemyHealth == 0 &&
			game_screen.enemy3.enemyHealth == 0 &&
			game_screen.enemy4.enemyHealth == 0 &&
			game_screen.boss.bossHealth == 0)
		{
			if (counter == 0)
			{
				screens.push("victory");
				mciSendString("close gamebg", NULL, 0, NULL);
				mciSendString("close gamebg2", NULL, 0, NULL);
				mciSendString("close gamebg3", NULL, 0, NULL);
				mciSendString("play victorysound from 0", NULL, 0, NULL);
				counter = 1;
			}
			else
			{
				playerProfile.kills += game_screen.getCurrentLevelKillCount();
				playerProfile.totalScore += game_screen.getCombinedScoreUpToCurrentLevel();
				playerProfile.levelReached = 2;
				savePlayerWinDetails(playerProfile);
				scoreScreen.load_scores_from_file();
				lastStoredWinLevel = 2;
				game_screen.initgame_screen(2);
				counter = 0;
				mciSendString("play gamebg2 repeat", NULL, 0, NULL);
				// After_lvl_1 intro shown when player presses Enter on victory screen
			}
		}

		// ---- LEVEL 2 WIN ----
		else if (game_screen.level == 2 &&
			game_screen.enemy1.enemyHealth == 0 &&
			game_screen.enemy2.enemyHealth == 0 &&
			game_screen.enemy3.enemyHealth == 0 &&
			game_screen.enemy4.enemyHealth == 0 &&
			game_screen.boss.bossHealth == 0)
		{
			if (counter == 0)
			{
				screens.push("victory");
				mciSendString("close gamebg", NULL, 0, NULL);
				mciSendString("close gamebg2", NULL, 0, NULL);
				mciSendString("close gamebg3", NULL, 0, NULL);
				mciSendString("play victorysound from 0", NULL, 0, NULL);
				counter = 1;
			}
			else
			{
				playerProfile.kills += game_screen.getCurrentLevelKillCount();
				playerProfile.totalScore += game_screen.getCombinedScoreUpToCurrentLevel();
				playerProfile.levelReached = 3;
				savePlayerWinDetails(playerProfile);
				scoreScreen.load_scores_from_file();
				game_screen.initgame_screen(3);
				counter = 0;
				mciSendString("close gamebg2", NULL, 0, NULL);
				mciSendString("play gamebg3 repeat", NULL, 0, NULL);
				// After_lvl_2 intro shown when player presses Enter on victory screen
			}
		}

		// ---- LEVEL 3 WIN ----
		else if (game_screen.level == 3 &&
			game_screen.enemy1.enemyHealth == 0 &&
			game_screen.enemy2.enemyHealth == 0 &&
			game_screen.enemy3.enemyHealth == 0 &&
			game_screen.enemy4.enemyHealth == 0 &&
			game_screen.boss.bossHealth == 0 &&
			game_screen.alphaBoss.alphaHealth == 0)
		{
			if (counter == 0)
			{
				screens.pop();
				screens.push("victory");
				mciSendString("close gamebg", NULL, 0, NULL);
				mciSendString("close gamebg2", NULL, 0, NULL);
				mciSendString("close gamebg3", NULL, 0, NULL);
				mciSendString("play victorysound from 0", NULL, 0, NULL);
				counter = 1;
			}
			else
			{
				playerProfile.kills += game_screen.getCurrentLevelKillCount();
				playerProfile.totalScore += game_screen.getCombinedScoreUpToCurrentLevel();
				playerProfile.levelReached = 1;
				savePlayerWinDetails(playerProfile);
				scoreScreen.load_scores_from_file();
				game_screen.initgame_screen(1);
				counter = 0;
			}
		}

		character_movement();
		game_screen.updateFloatingWallGroundSupport();

		double healthBeforeObstacle = game_screen.hero1.HeroHealth;
		game_screen.updateAnimatedObstacle(game_screen.hero1);
		if (game_screen.hero1.HeroHealth < healthBeforeObstacle)
			game_screen.triggerHitOverlay();

		double healthBeforeEnemy = game_screen.hero1.HeroHealth;
		enemy_movement();
		if (game_screen.hero1.HeroHealth < healthBeforeEnemy)
			game_screen.triggerHitOverlay();

		game_screen.updateProjectile();
		update_attack_animation();
		hero_hit_loop();

		if (game_screen.level == 1)
		{
			game_screen.powerUp.update(game_screen.hero1);
			game_screen.powerUp.checkRevert(game_screen.enemy1, game_screen.enemy2, game_screen.enemy3, game_screen.enemy4, game_screen.boss, game_screen.hero1);
		}

		if (game_screen.level >= 2)
		{
			double healthBeforeTrap = game_screen.hero1.HeroHealth;
			game_screen.level2Trap.checkCollision(game_screen.hero1);
			if (game_screen.hero1.HeroHealth < healthBeforeTrap)
				game_screen.triggerHitOverlay();
		}
	}
}

void character_idle_animation()
{
	if (screens.top() == "game_screen")
	{
		game_screen.hero1.idle_animation();
	}
}

/* -------------------- MAIN -------------------- */

int main()
{
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//button_sound//button.mp3\" alias ggsong", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_2//bg_2//song.mp3\" alias gamebg2", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_3//bg_3//bgm_for_final_round.mp3\" alias gamebg3", NULL, 0, NULL);
	mciSendString("open \"resources//credit//credit_bg.mp3\" alias creditbg", NULL, 0, NULL);
	mciSendString("open \"resources//sounds//gameOver.mp3\" alias gameoversound", NULL, 0, NULL);
	mciSendString("open \"resources//sounds//knife.mp3\" alias knifesound", NULL, 0, NULL);
	mciSendString("open \"resources//sounds//victory.mp3\" alias victorysound", NULL, 0, NULL);

	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Obscure Defiled");
	counter = 0;

	initPlayerProfile(playerProfile);
	bool requireCreateProfile = shouldSkipPlayerStorage(playerProfile.playerName);

	menu.initmenubar();
	setting.initsettingbar(menu.images[0]);
	initIntroScreen();
	credit.initcreditbar();
	after_level_1_intro_screen.initIntroScreen();
	after_level_2_intro_screen.initIntroScreen();   // <-- NEW
	game_screen.initgame_screen(playerProfile.levelReached);
	game_screen.updateScoreWhenLoadingLevel(playerProfile);
	createAccountScreen.initCreateAccountScreen(menu.images[0]);
	profileScreen.initProfileScreen(menu.images[0]);
	controlsScreen.initControlsScreen();
	gameOverScreen.initGameOverScreen();

	cout << "level: " << playerProfile.levelReached;

	iSetTimer(200, character_idle_animation);
	iSetTimer(50, all_50_ms_ticks);
	iSetTimer(20, physics_update);

	screens.push("Menu");
	if (requireCreateProfile)
		screens.push("CreateAccount");

	if (screens.top() == "Menu" || screens.top() == "CreateAccount")
		mciSendString("play bgsong repeat", NULL, 0, NULL);
	else if (playerProfile.levelReached == 1)
		mciSendString("play gamebg repeat", NULL, 0, NULL);
	else if (playerProfile.levelReached == 2)
		mciSendString("play gamebg2 repeat", NULL, 0, NULL);
	else if (playerProfile.levelReached >= 3)
		mciSendString("play gamebg3 repeat", NULL, 0, NULL);
	else if (screens.top() == "Credits")
		mciSendString("play creditbg repeat", NULL, 0, NULL);

	iStart();
	return 0;
}