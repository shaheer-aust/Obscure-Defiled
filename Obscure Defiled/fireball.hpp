#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include <vector>
#include <cstdlib>
#include <ctime>
#include "character_functions/Hero.hpp"
#include "enemy_functions/enemy.hpp"

using namespace std;

#define FB_COUNT        3
#define FB_SPEED        0.2
#define FB_WIDTH        60
#define FB_HEIGHT       60
#define FB_EFFECT_W     90
#define FB_EFFECT_H     90
// y above which cloud covers the ball spawn area (clouds start ~425 in game)
#define FB_SPAWN_MIN_Y  720     // just above the screen top (y=0 is bottom in iGraphics)
#define FB_SPAWN_MAX_Y  900     // extra off-screen buffer
// ground level — when ball.y reaches this, swap to effect image
#define FB_GROUND_Y     100
// effect stays visible for this many ticks before resetting
#define FB_EFFECT_TICKS 12

struct Fireball
{
    double x;
    double y;
    double speed;
    bool showEffect;    // false = ball.png, true = effect.png
    int  effectTimer;   // counts down after effect appears
    bool hitHero;       // true if it has already damaged the hero this drop
    bool hitEnemy[4];   // true if it has damaged mini-enemies this drop
    bool hitBoss;       // true if it has damaged the boss this drop
};

struct FireballSystem
{
    vector<Fireball> balls;
    int ballImage   = 0;
    int effectImage = 0;
    bool isActive   = false;

    // ------------------------------------------------------------------ init
    void init()
    {
        static bool seeded = false;
        if (!seeded) { srand((unsigned)time(NULL)); seeded = true; }

        ballImage   = iLoadImage("resources/Fire Ball/Ball/ball.png");
        effectImage = iLoadImage("resources/Fire Ball/Ground effect/effect.png");

        balls.resize(FB_COUNT);
        for (int i = 0; i < FB_COUNT; i++)
            spawnBall(balls[i], true /* initial stagger */);

        isActive = true;
    }

    // --------------------------------------------------- spawn / reset a ball
    void spawnBall(Fireball &fb, bool stagger = false)
    {
        fb.x             = rand() % (SCREEN_WIDTH - FB_WIDTH);
        // stagger starting heights so they don't all arrive at once
        int extra        = stagger ? (rand() % 600) : 0;
        fb.y             = (double)(FB_SPAWN_MIN_Y + extra);
        fb.speed         = FB_SPEED *1.6;
        fb.showEffect    = false;
        fb.effectTimer   = 0;
        fb.hitHero       = false;
        for (int i = 0; i < 4; i++) fb.hitEnemy[i] = false;
        fb.hitBoss       = false;
    }

    // --------------------------------------------------------------- update
    void update()
    {
        if (!isActive) return;

        for (int i = 0; i < (int)balls.size(); i++)
        {
            Fireball &fb = balls[i];

            if (fb.showEffect)
            {
                // effect is visible — count down then reset
                fb.effectTimer--;
                if (fb.effectTimer <= 0)
                    spawnBall(fb);  // reset to top
                continue;
            }

            // fall downward (y decreases in iGraphics — bottom is y=0)
            fb.y -= fb.speed;

            // swap to effect when reaching ground level
            if (fb.y <= (double)FB_GROUND_Y)
            {
                fb.y          = (double)FB_GROUND_Y;
                fb.showEffect = true;
                fb.effectTimer = FB_EFFECT_TICKS;
            }
        }
    }

    // ----------------------------------------------------------------- draw
    // Call this AFTER cloud layer draw so balls appear BEHIND clouds
    void draw()
    {
        if (!isActive) return;

        for (int i = 0; i < (int)balls.size(); i++)
        {
            const Fireball &fb = balls[i];
            if (fb.showEffect)
            {
                if (effectImage != 0)
                    iShowImage(fb.x - 15, fb.y - 10, FB_EFFECT_W, FB_EFFECT_H, effectImage);
            }
            else
            {
                if (ballImage != 0)
                    iShowImage(fb.x, fb.y, FB_WIDTH, FB_HEIGHT, ballImage);
            }
        }
    }

    // -------------------------------------------------------- collision check
    // Matches lightning checkCollision style — center-based AABB per target.
    void checkCollisions(Hero &hero,
                         Enemy &enemy1, Enemy &enemy2,
                         Enemy &enemy3, Enemy &enemy4,
                         Boss  &boss)
    {
        if (!isActive) return;

        for (int i = 0; i < (int)balls.size(); i++)
        {
            Fireball &fb = balls[i];
            if (fb.showEffect)        continue;  // effect phase — no collision

            double ballCenterX = fb.x + (FB_WIDTH  / 2.0);
            double ballCenterY = fb.y + (FB_HEIGHT / 2.0);

            // ---- Hero ----
            double heroCenterX = hero.characterPosition_X + (152.0 / 2.0);
            double heroCenterY = hero.characterPosition_Y + (152.0 / 2.0);

            bool hitX = (ballCenterX >= hero.characterPosition_X) &&
                        (ballCenterX <= hero.characterPosition_X + 152.0);
            bool hitY = (ballCenterY >= hero.characterPosition_Y) &&
                        (ballCenterY <= hero.characterPosition_Y + 152.0);

            if (hitX && hitY && !fb.hitHero)
            {
                hero.HeroHealth -= 12;
                hero.gettingHit = true;
                if (hero.HeroHealth < 0) hero.HeroHealth = 0;
                fb.hitHero = true;
            }

            // ---- Mini enemies ----
            Enemy* enemies[4] = { &enemy1, &enemy2, &enemy3, &enemy4 };
            for (int e = 0; e < 4; e++)
            {
                if (fb.hitEnemy[e]) continue;

                Enemy &en = *enemies[e];
                if (!en.isActive || en.enemyHealth <= 0) continue;

                double enCenterX = en.enemyPosition_X + (100.0 / 2.0);
                double enCenterY = en.enemyPosition_Y + (100.0 / 2.0);

                bool eHitX = (ballCenterX >= en.enemyPosition_X) &&
                             (ballCenterX <= en.enemyPosition_X + 100.0);
                bool eHitY = (ballCenterY >= en.enemyPosition_Y) &&
                             (ballCenterY <= en.enemyPosition_Y + 100.0);

                if (eHitX && eHitY)
                {
                    en.enemy_takeDamage(2.0);
                    fb.hitEnemy[e] = true;
                }
            }

            // ---- Boss ----
            if (!fb.hitBoss && boss.isActive && boss.bossHealth > 0)
            {
                double boCenterX = boss.bossPosition_X + (200.0 / 2.0);
                double boCenterY = boss.bossPosition_Y + (220.0 / 2.0);

                bool bHitX = (ballCenterX >= boss.bossPosition_X) &&
                             (ballCenterX <= boss.bossPosition_X + 200.0);
                bool bHitY = (ballCenterY >= boss.bossPosition_Y) &&
                             (ballCenterY <= boss.bossPosition_Y + 220.0);

                if (bHitX && bHitY)
                {
                    boss.bosstakeDamage(2.0);
                    fb.hitBoss = true;
                }
            }
        }
    }

    // -------------------------------------------- scroll with background
    void shift(double dx)
    {
        for (int i = 0; i < (int)balls.size(); i++)
            balls[i].x += dx;
    }
};

#endif // FIREBALL_HPP
