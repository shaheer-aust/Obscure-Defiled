#include "Hero.hpp"
#include "Screens\game_screen.hpp"
#include <vector>
using namespace std;
void reset_movement()
{
	game.resetMovement();
}
void physics_update()
{
	if (screens.top() == "Game")
	{
		game.updatePhysics();
	}
}

void character_movement()
{
	if (game.rightPressed && !game.hero1.isJumping)
	{
		game.x -= game.bg_speed;
		if(game.enemy1.isActive){
			game.enemy1.enemyPosition_X -= game.bg_speed;
		}
		if(game.enemy2.isActive){
			game.enemy2.enemyPosition_X -= game.bg_speed;
		}
		if (game.boss.isActive || game.boss.bossHealth <= 0){
			game.boss.bossPosition_X -= game.bg_speed;
		}
		if (game.x <= -SCREEN_WIDTH)
		{
			game.x = 0;
		}
		game.hero1.isMoving = true;
		game.hero1.movement_index++;
		game.hero1.characterPosition_X += game.hero1.character_speed;
		if (game.hero1.characterPosition_X >= SCREEN_WIDTH - 70)
		{
			game.hero1.characterPosition_X = SCREEN_WIDTH - 70;
		}
	}
	else if (game.leftPressed && !game.hero1.isJumping)
	{
		game.x += game.bg_speed;
		if(game.enemy1.isActive){
			game.enemy1.enemyPosition_X += game.bg_speed;
		}
		if(game.enemy2.isActive){
			game.enemy2.enemyPosition_X += game.bg_speed;
		}
		if(game.boss.isActive || game.boss.bossHealth<=0){
			game.boss.bossPosition_X += game.bg_speed;
		}
		if (game.x >= SCREEN_WIDTH)
		{  
			game.x = 0;
		}
		game.hero1.isMoving = true;
		game.hero1.movement_index++;
		game.hero1.characterPosition_X -= game.hero1.character_speed;
		if (game.hero1.characterPosition_X < 0)
		{
			game.hero1.characterPosition_X = 0;
		}
	}
	else if (game.hero1.isJumping)
	{
				if(game.enemy1.isActive){
			game.enemy1.enemyPosition_X += game.bg_speed;
		}
		if(game.enemy2.isActive){
			game.enemy2.enemyPosition_X += game.bg_speed;
		}
		if(game.boss.isActive || game.boss.bossHealth<=0){
			game.boss.bossPosition_X += game.bg_speed;
		}
		if (game.x >= SCREEN_WIDTH)
		{  
			game.x = 0;
		}
		game.hero1.isMoving = false;
	}
	else
	{
		game.hero1.isMoving = false;
	}
}