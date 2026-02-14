#include "enemy.hpp"
#include "../character_functions/Hero.hpp"
#include <iostream>
#include <cmath>

using namespace std;

void Enemy::move_enemy(Hero& hero1)
{
    if (!isActive) return; // Don't move inactive enemies

    double characterX = hero1.characterPosition_X;
    double characterY = hero1.characterPosition_Y;
    if (abs(enemyPosition_X - characterX) < 26 && (enemyPosition_Y == characterY)) {
        hero1.takeDamage(2);
        hero1.gettingHit = true;
    } else {
        hero1.gettingHit = false;
    }

    if (enemyPosition_X > characterX + 25)
    {
        enemyPosition_X -= enemy_speed;
        isright = false;
    }
    else if (enemyPosition_X < characterX - 25)
    {
        enemyPosition_X += enemy_speed;
        isright = true;
    }
    movement_index++;
    if (movement_index >= (int)enemy_idle_R_images.size())
    {
        movement_index = 0;
    }
}

void Boss::move_boss(Hero& hero1)
{
    if (!isActive) return; // Don't move inactive boss

    double characterX = hero1.characterPosition_X;
    double characterY = hero1.characterPosition_Y;
    //boss attack check
    if (abs(bossPosition_X - characterX) < 66 && (bossPosition_Y == characterY))
    {
        if (!isAttacking)
        {
            isAttacking = true;
            attack_index = 0;
        }
    }
    else
    {
        isAttacking = false;
        attack_index = 0;
    }
    // Boss collision check
    if (abs(bossPosition_X - characterX) < 55 && (bossPosition_Y == characterY))
    {
        hero1.takeDamage(4); // Boss does more damage
        cout << "Boss hit! Hero health: " << hero1.HeroHealth << endl;
        hero1.gettingHit = true;
    }
    else
    {
        hero1.gettingHit = false;
    }

    // Boss AI - chase the hero
    if (bossPosition_X > characterX + 50)
    {
        bossPosition_X -= boss_speed;
        isright = false;
    }
    else if (bossPosition_X < characterX - 50)
    {
        bossPosition_X += boss_speed;
        isright = true;
    }

    movement_index++;
    if (movement_index >= (int)boss_walking_R_images.size())
    {
        movement_index = 0;
    }
}
