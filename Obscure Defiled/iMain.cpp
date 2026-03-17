
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
#include "Screens\after_lvl_1_screen.hpp"
#include "level_handler.hpp"
#include "Screens\create_account_screen.hpp"
#include "Screens\profile_screen.hpp"
#include "Screens\controls_screen.hpp"
// #include "Screens\Level_2_game_screen.hpp";
#include "Screens\GameScreen.hpp";
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
stack<string> screens; // standard template library stack for screen management

MenuScreen menu;
GameScreen game_screen;
After_level_1_screen after_level_1_intro_screen;
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

/* -------------------- DRAW -------------------- */
void iDraw()
{
	iClear();
	iSetColor(255, 255, 255);
	// cout << screens.top() << endl;
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

		// level_1_screen.drawgame_screen();
		game_screen.drawgame_screen();
	}
	// else if (screens.top() == "level_2_screen")
	// {

	// 	//level_2_screen.drawgame_screen();
	// 	game_screen.drawgame_screen();
	// }
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
	else if (screens.top() == "CreateAccount")
	{
		createAccountScreen.checkButtonHover(mx, my);
	}
	else if (screens.top() == "Profile")
	{
		profileScreen.checkButtonHover(mx, my);
	}
	// printf("co-ordinates: %dx%d/n", mx, my);
}
void iMouse(int button, int state, int mx, int my)
{
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_2//bg_2//song.mp3\" alias gamebg2", NULL, 0, NULL);
	if (state == GLUT_DOWN && screens.top() == "Menu")
	{
		// Handle menu selection based on mouse position
		if (menu.isPlayButtonClicked(mx, my))
		{
			mciSendString("close bgsong", NULL, 0, NULL);
			mciSendString("play gamebg repeat", NULL, 0, NULL);
			screens.push("game_screen");
			if (playerProfile.levelReached == 1)
			{
				mciSendString("play gamebg repeat", NULL, 0, NULL);
				screens.push("Intro");
			}
			else if (playerProfile.levelReached == 2)
			{
				mciSendString("play gamebg repeat", NULL, 0, NULL);
				screens.push("After_lvl_1");
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
		}else if(setting.isControlsButtonClicked(mx, my))
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
		// Handle create account screen mouse clicks
		if (createAccountScreen.isBackButtonClicked(mx, my))
		{
			screens.pop();
		}
		else
		{
			createAccountScreen.handleMouseClick(mx, my);
			// Check if profile was created and go back
			if (createAccountScreen.isCreateButtonClicked(mx, my))
			{
				// Reload player profile after creation
				cout << "accounty created!";
				initPlayerProfile(playerProfile);
				screens.pop(); // Go back to settings
			}
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
	else if (state == GLUT_DOWN && (screens.top() == "game_screen") && button == GLUT_LEFT_BUTTON)
	{
		// Handle left mouse click for attack
		// level_1_screen.hero1.startAttack();
		game_screen.hero1.startAttack();
	}
	else if (state == GLUT_DOWN && screens.top() == "Credits")
	{
		if (credit.isBackButtonClicked(mx, my))
		{
			screens.pop();
		}
	}	else if (state == GLUT_DOWN && screens.top() == "Profile")
	{
		// Handle profile screen click
		if (profileScreen.isBackButtonClicked(mx, my))
		{
			screens.pop(); // Go back to settings
		}
	}}
void iKeyboard(unsigned char key)
{
	mciSendString("open \"resources//game_screen//level_1//bg_1//bg_audio.mp3\" alias gamebg", NULL, 0, NULL);
	mciSendString("open \"resources//menu_screen//bg_audio//menu_bg.mp3\" alias bgsong", NULL, 0, NULL);
	mciSendString("open \"resources//game_screen//level_2//bg_2//song.mp3\" alias gamebg2", NULL, 0, NULL);
	if (key == 27) // ESC key
	{
		if (screens.size() > 1)
		{
			screens.pop();
			game_screen.resetgame();
			if (screens.top() == "Menu")
			{
				// stop credit bgm if going back to menu from credits
				mciSendString("close gamebg", NULL, 0, NULL);
				mciSendString("close gamebg2", NULL, 0, NULL);
				mciSendString("play bgsong repeat", NULL, 0, NULL);
			}
		}
	}
	else if (key == 13 && screens.top() == "victory"){
		screens.pop();
		screens.push("After_lvl_1");

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
		}
	}
	else if (key == 32 && (screens.top() == "game_screen"))
	{ // SPACE key to jump
		// level_1_screen.startJump();
		game_screen.startJump();
	}
	else if (screens.top() == "game_screen")
	{
		// Handle WASD keys for game movement
		if (key == 'w' || key == 'W')
		{
			// level_1_screen.startJump(); // W key to jump
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
	}
	else if (screens.top() == "After_lvl_1")
	{
		// Pass the pressed key to the after level 1 screen
		bool isend = after_level_1_intro_screen.introKeyboardHandler(key);
		if (isend)
		{
			// Reset the picture index for next time
			after_level_1_intro_screen.after_level_1_pic_index = 0;
			screens.pop(); // Remove "After_lvl_1" from top of stack
		}
	}
	else if (screens.top() == "CreateAccount")
	{
		// Handle keyboard input for create account screen
		createAccountScreen.handleKeyInput(key);
		// Check if Enter was pressed and profile was created
		if ((key == '\r' || key == '\n'))
		{
			// Reload player profile after creation
			initPlayerProfile(playerProfile);
			screens.pop(); // Go back to settings
		}
	}
}
void iKeyboardUp(unsigned char key)
{
	if (screens.top() == "game_screen")
	{
		if (key == 32) // Space key released
		{
			game_screen.spacePressed = false; // Stop jump when space key is released
		}
		else if (key == 'a' || key == 'A') // A key released
		{
			game_screen.leftPressed = false; // Stop moving left
		}
		else if (key == 'd' || key == 'D') // D key released
		{
			game_screen.rightPressed = false; // Stop moving right
		}
		else if (key == 'w' || key == 'W') // W key released
		{
			game_screen.spacePressed = false; // Stop jump when W key is released
		}
	}
}
void iSpecialKeyboardUp(unsigned char key)
{
	if (screens.top() == "game_screen")
	{
		if (key == GLUT_KEY_RIGHT) // Right arrow key released
		{
			game_screen.rightPressed = false; // Stop moving right
		}
		else if (key == GLUT_KEY_LEFT) // Left arrow key released
		{
			game_screen.leftPressed = false; // Stop moving left
		}
		else if (key == GLUT_KEY_UP) // Up arrow key released
		{
			game_screen.spacePressed = false; // Stop jump when up arrow key is released
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
	else if (screens.top() == "game_screen")
	{
		// Handle game-specific special keys (e.g., arrow keys for movement)
		game_screen.handleSpecialKeyboard(key);
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
	else if (screens.top() == "After_lvl_1")
	{
		// Pass the arrow keys to the intro handler
		bool isend = after_level_1_intro_screen.introKeyboardHandler(key);
		if (isend)
		{
			after_level_1_intro_screen.after_level_1_pic_index = 0;
			screens.pop(); // Remove "After_lvl_1" from top of stack
		}
	}
}

/* -------------------- INIT -------------------- */

void physics_update()
{
	game_screen.updateJumpPhysics();
}

void character_movement()
{
	if (game_screen.rightPressed && !game_screen.hero1.isJumping)
	{
		game_screen.x -= game_screen.bg_speed;

		if (game_screen.x <= -SCREEN_WIDTH)
		{
			game_screen.x = 0;
		}
		game_screen.hero1.isMoving = true;
		game_screen.hero1.movement_index++;
		game_screen.hero1.characterPosition_X += game_screen.hero1.character_speed;
		if (game_screen.hero1.characterPosition_X >= SCREEN_WIDTH - 70)
		{
			game_screen.hero1.characterPosition_X = SCREEN_WIDTH - 70;
		}
	}
	else if (game_screen.leftPressed && !game_screen.hero1.isJumping)
	{
		game_screen.x += game_screen.bg_speed;

		if (game_screen.x >= SCREEN_WIDTH)
		{
			game_screen.x = 0;
		}
		game_screen.hero1.isMoving = true;
		game_screen.hero1.movement_index++;
		game_screen.hero1.characterPosition_X -= game_screen.hero1.character_speed;
		if (game_screen.hero1.characterPosition_X < 0)
		{
			game_screen.hero1.characterPosition_X = 0;
		}
	}
	else if (game_screen.hero1.isJumping)
	{
		game_screen.hero1.isMoving = false;
	}
	else
	{
		game_screen.hero1.isMoving = false;
	}
}
void enemy_movement()
{
	if (screens.top() == "game_screen")
	{
		if (game_screen.rightPressed && !game_screen.hero1.isJumping)
		{
			if (game_screen.enemy1.isActive)
			{
				game_screen.enemy1.enemyPosition_X -= game_screen.bg_speed;
			}
			if (game_screen.enemy2.isActive)
			{
				game_screen.enemy2.enemyPosition_X -= game_screen.bg_speed;
			}
			if (game_screen.enemy3.isActive)
			{
				game_screen.enemy3.enemyPosition_X -= game_screen.bg_speed;
			}
			if (game_screen.enemy4.isActive)
			{
				game_screen.enemy4.enemyPosition_X -= game_screen.bg_speed;
			}
			if (game_screen.boss.isActive || game_screen.boss.bossHealth <= 0)
			{
				game_screen.boss.bossPosition_X -= game_screen.bg_speed;
			}
			// Step 5: scroll the power-up icon with the background
			game_screen.powerUp.shiftIcon(-game_screen.bg_speed);
		}
		if (game_screen.leftPressed && !game_screen.hero1.isJumping)
		{
			if (game_screen.enemy1.isActive)
			{
				game_screen.enemy1.enemyPosition_X += game_screen.bg_speed;
			}
			if (game_screen.enemy2.isActive)
			{
				game_screen.enemy2.enemyPosition_X += game_screen.bg_speed;
			}
			if (game_screen.enemy3.isActive)
			{
				game_screen.enemy3.enemyPosition_X += game_screen.bg_speed;
			}
			if (game_screen.enemy4.isActive)
			{
				game_screen.enemy4.enemyPosition_X += game_screen.bg_speed;
			}
			if (game_screen.boss.isActive || game_screen.boss.bossHealth <= 0)
			{
				game_screen.boss.bossPosition_X += game_screen.bg_speed;
			}
			// Step 5: scroll the power-up icon with the background
			game_screen.powerUp.shiftIcon(game_screen.bg_speed);
		}
		// Spawn enemy2 when hero reaches halfway across the screen
		if (!game_screen.enemy2Spawned && game_screen.hero1.characterPosition_X >= SCREEN_WIDTH / 2)
		{
			game_screen.enemy2.isActive = true;
			game_screen.enemy2Spawned = true;
		}

		if (game_screen.level == 1 && !game_screen.enemy3Spawned && game_screen.enemy1.enemyHealth <= 0)
		{
			game_screen.enemy3.isActive = true;
			game_screen.enemy3Spawned = true;
		}

		if (game_screen.level == 1 && !game_screen.enemy4Spawned && game_screen.enemy2.enemyHealth <= 0)
		{
			game_screen.enemy4.isActive = true;
			game_screen.enemy4Spawned = true;
			game_screen.enemy4.enemyPosition_X = SCREEN_WIDTH ;
		}

		if (game_screen.level == 2 && !game_screen.enemy4Spawned && game_screen.enemy1.enemyHealth <= 0)
		{
			game_screen.enemy4.isActive = true;
			game_screen.enemy4Spawned = true;
			game_screen.enemy4.enemyPosition_X = SCREEN_WIDTH+12;	
		}

		// Spawn boss when hero reaches 75% across the screen
		if (!game_screen.bossSpawned && game_screen.hero1.characterPosition_X >= (SCREEN_WIDTH * 0.75))
		{
			game_screen.boss.isActive = true;
			game_screen.bossSpawned = true;
		}

		game_screen.enemy1.move_enemy(game_screen.hero1);
		game_screen.enemy2.move_enemy(game_screen.hero1);
		game_screen.enemy3.move_enemy(game_screen.hero1);
		game_screen.enemy4.move_enemy(game_screen.hero1);
		game_screen.boss.move_boss(game_screen.hero1);

		// Handle Trap movement for Level 2
		if (game_screen.level == 2 && game_screen.level2Trap.isActive)
		{
			if (game_screen.rightPressed && !game_screen.hero1.isJumping)
			{
				game_screen.level2Trap.shiftTraps(-game_screen.bg_speed);
			}
			else if (game_screen.leftPressed && !game_screen.hero1.isJumping)
			{
				game_screen.level2Trap.shiftTraps(game_screen.bg_speed);
			}
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
	}
}
void hero_hit_loop()
{
	if (game_screen.hero1.gettingHit)
	{
		game_screen.hero1.hit_index++;
		if (game_screen.hero1.hit_index >= game_screen.hero1.character_idle_hit_R_images.size() - 1)
		{
			game_screen.hero1.hit_index = 0;
			// game_screen.hero1.gettingHit = false;
		}
	}
}
int counter = 0;
void all_50_ms_ticks()
{
	if (screens.top() == "game_screen" || screens.top() == "victory")
	{
		
		if (game_screen.hero1.isDead)
		{
			screens.pop();
			screens.push("gameOver");
		}
		// --- ADD YOUR LEVEL TRANSITION CONDITION HERE ---
		
		else if ((game_screen.level == 1 && game_screen.enemy1.enemyHealth == 0 && game_screen.enemy2.enemyHealth == 0 && game_screen.enemy3.enemyHealth == 0 && game_screen.enemy4.enemyHealth == 0 && game_screen.boss.bossHealth == 0) ||
			(game_screen.level == 2 && game_screen.enemy1.enemyHealth == 0 && game_screen.enemy2.enemyHealth == 0 && game_screen.enemy4.enemyHealth == 0 && game_screen.boss.bossHealth == 0))
		{
		
			if (counter == 0) {
				screens.push("victory");
				counter++;
			}
			else{
				cout << "init called" << endl;
				game_screen.initgame_screen(2);
				mciSendString("close gamebg", NULL, 0, NULL);
				mciSendString("play gamebg2 repeat", NULL, 0, NULL);
				
			}
			
		}
		// ------------------------------------------------

		character_movement();
		enemy_movement();
		update_attack_animation();
		hero_hit_loop();
		// Step 5 & 6: update power-up collision and revert check
		if (game_screen.level == 1)
		{
			game_screen.powerUp.update(game_screen.hero1);
			game_screen.powerUp.checkRevert(game_screen.enemy1, game_screen.enemy2, game_screen.enemy3, game_screen.enemy4, game_screen.boss, game_screen.hero1);
		}

		// Handle Trap Collision for Level 2
		if (game_screen.level == 2)
		{
			game_screen.level2Trap.checkCollision(game_screen.hero1);
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
	mciSendString("open \"resources//credit//credit_bg.mp3\" alias creditbg", NULL, 0, NULL);
	// iSetTimer(50,moveBG);
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Obscure Defiled");

	// Only initialize menu screen at startup - others load on-demand
	initPlayerProfile(playerProfile);

	menu.initmenubar();
	setting.initsettingbar(menu.images[0]);
	initIntroScreen();
	credit.initcreditbar();
	after_level_1_intro_screen.initIntroScreen();
	game_screen.initgame_screen(playerProfile.levelReached);
	// level_2_screen.initgame_screen(); // Prevents vector out of range crash
	createAccountScreen.initCreateAccountScreen(menu.images[0]);
	profileScreen.initProfileScreen(menu.images[0]);
	controlsScreen.initControlsScreen();
	gameOverScreen.initGameOverScreen();
	cout << "level: " << playerProfile.levelReached;
	iSetTimer(200, character_idle_animation);
	iSetTimer(50, all_50_ms_ticks);
	// iSetTimer(1000, reset_movement);
	iSetTimer(20, physics_update);
	// iSetTimer(80, character_movement);
	// iSetTimer(100, enemy_movement);
	// iSetTimer(50, update_attack_animation);
	// iSetTimer(100, hero_hit_loop);
	//  iSetTimer(100, boss_hit_loop);

	screens.push("Menu");
	// menu_images[1] = menu.initmenubar1();
	if (screens.top() == "Menu")
	{

		mciSendString("play bgsong repeat", NULL, 0, NULL);
	}
	else if (playerProfile.levelReached == 1)
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
