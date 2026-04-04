#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

// Forward declaration of idle index getter
extern int getIdleIndex();
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BUTTON_WIDTH 242
#define BUTTON_HEIGHT 62
#define HOVER_COOLDOWN 300 // milliseconds
#include <iostream>
#include "enemy_functions\enemy.hpp";
#include "character_functions\Hero.hpp";
#include "level_handler.hpp"
#include <vector>
#include <array>
#include "trap.hpp"
#include "cloud.hpp"
#include "../cloud2.hpp"
#include "power.hpp"
#include "lava.hpp"
#include "lightning.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "rain.hpp"
using namespace std;
struct GameScreen
{
    int level;
   // Lvl_1_GameScreen level_1_screen;
    //Lvl_2_GameScreen level_2_screen;
    vector<int> BgImages;
    vector<int> health_bar_images;
    int victoryImage;
    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;
    Boss boss;
    AlphaBoss alphaBoss;
    Hero hero1;
    Trap level2Trap;
    Lava level3Lava;
    Cloud cloud1;
    Cloud cloud2;
    CloudLayer cloudLayer1;
    CloudLayer cloudLayer2;
    Lightning lightning1;
    RainSystem rainEffect;
    PowerUpSystem powerUp;
    bool spacePressed = false;
    bool rightPressed = false;
    bool leftPressed = false;
    int x = 0;
    double jumpVelocity = 0.0;
    double gravity = 2.0;
    double base_gravity = 5;
    double groundY = 100.0;
    double bg_speed = 4.0;
    bool enemy2Spawned = false;
    bool enemy3Spawned = false;
    bool enemy4Spawned = false;
    bool bossSpawned = false;
    bool alphaBossSpawned = false;
    int hitOverlayImage = 0;
    vector<int> animatedObstacleFrames;
    double animatedObstacleX = 980.0;
    double animatedObstacleY = 100.0;
    int animatedObstacleWidth = 110;
    int animatedObstacleHeight = 90;
    bool animatedObstacleVisible = false;
    int animatedObstacleFrameIndex = 0;
    int animatedObstacleFrameTimer = 0;
    int animatedObstacleDamageCooldown = 0;
    int projectileImage = 0;
    bool projectileActive = false;
    bool projectileRight = true;
    double projectileX = 0.0;
	double projectileY = 0.0;
    double projectileSpeed = 28.0;
    int projectileWidth =40;
    int projectileHeight =20;
    int healthRecoverIconImage = 0;
    bool healthRecoverUsed = false;
    int levelScore = 0;
	int levelScores[4]; // Index 0 unused, levels start from 1
    double levelElapsedSeconds = 0.0;
    vector<double> enemySpawnTimes;
    vector<bool> enemySpawnTracked;
    vector<bool> enemyKillScored;
	
    double bossSpawnTime = 0.0;
    bool bossSpawnTracked = false;
    bool bossKillScored = false;
    int hitOverlayTimerTicks = 0;
    int mainObstacleImage = 0;
    double mainObstacleX = 760.0;
    double mainObstacleY = 100.0;
    int mainObstacleWidth = 70;
    int mainObstacleHeight = 110;
    bool heroMovementBlockedByMainObstacle = false;

    void randomizeMainObstacleX()
    {
        static bool seeded = false;
        if (!seeded)
        {
            srand((unsigned int)time(NULL));
            seeded = true;
        }

        int minX = 250+ 20;
        int maxX = SCREEN_WIDTH - 100 - mainObstacleWidth;
        if (maxX <= minX)
        {
            mainObstacleX = minX;
            return;
        }

        mainObstacleX = minX + (rand() % (maxX - minX + 1));
    }

    void shiftMainObstacle(double dx)
    {
        mainObstacleX += dx;
    }

    bool overlapsMainObstacle(double heroLeft, double heroRight, double heroBottom, double heroTop) const
    {
        if (mainObstacleImage == 0)
        {
            return false;
        }

        double obstacleLeft = mainObstacleX-20;
        double obstacleRight = mainObstacleX + mainObstacleWidth-20;
        double obstacleBottom = mainObstacleY;
        double obstacleTop = mainObstacleY + mainObstacleHeight-20;

        bool horizontalOverlap = (heroRight > obstacleLeft) && (heroLeft < obstacleRight);
        bool verticalOverlap = (heroTop > obstacleBottom) && (heroBottom < obstacleTop);
        return horizontalOverlap && verticalOverlap;
    }

    bool canHeroMoveHorizontal(double deltaX) const
    {
        double heroLeft = hero1.characterPosition_X + 20.0;
        double heroRight = hero1.characterPosition_X + 100;
        double heroBottom = hero1.characterPosition_Y;
        double heroTop = hero1.characterPosition_Y + 120.0;

        return !overlapsMainObstacle(heroLeft + deltaX, heroRight + deltaX, heroBottom, heroTop);
    }

    void keepEnemyOutsideMainObstacle(Enemy &enemy, double previousX)
    {
        if (!enemy.isActive || enemy.enemyHealth <= 0)
        {
            return;
        }

        double width = 100.0;
        double height = 100.0;
        double currentLeft = enemy.enemyPosition_X;
        double currentRight = enemy.enemyPosition_X + width;
        double currentBottom = enemy.enemyPosition_Y;
        double currentTop = enemy.enemyPosition_Y + height;
        if (!overlapsMainObstacle(currentLeft, currentRight, currentBottom, currentTop))
        {
            return;
        }

        double obstacleLeft = mainObstacleX - 20;
        double obstacleRight = mainObstacleX + mainObstacleWidth - 20;
        double previousRight = previousX + width;
        if (previousRight <= obstacleLeft)
        {
            enemy.enemyPosition_X = obstacleLeft - width;
            return;
        }
        if (previousX >= obstacleRight)
        {
            enemy.enemyPosition_X = obstacleRight;
            return;
        }

        double leftResolve = obstacleLeft - width;
        double rightResolve = obstacleRight;
        if (fabs(previousX - leftResolve) <= fabs(previousX - rightResolve))
        {
            enemy.enemyPosition_X = leftResolve;
        }
        else
        {
            enemy.enemyPosition_X = rightResolve;
        }
    }

    // void keepBossOutsideMainObstacle(double previousX)
    // {
    //     if (!boss.isActive || boss.bossHealth <= 0)
    //     {
    //         return;
    //     }

    //     double width = (boss.level == 1 ? 122.0 : 130.0);
    //     double height = (boss.level == 1 ? 81.0 : 170.0);
    //     double currentLeft = boss.bossPosition_X;
    //     double currentRight = boss.bossPosition_X + width;
    //     double currentBottom = boss.bossPosition_Y;
    //     double currentTop = boss.bossPosition_Y + height;
    //     if (!overlapsMainObstacle(currentLeft, currentRight, currentBottom, currentTop))
    //     {
    //         return;
    //     }

    //     double obstacleLeft = mainObstacleX;
    //     double obstacleRight = mainObstacleX + mainObstacleWidth;
    //     double previousRight = previousX + width;
    //     if (previousRight <= obstacleLeft)
    //     {
    //         boss.bossPosition_X = obstacleLeft - width;
    //         return;
    //     }
    //     if (previousX >= obstacleRight)
    //     {
    //         boss.bossPosition_X = obstacleRight;
    //         return;
    //     }

    //     double leftResolve = obstacleLeft - width;
    //     double rightResolve = obstacleRight;
    //     if (fabs(previousX - leftResolve) <= fabs(previousX - rightResolve))
    //     {
    //         boss.bossPosition_X = leftResolve;
    //     }
    //     else
    //     {
    //         boss.bossPosition_X = rightResolve;
    //     }
    // }

    int calculateKillScore(double elapsedSeconds, int maxScore) const
    {
        int earned = maxScore - (int)elapsedSeconds;
        return max(0, min(maxScore, earned));
    }

    void beginLevelScoreTracking()
    {
        levelScore = 0;
        levelElapsedSeconds = 0.0;
        enemySpawnTracked = {false, false, false, false};
        enemyKillScored = {false, false, false, false};
        enemySpawnTimes = {0.0, 0.0, 0.0, 0.0};
        bossSpawnTime = 0.0;
        bossSpawnTracked = false;
        bossKillScored = false;
    }

    void updateScoreTimer(double deltaSeconds)
    {
        if (deltaSeconds > 0.0)
        {
            levelElapsedSeconds += deltaSeconds;
        }
    }

    void updateSpawnTracking()
    {
        Enemy* enemies[4] = {&enemy1, &enemy2, &enemy3, &enemy4};
        for (int i = 0; i < 4; i++)
        {
            if (!enemySpawnTracked[i] && enemies[i]->isActive)
            {
                enemySpawnTracked[i] = true;
                enemySpawnTimes[i] = levelElapsedSeconds;
            }
        }

        if (!bossSpawnTracked && boss.isActive)
        {
            bossSpawnTracked = true;
            bossSpawnTime = levelElapsedSeconds;
        }
    }
	void updateScoreWhenLoadingLevel(playerInfo &info)
    {
		levelScores[0] = 0;
		levelScores[1] = 0;
		levelScores[2] = 0;
		levelScores[3] = 0;

        levelScores[info.levelReached] = info.totalScore;
    }
    void updateKillScores()
    {
        Enemy* enemies[4] = {&enemy1, &enemy2, &enemy3, &enemy4};
        for (int i = 0; i < 4; i++)
        {
            if (enemySpawnTracked[i] && !enemyKillScored[i] && enemies[i]->enemyHealth <= 0)
            {
                double elapsed = levelElapsedSeconds - enemySpawnTimes[i];
                levelScore += calculateKillScore(elapsed, 100);
                enemyKillScored[i] = true;
            }
        }

        if (bossSpawnTracked && !bossKillScored && boss.bossHealth <= 0)
        {
            double elapsed = levelElapsedSeconds - bossSpawnTime;
            levelScore += calculateKillScore(elapsed, 300);
            bossKillScored = true;
        }
        levelScores[level] = levelScore;
    }

    void updateScoreSystem(double deltaSeconds)
    {
        updateScoreTimer(deltaSeconds);
        updateSpawnTracking();
        updateKillScores();
    }

    int getCurrentLevelKillCount() const
    {
        int kills = 0;
        for (int i = 0; i < 4; i++)
        {
            if (enemyKillScored[i])
            {
                kills++;
            }
        }
        if (bossKillScored)
        {
            kills++;
        }
        return kills;
    }

    int getCombinedScoreUpToCurrentLevel() const
    {
		return levelScores[level-1];
    }

    void drawScoreTopRight()
    {
        char scoreText[64];
        sprintf_s(scoreText, "Score: %d", levelScore);
        iText(SCREEN_WIDTH - 190, SCREEN_HEIGHT - 30, scoreText, GLUT_BITMAP_HELVETICA_18);
    }

    void triggerHitOverlay(int durationTicks = 6)
    {
        if (durationTicks > hitOverlayTimerTicks)
        {
            hitOverlayTimerTicks = durationTicks;
        }
    }

    void updateHitOverlayTimer()
    {
        if (hitOverlayTimerTicks > 0)
        {
            hitOverlayTimerTicks--;
        }
    }

    bool shouldShowHitOverlay() const
    {
        return (hitOverlayImage != 0 && (hero1.gettingHit || hitOverlayTimerTicks > 0));
    }

    bool canShowHealthRecoverPrompt() const
    {
        return (level >= 2 && levelScore > 100 && !healthRecoverUsed && healthRecoverIconImage != 0);
    }

    void drawHealthRecoverPrompt()
    {
        if (!canShowHealthRecoverPrompt())
        {
            return;
        }

        int iconX = 40;
        int iconY = SCREEN_HEIGHT / 2;
        int iconWidth = 72;
        int iconHeight = 72;
        iShowImage(iconX, iconY, iconWidth, iconHeight, healthRecoverIconImage);

        char hintText[] = "press H";
        iText(iconX, iconY - 25, hintText, GLUT_BITMAP_HELVETICA_18);
    }

    bool tryUseHealthRecover()
    {
        if (!canShowHealthRecoverPrompt())
        {
            return false;
        }

        hero1.HeroHealth = 100;
        healthRecoverUsed = true;
        mciSendString("close powerupsfx", NULL, 0, NULL);
        mciSendString("open \"resources//sounds//powerUp.mp3\" alias powerupsfx", NULL, 0, NULL);
        mciSendString("play powerupsfx from 0", NULL, 0, NULL);
        return true;
    }

    void init_projectile()
    {
        projectileImage = iLoadImage(level==2?"resources/projectile/4.png":"resources/projectile/2.png");
        projectileActive = false;
        projectileRight = true;
        projectileX = 0.0;
        projectileY = 0.0;
        projectileSpeed = 28.0;
		projectileWidth = level == 2 ? 40:80;
		projectileHeight = level == 2 ? 20:40;
    }

    void spawnProjectile()
    {
        if (level < 2 || projectileImage == 0)
            return;

        projectileActive = true;
        projectileRight = hero1.isright;
        projectileX = hero1.characterPosition_X + (projectileRight ? 118.0 : -20.0);
        projectileY = hero1.characterPosition_Y + 70.0;
    }

    void startHeroAttack()
    {
        bool wasAttacking = hero1.isAttacking;
        hero1.startAttack();
        if (level >= 2 && !wasAttacking && hero1.isAttacking)
        {
            spawnProjectile();
        }
    }

    bool hitEnemyWithProjectile(Enemy &enemy)
    {
        if (!projectileActive || !enemy.isActive || enemy.enemyHealth <= 0)
            return false;

        double projectileLeft = projectileX;
        double projectileRightEdge = projectileX + projectileWidth;
        double projectileBottom = projectileY;
        double projectileTop = projectileY + projectileHeight;

        double enemyWidth = (enemy.level == 1 ? 100.0 : 150.0);
        double enemyHeight = 100.0;
        double enemyLeft = enemy.enemyPosition_X;
        double enemyRightEdge = enemy.enemyPosition_X + enemyWidth;
        double enemyBottom = enemy.enemyPosition_Y;
        double enemyTop = enemy.enemyPosition_Y + enemyHeight;

        bool overlap = (projectileRightEdge > enemyLeft) && (projectileLeft < enemyRightEdge) && (projectileTop > enemyBottom) && (projectileBottom < enemyTop);
        if (!overlap)
            return false;

        enemy.enemy_takeDamage(hero1.attack_damage);
        projectileActive = false;
        return true;
    }

    bool hitBossWithProjectile()
    {
        if (!projectileActive || !boss.isActive || boss.bossHealth <= 0)
            return false;

        double projectileLeft = projectileX;
        double projectileRightEdge = projectileX + projectileWidth;
        double projectileBottom = projectileY;
        double projectileTop = projectileY + projectileHeight;

        double bossWidth = 200.0;
        double bossHeight = 220.0;
        double bossLeft = boss.bossPosition_X;
        double bossRightEdge = boss.bossPosition_X + bossWidth;
        double bossBottom = boss.bossPosition_Y;
        double bossTop = boss.bossPosition_Y + bossHeight;

        bool overlap = (projectileRightEdge > bossLeft) && (projectileLeft < bossRightEdge) && (projectileTop > bossBottom) && (projectileBottom < bossTop);
        if (!overlap)
            return false;

        boss.bosstakeDamage(hero1.attack_damage);
        projectileActive = false;
        return true;
    }

    void updateProjectile()
    {
        if (level < 2 || !projectileActive)
            return;

        projectileX += (projectileRight ? projectileSpeed : -projectileSpeed);

        if (projectileX > SCREEN_WIDTH || projectileX + projectileWidth < 0)
        {
            projectileActive = false;
            return;
        }

        if (hitEnemyWithProjectile(enemy1)) return;
        if (hitEnemyWithProjectile(enemy2)) return;
        if (hitEnemyWithProjectile(enemy3)) return;
        if (hitEnemyWithProjectile(enemy4)) return;
        hitBossWithProjectile();
    }

    void init_animated_obstacle()
    {
        animatedObstacleFrames.clear();
        for (int i = 0; i <= 3; i++)
        {
            char a[200];
            sprintf_s(a, "resources/obstacles/level 1 obstacles animated/frame_%03d.png", i);
            animatedObstacleFrames.push_back(iLoadImage(a));
        }
        animatedObstacleX = 980.0;
        animatedObstacleY = 100.0;
        animatedObstacleWidth = 110;
        animatedObstacleHeight = 90;
        animatedObstacleVisible = false;
        animatedObstacleFrameIndex = 0;
        animatedObstacleFrameTimer = 0;
        animatedObstacleDamageCooldown = 0;
    }

    void shiftAnimatedObstacle(double dx)
    {
        animatedObstacleX += dx;
    }

    void updateAnimatedObstacle(Hero &hero)
    {
        if (animatedObstacleFrames.empty())
            return;

        if (!animatedObstacleVisible && hero.characterPosition_X >= animatedObstacleX - 260)
        {
            animatedObstacleVisible = true;
        }

        if (!animatedObstacleVisible)
            return;

        animatedObstacleFrameTimer++;
        if (animatedObstacleFrameTimer >= 5)
        {
            animatedObstacleFrameTimer = 0;
            animatedObstacleFrameIndex++;
            if (animatedObstacleFrameIndex >= animatedObstacleFrames.size())
            {
                animatedObstacleFrameIndex = 0;
            }
        }

        if (animatedObstacleDamageCooldown > 0)
        {
            animatedObstacleDamageCooldown--;
        }

        if (hero.isJumping)
            return;

        double heroLeft = hero.characterPosition_X + 20;
        double heroRight = hero.characterPosition_X + 132;
        double heroBottom = hero.characterPosition_Y;
        double obstacleLeft = animatedObstacleX;
        double obstacleRight = animatedObstacleX + animatedObstacleWidth;
        double obstacleTop = animatedObstacleY + animatedObstacleHeight;

        bool horizontalOverlap = (heroRight > obstacleLeft) && (heroLeft < obstacleRight);
        bool standingOnObstacle = heroBottom <=150;

        if (horizontalOverlap && standingOnObstacle && animatedObstacleDamageCooldown == 0)
        {
            hero.takeDamage(2);
            hero.gettingHit = true;
            hero.hit_index = 0;
            animatedObstacleDamageCooldown = 6;
        }
    }

    void resetgame (){
        spacePressed = false;
		rightPressed = false;
		leftPressed = false;
		x = 0;
		
		jumpVelocity = 0.0;
		gravity = 2.0;
		base_gravity = 5;
		groundY = 100.0;
		bg_speed = 4.0;
        heroMovementBlockedByMainObstacle = false;
        enemy2Spawned = false;
		enemy3Spawned = false;
		enemy4Spawned = false;
		bossSpawned = false;
        alphaBossSpawned = false;
        animatedObstacleVisible = false;
        animatedObstacleFrameIndex = 0;
        animatedObstacleFrameTimer = 0;
        animatedObstacleDamageCooldown = 0;
        projectileActive = false;
        projectileRight = true;
        projectileX = 0.0;
        projectileY = 0.0;
        healthRecoverUsed = false;
        hitOverlayTimerTicks = 0;
        beginLevelScoreTracking();
        animatedObstacleX = 980.0;
        animatedObstacleY = 100.0;
        randomizeMainObstacleX();
        groundY = hero1.characterPosition_Y;
        enemy2.isActive = false; 
        enemy2.enemyPosition_X = 64;
        enemy3.isActive = false;
        enemy3.enemyPosition_X = SCREEN_WIDTH - 220;
        enemy4.isActive = false;
        enemy4.enemyPosition_X = SCREEN_WIDTH - 360;
        boss.isActive = false; 
        alphaBoss.isActive = false;
        //enemy
        enemy1.enemyPosition_X = SCREEN_WIDTH - 64;
        enemy1.enemyPosition_Y = 100.0;
        enemy1.enemyHealth = 100.0;
        enemy1.isright = false;
		enemy1.enemy_movement_index = 0;
        enemy1.enemy_speed = 8.0;
        enemy1.enemyGettingHit = false;
        enemy1.isAttacking = false;
        enemy1.attack_index = 0;
        enemy1.hit_index = 0;
        enemy1.isActive = true;  // enemy1 is always first — starts active
        enemy1.enemyType = 1;
        //enemy2.enemyPosition_X = SCREEN_WIDTH - 64;
        //enemy2.enemyPosition_Y = 100.0;
        enemy2.enemyHealth = 100.0;
        enemy2.isright = false;
		enemy2.enemy_movement_index = 0;
        enemy2.enemy_speed = 8.0;
        enemy2.enemyGettingHit = false;
        enemy2.isAttacking = false;
        enemy2.attack_index = 0;
        enemy2.hit_index = 0;
        //enemy2.isActive = true; // Whether this enemy is currently active in the game
        enemy2.enemyType = 2;
        enemy3.enemyPosition_Y = 100.0;
        enemy3.enemyHealth = 100.0;
        enemy3.isright = false;
		enemy3.enemy_movement_index = 0;
        enemy3.enemy_speed = 8.0;
        enemy3.enemyGettingHit = false;
        enemy3.isAttacking = false;
        enemy3.attack_index = 0;
        enemy3.hit_index = 0;
        enemy3.enemyType = 3;
        enemy4.enemyPosition_Y = 100.0;
        enemy4.enemyHealth = 100.0;
        enemy4.isright = false;
		enemy4.enemy_movement_index = 0;
        enemy4.enemy_speed = 8.0;
        enemy4.enemyGettingHit = false;
        enemy4.isAttacking = false;
        enemy4.attack_index = 0;
        enemy4.hit_index = 0;
        enemy4.enemyType = 4;
        //boss
        boss.bossPosition_X = SCREEN_WIDTH - 128;
        boss.bossPosition_Y = 100;
        boss.bossHealth = 200.0;
        boss.maxBossHealth = 200.0;
        boss.isright = true;
        boss.movement_index = 0;
        boss.boss_speed = 5.0;
        boss.isActive = false; // Boss spawns later in the game
        boss.isAttacking = false;
        boss.attack_index = 0;
        boss.bossGettingHit = false;
        boss.hit_index = 0;
        boss.attack_timer = 0;
        boss.dead_index = 0;
        boss.dead_timer = 0;
        alphaBoss.alphaPosition_X = SCREEN_WIDTH - 180;
        alphaBoss.alphaPosition_Y = 100.0;
        alphaBoss.alphaHealth = 300.0;
        alphaBoss.maxAlphaHealth = 300.0;
        alphaBoss.isAttacking = false;
        alphaBoss.attack_index = 0;
        alphaBoss.attack_timer = 0;
        alphaBoss.dead_index = 0;
        alphaBoss.dead_timer = 0;
        alphaBoss.isActive = false;
		//hero
		hero1.characterPosition_X = 100;
		hero1.attack_index = 0;
		hero1.dead_index = 0;
		hero1.character_speed = 20;
		hero1.base_speed = 20;
		hero1.attack_damage = 4;
		hero1.isJumping = false;
		hero1.gettingHit = false;
		hero1.isright = true;
		hero1.movement_index = 0;
		hero1.idle_Index = 0;
		hero1.jump_index = 0;
		hero1.hit_index = 0;
		hero1.isMoving = false;
		hero1.isAttacking = false;
		hero1.attack_timer = 0;
		hero1.dead_timer = 0;
		hero1.isDead = false;
		hero1.HeroHealth = 100;
		if (level == 1){
            powerUp.revert(hero1);
            powerUp.init(600.0, 100.0);
            cloud1.initCloud(640, 580, 350, 180);
            lightning1.initLightning(60, 120, 4.0);
            cloud2.initCloud(0, 580, 400, 200);
        }
        if (level == 2)
        {
            level2Trap.isActive = false; // Disabled falling fireballs unconditionally
            rainEffect.initRain();
            lightning1.initLightning(60, 120, 4.0);
        }
        else
        {
            level2Trap.isActive = false;
            rainEffect.isActive = false;
		}
        if (level == 3)
{
    level3Lava.initLava(1280, 100, 350, 80, .12);
}
else
{
    level3Lava.isActive = false;
}
    }
    void initgame_screen(int level)
    {
        this->level = level;
        resetgame();
        BgImages.clear();
        health_bar_images.clear();
        BgImages.push_back(iLoadImage("resources//game_screen//level_1/bg_1//screen_for_level_1_new.jpg"));
        BgImages.push_back(iLoadImage("resources//game_screen//level_2//bg_2//pic.jpg"));
        BgImages.push_back(iLoadImage("resources//game_screen//level_3//bg_3//Screen_for_final_round.png"));
        hero1.init_character_images(level);
        victoryImage= iLoadImage("resources/victory_screen/victory_image.png");
        hitOverlayImage = iLoadImage("resources/game_screen/getting hit frame.png");
        enemy1.initenemy(1,level);         // Initialize Small enemy 1
        enemy2.initenemy(2,level);         // Initialize Small enemy 2
        enemy3.initenemy(3,level);         // Initialize Small enemy 3
        enemy4.initenemy(4,level);         // Initialize Small enemy 4
        alphaBoss.initAlphaBoss(level);
        init_animated_obstacle();
        init_projectile();
        mainObstacleImage = iLoadImage("resources/obstacles/obstacles_main_size/Obstacle_2_main.png");
        healthRecoverIconImage = iLoadImage("resources/power_up_icon/Health_recover/Health_Boast_up.png");

        if (level == 1)
        {
            enemy3.isActive = false;
            enemy3.enemyPosition_X = SCREEN_WIDTH - 220;
            enemy4.isActive = false;
            enemy4.enemyPosition_X = SCREEN_WIDTH - 360;
        }
        else
        {
            enemy3.isActive = false;
            enemy3.enemyPosition_X = SCREEN_WIDTH - 220;
            enemy4.isActive = false;
            enemy4.enemyPosition_X = SCREEN_WIDTH - 360;
        }

        enemy2.isActive = false;       // Spawned later by kill chain
        enemy2.enemyPosition_X = 64;   // Left side spawn when activated
        boss.initboss(level);        // Initialize boss
        boss.isActive = false;        // Boss starts inactive
        alphaBoss.isActive = false;
        enemy1.isActive = true;       // enemy1 is always first — starts active
        if(level == 1){

            cloudLayer1.initCloudLayer("resources\\cloud\\image1.png", 1);
            powerUp.init(600.0, 100.0);
        }
        
        // Trap Initialization for Level 2

        if (level == 2)
        {
            // Initializes the trap ahead of the hero on the ground
            // Ground is at 100, so we can place it somewhere ahead like x=800
            // Image size may vary but a width of 100 and height of 50 works for collisions
            level2Trap.isActive = false; // Disabled falling fireballs
            cloudLayer2.initCloudLayer("resources\\cloud\\image.png", 2); // cloud band at top of screen
            rainEffect.initRain();
            lightning1.initLightning(60, 120, 5.0);
        }
        else
        {
            level2Trap.isActive = false;
            cloudLayer2.isActive = false;
            rainEffect.isActive = false;
        }

        init_health_bar_images();
        if (level == 3)
    {
    level3Lava.initLava(1280, 100, 350, 80, .12);
    }
    else
    {
    level3Lava.isActive = false;
    }
    }

    void init_health_bar_images()
    {
        for (int i = 0; i <= 100; i += 10)
        {
            char a[200];
            sprintf_s(a, "resources/Health Bar//%d Percent//resize_health_bar_%d.png", i, i);
            health_bar_images.push_back(iLoadImage(a));
        }
    }

    void startJump()
    {
        if (!hero1.isJumping)
        {

            hero1.isJumping = true;
            hero1.isMoving = false;
            // record the ground position to return to
            groundY = hero1.characterPosition_Y;
            jumpVelocity = 35.0; // initial jump impulse
            gravity = base_gravity;
            hero1.jump_index = 0;
        }
    }

    void updateJumpPhysics()
    {
        if (hero1.isJumping)
        {
            if (rightPressed)
            {
                if (canHeroMoveHorizontal(hero1.character_speed - 5))
                {
                    heroMovementBlockedByMainObstacle = false;
                    shiftAnimatedObstacle(-bg_speed);
                    shiftMainObstacle(-bg_speed);
                    cloudLayer1.shift(-bg_speed);
                    cloudLayer2.shift(-bg_speed); // scroll clouds during mid-air right move
                    x -= bg_speed;
                    if (x <= -SCREEN_WIDTH)
                    {
                        x = 0;
                    }
                    hero1.characterPosition_X += hero1.character_speed - 5;
                    hero1.isright = true;
                }
                else
                {
                    heroMovementBlockedByMainObstacle = true;
                }
            }
            else if (leftPressed)
            {
                if (canHeroMoveHorizontal(hero1.character_speed - 5))
                {
                    heroMovementBlockedByMainObstacle = false;
                    shiftAnimatedObstacle(+bg_speed);
                    shiftMainObstacle(+bg_speed);
                    cloudLayer1.shift(+bg_speed);
                    cloudLayer2.shift(+bg_speed);
                    x += bg_speed;
                    if (x >= SCREEN_WIDTH)
                    {
                        x = 0;
                    }
                    hero1.characterPosition_X -= hero1.character_speed - 5;
                    hero1.isright = false;
                }
                else
                {
                    heroMovementBlockedByMainObstacle = true;
                }
            }
            // apply vertical movement
            hero1.characterPosition_Y += jumpVelocity;
            jumpVelocity -= gravity;

            // advance jump animation frame
            if (hero1.isright)
            {
                hero1.jump_index++;
                if (hero1.jump_index >= hero1.character_jump_R_images.size())
                {
                    hero1.jump_index = 0;
                }
            }
            else
            {
                hero1.jump_index++;
                if (hero1.jump_index >= hero1.character_jump_L_images.size())
                {
                    hero1.jump_index = 0;
                }
            }
            // landing check
            if (hero1.characterPosition_Y <= groundY)
            {
                hero1.characterPosition_Y = groundY;
                hero1.isJumping = false;
                hero1.isMoving = true;
                jumpVelocity = 0.0;
                gravity = base_gravity;
                hero1.jump_index = 0;
            }
        }
    }

    void handleSpecialKeyboard(unsigned char key)
    {
        // Handle special keyboard input for game controls (e.g., arrow keys for movement)

        if (key == GLUT_KEY_UP)
        {
            startJump();
        }
        else if (key == GLUT_KEY_DOWN)
        {
        }
        else if (key == GLUT_KEY_LEFT)
        {

            leftPressed = true;
            hero1.isMoving = true;
            hero1.isright = false;
        }
        else if (key == GLUT_KEY_RIGHT)
        {

            rightPressed = true;
            hero1.isright = true;

            hero1.isMoving = true;
        }
    }

    void drawgame_screen()
    {
		//cout << hero1.dead_index << " --- " << hero1.character_dead_R_images.size() << endl;
        //...
        iShowImage(-SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BgImages[level-1]);
        iShowImage(x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BgImages[level-1]);
        iShowImage(SCREEN_WIDTH + x, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BgImages[level-1]);

        // Layer: cloud band on top of BG (levels 1 & 2)
        cloudLayer1.draw(level);
        cloudLayer2.draw(level);

        // cout << "Hero Health: " << hero1.HeroHealth << endl;
        iShowImage(SCREEN_WIDTH / 2 - (275 / 2), SCREEN_HEIGHT - 150, 275, 200, health_bar_images[(hero1.HeroHealth / 10)]);
if (level == 2)
{
    lightning1.drawLightning(level);
    lightning1.checkCollision(hero1, level);
}

        // Draw boss health bar if boss is active
        if (boss.isActive && !boss.boss_health_bar_images.empty())
        {

            double currentHealth = max(0.0, min(200.0, boss.bossHealth)); // Clamp health between 0 and 200

            // Calculate index
            int frameIndex = (int)floor((currentHealth / 200.0) * 15);
            iShowImage(boss.bossPosition_X - 10, boss.bossPosition_Y + (level==1?100:200), 122, 20, boss.boss_health_bar_images[frameIndex]);
        }
        if (alphaBossSpawned && alphaBoss.alphaHealth > 0 && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(alphaBoss.maxAlphaHealth, alphaBoss.alphaHealth));
            int frameIndex = (int)floor((currentHealth / alphaBoss.maxAlphaHealth) * 15.0);
            if (frameIndex < 0) frameIndex = 0;
            if (frameIndex > 15) frameIndex = 15;
            iShowImage(alphaBoss.alphaPosition_X + 18, alphaBoss.alphaPosition_Y + 190, 122, 20, boss.boss_health_bar_images[frameIndex]);
        }
        if (enemy1.isActive && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(100.0, enemy1.enemyHealth)); // Clamp health between 0 and 100

            // Calculate index
            int frameIndex = (int)floor((currentHealth / 100.0) * 15);
            iShowImage(enemy1.enemyPosition_X - 2, enemy1.enemyPosition_Y + 100, 50, 15, boss.boss_health_bar_images[frameIndex]);
        }
        if (enemy2.isActive && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(100.0, enemy2.enemyHealth)); // Clamp health between 0 and 100

            // Calculate index
            int frameIndex = (int)floor((currentHealth / 100.0) * 15);
            iShowImage(enemy2.enemyPosition_X - 2, enemy2.enemyPosition_Y + 100, 50, 15, boss.boss_health_bar_images[frameIndex]);
        }
        if (enemy3.isActive && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(100.0, enemy3.enemyHealth));

            int frameIndex = (int)floor((currentHealth / 100.0) * 15);
            iShowImage(enemy3.enemyPosition_X - 2, enemy3.enemyPosition_Y + 100, 50, 15, boss.boss_health_bar_images[frameIndex]);
        }
        if (enemy4.isActive && !boss.boss_health_bar_images.empty())
        {
            double currentHealth = max(0.0, min(100.0, enemy4.enemyHealth));

            int frameIndex = (int)floor((currentHealth / 100.0) * 15);
            iShowImage(enemy4.enemyPosition_X - 2, enemy4.enemyPosition_Y + 100, 50, 15, boss.boss_health_bar_images[frameIndex]);
        }
        hero1.show_chracter_moving();
        if (mainObstacleImage != 0)
        {
            iShowImage(mainObstacleX, mainObstacleY, mainObstacleWidth, mainObstacleHeight, mainObstacleImage);
        }
        if (level >= 2 && projectileActive && projectileImage != 0)
        {
            iShowImage(projectileX, projectileY, projectileWidth, projectileHeight, projectileImage);
        }
        if (level == 3)
{
    level3Lava.drawLava(level);
    level3Lava.checkCollision(hero1);
    if (!level3Lava.isActive)
    {
        level3Lava.spawnLava(1280, 100, level);
    }
}
        enemy1.show_enemy_moving();
        enemy2.show_enemy_moving();
        enemy3.show_enemy_moving();
        enemy4.show_enemy_moving();
        if (animatedObstacleVisible && !animatedObstacleFrames.empty())
        {
            iShowImage(animatedObstacleX, animatedObstacleY-20, animatedObstacleWidth, animatedObstacleHeight, animatedObstacleFrames[animatedObstacleFrameIndex]);
        }
        boss.show_boss_moving();
        alphaBoss.show_alpha_moving();

        // Draw trap for level 2
        if (level == 2 && level2Trap.isActive)
        {
            level2Trap.drawTrap();
        }
        
        if (level == 2)
        {
            std::vector<BoundingBox> surfaces;
            surfaces.push_back({hero1.characterPosition_X + 20, hero1.characterPosition_Y, 112, 120});
            if(enemy1.isActive && enemy1.enemyHealth > 0) surfaces.push_back({enemy1.enemyPosition_X, enemy1.enemyPosition_Y, 150, 100});
            if(enemy2.isActive && enemy2.enemyHealth > 0) surfaces.push_back({enemy2.enemyPosition_X, enemy2.enemyPosition_Y, 150, 100});
            if(enemy3.isActive && enemy3.enemyHealth > 0) surfaces.push_back({enemy3.enemyPosition_X, enemy3.enemyPosition_Y, 150, 100});
            if(enemy4.isActive && enemy4.enemyHealth > 0) surfaces.push_back({enemy4.enemyPosition_X, enemy4.enemyPosition_Y, 150, 100});
            if(boss.isActive && boss.bossHealth > 0) surfaces.push_back({boss.bossPosition_X, boss.bossPosition_Y, 200, 220});
            
            if(level2Trap.isActive) {
                for(int i = 0; i < (int)level2Trap.traps.size(); i++) {
                    if(level2Trap.traps[i].active) {
                        surfaces.push_back({level2Trap.traps[i].x, level2Trap.traps[i].y, (double)level2Trap.trapWidth, (double)level2Trap.trapHeight});
                    }
                }
            }
            
            if(animatedObstacleVisible) surfaces.push_back({animatedObstacleX, animatedObstacleY, (double)animatedObstacleWidth, (double)animatedObstacleHeight});
            if(mainObstacleImage != 0) surfaces.push_back({mainObstacleX, mainObstacleY, (double)mainObstacleWidth, (double)mainObstacleHeight - 20});
            
            rainEffect.drawRain(groundY, surfaces);
        }
        if(level == 1 ){
            powerUp.draw();    
        }
        // Full-screen hit overlay — drawn last so it appears on top of everything
        if (shouldShowHitOverlay())
        {
            iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, hitOverlayImage);
        }
        drawHealthRecoverPrompt();
        drawScoreTopRight();

    }
};

#endif