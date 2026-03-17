

#ifndef POWER_H
#define POWER_H

		
#include <vector>
#include <cstdio>

#include "character_functions\Hero.hpp"
#include "enemy_functions\enemy.hpp"

			using namespace std;

		struct PowerUpIcon
		{
			double x = 600;
			double y = 100;
			double width = 64;
			double height = 64;
			int    textureId = -1;
			bool   isVisible = true;

			void init(double posX, double posY, double w = 64, double h = 64)
			{
				x = posX; y = posY; width = w; height = h;
				isVisible = true;
				textureId = iLoadImage("resources//power_up_icon//damage_up//Power_up_icon.png");
			}

			void draw()
			{
				if (isVisible && textureId >= 0)
					iShowImage(x, y, (int)width, (int)height, textureId);
			}

			// Move the icon with the scrolling background
			void shift(double dx) { if (isVisible) x += dx; }

			// AABB collision with the 152x152 hero box
			bool collidesWithHero(const Hero& hero) const
			{
				if (!isVisible) return false;
				double hx = hero.characterPosition_X;
				double hy = hero.characterPosition_Y;
				return (hx < x + width) && (hx + 152 > x)
					&& (hy < y + height) && (hy + 152 > y);
			}
		};

		// ─────────────────────────────────────────────────────────────
		//  PowerUpSystem
		// ─────────────────────────────────────────────────────────────
		struct PowerUpSystem
		{
			PowerUpIcon icon;
			bool isPoweredUp = false;

			// Saved primary stats (restored when power-up ends)
			double sv_speed = 20.0;
			double sv_attack_damage = 20.0;

			// Power-Up sprite vectors (loaded once in init)
			vector<int> pu_idle_R, pu_idle_L;
			vector<int> pu_run_R, pu_run_L;
			vector<int> pu_jump_R, pu_jump_L;
			vector<int> pu_attack_R, pu_attack_L;
			vector<int> pu_hit_R, pu_hit_L;
			vector<int> pu_dead_R, pu_dead_L;

			// Saved Normal sprite vectors (restored on revert)
			vector<int> sv_idle_R, sv_idle_L;
			vector<int> sv_run_R, sv_run_L;
			vector<int> sv_jump_R, sv_jump_L;
			vector<int> sv_attack_R, sv_attack_L;
			vector<int> sv_hit_R, sv_hit_L;
			vector<int> sv_dead_R, sv_dead_L;

			// ── init: load all Power-Up textures and place the icon ──
			void init(double iconX = 600.0, double iconY = 100.0)
			{
				isPoweredUp = false;
				icon.init(iconX, iconY, 64, 64);

				// Helper lambda-style macro for loading numbered frames
				// Idle R/L (4 frames each)
				pu_idle_R.clear(); pu_idle_L.clear();
				for (int i = 1; i <= 4; i++) {
					char a[200];
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Idle//idle_right_%d.png", i);
					pu_idle_R.push_back(iLoadImage(a));
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Idle//idle_left_%d.png", i);
					pu_idle_L.push_back(iLoadImage(a));
				}

				// Walk R/L (4 frames each)
				pu_run_R.clear(); pu_run_L.clear();
				for (int i = 1; i <= 4; i++) {
					char a[200];
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Walking//walking_right_%d.png", i);
					pu_run_R.push_back(iLoadImage(a));
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Walking//walking_left_%d.png", i);
					pu_run_L.push_back(iLoadImage(a));
				}

				// Jump R/L  (note: asset filename typo for right frame 2)
				pu_jump_R.clear(); pu_jump_L.clear();
				for (int i = 1; i <= 4; i++) {
					char a[200];
					if (i == 2)
						sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Jumping//jumpin_right_%d.png", i);
					else
						sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Jumping//jumping_right_%d.png", i);
					pu_jump_R.push_back(iLoadImage(a));
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Jumping//jumping_left_%d.png", i);
					pu_jump_L.push_back(iLoadImage(a));
				}

				// Attack / Ground Hitting R/L (4 frames each)
				pu_attack_R.clear(); pu_attack_L.clear();
				for (int i = 1; i <= 4; i++) {
					char a[200];
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Ground Hitting//hit_right_%d.png", i);
					pu_attack_R.push_back(iLoadImage(a));
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Ground Hitting//hit_left_%d.png", i);
					pu_attack_L.push_back(iLoadImage(a));
				}

				// Getting Hit R/L (3 frames each)
				pu_hit_R.clear(); pu_hit_L.clear();
				for (int i = 1; i <= 3; i++) {
					char a[200];
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Getting Hit//idle+knife//idle_right_%d.png", i);
					pu_hit_R.push_back(iLoadImage(a));
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Getting Hit//idle+knife//idle_left_%d.png", i);
					pu_hit_L.push_back(iLoadImage(a));
				}

				// Death: 2 "Dead from above" frames + 1 "Death" frame each side
				pu_dead_R.clear(); pu_dead_L.clear();
				for (int i = 1; i <= 2; i++) {
					char a[200];
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Dead from above//dead_above_right_%d.png", i);
					pu_dead_R.push_back(iLoadImage(a));
					sprintf_s(a, "resources//Main_Character//Power Up//With Knife//Dead from above//dead_above_left_%d.png", i);
					pu_dead_L.push_back(iLoadImage(a));
				}
				pu_dead_R.push_back(iLoadImage("resources//Main_Character//Power Up//With Knife//Dead from above//right_dead_3.png"));
				pu_dead_L.push_back(iLoadImage("resources//Main_Character//Power Up//With Knife//Dead from above//left_dead_3.png"));
			}

			// ── Draw the icon each frame ──
			void draw() { icon.draw(); }

			// ── Scroll the icon with the background ──
			void shiftIcon(double dx) { icon.shift(dx); }

			// ── Called every 50 ms ──
			void update(Hero& hero)
			{
				if (!isPoweredUp && icon.collidesWithHero(hero))
					activate(hero);
			}

			// ── Activate: swap hero sprites to Power-Up set and boost stats ──
			void activate(Hero& hero)
			{
				isPoweredUp = true;
				icon.isVisible = false;

				// Save Normal vectors
				sv_idle_R = hero.character_idle_R_images;
				sv_idle_L = hero.character_idle_L_images;
				sv_run_R = hero.character_run_R_images;
				sv_run_L = hero.character_run_L_images;
				sv_jump_R = hero.character_jump_R_images;
				sv_jump_L = hero.character_jump_L_images;
				sv_attack_R = hero.character_attack_R_images;
				sv_attack_L = hero.character_attack_L_images;
				sv_hit_R = hero.character_idle_hit_R_images;
				sv_hit_L = hero.character_idle_hit_L_images;
				sv_dead_R = hero.character_dead_R_images;
				sv_dead_L = hero.character_dead_L_images;

				// Save primary stats before boosting
				sv_speed = hero.base_speed;
				sv_attack_damage = hero.attack_damage;

				// Boost: speed +5%, hit damage +10%
				hero.character_speed = hero.base_speed * 1.05;
				hero.attack_damage   = hero.attack_damage * 1.10;

				// Swap in Power-Up sprites
				hero.character_idle_R_images = pu_idle_R;
				hero.character_idle_L_images = pu_idle_L;
				hero.character_run_R_images = pu_run_R;
				hero.character_run_L_images = pu_run_L;
				hero.character_jump_R_images = pu_jump_R;
				hero.character_jump_L_images = pu_jump_L;
				hero.character_attack_R_images = pu_attack_R;
				hero.character_attack_L_images = pu_attack_L;
				hero.character_idle_hit_R_images = pu_hit_R;
				hero.character_idle_hit_L_images = pu_hit_L;
				hero.character_dead_R_images = pu_dead_R;
				hero.character_dead_L_images = pu_dead_L;
			}

			// ── Called every 50 ms – reverts when all Level-1 enemies die ──
			void checkRevert(const Enemy& e1, const Enemy& e2, const Enemy& e3, const Enemy& e4,
				const Boss& boss, Hero& hero)
			{
				if (!isPoweredUp) return;
				if (e1.enemyHealth <= 0 && e2.enemyHealth <= 0 && e3.enemyHealth <= 0 && e4.enemyHealth <= 0 && boss.bossHealth <= 0)
					revert(hero);
			}

			// ── Restore Normal sprite vectors and primary stats ──
			void revert(Hero& hero)
			{
				isPoweredUp = false;
				hero.character_idle_R_images = sv_idle_R;
				hero.character_idle_L_images = sv_idle_L;
				hero.character_run_R_images = sv_run_R;
				hero.character_run_L_images = sv_run_L;
				hero.character_jump_R_images = sv_jump_R;
				hero.character_jump_L_images = sv_jump_L;
				hero.character_attack_R_images = sv_attack_R;
				hero.character_attack_L_images = sv_attack_L;
				hero.character_idle_hit_R_images = sv_hit_R;
				hero.character_idle_hit_L_images = sv_hit_L;
				hero.character_dead_R_images = sv_dead_R;
				hero.character_dead_L_images = sv_dead_L;

				// Restore primary speed and attack damage
				hero.character_speed = sv_speed;
				hero.attack_damage   = sv_attack_damage;
			}
		};

#endif // POWER_H
