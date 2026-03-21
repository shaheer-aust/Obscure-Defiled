#ifndef ENEMY_LVL_2_HPP
#define ENEMY_LVL_2_HPP

// =============================================================================
//  enemy_lvl_2.hpp  –  Sequential wave-based enemy spawner (Level 1 & 2)
//
//  HOW IT WORKS
//  ─────────────────────────────────────────────────────────────────────────
//  Each level defines an ordered list of WaveSlot entries.
//  - Slot 0 activates immediately when the level starts.
//  - When the active enemy's health reaches 0, that enemy is deactivated
//    and the NEXT slot in the list is activated automatically.
//  - Once the last slot is cleared, isLevelComplete() returns true.
//
//  INTEGRATION (do ONCE)
//  ─────────────────────────────────────────────────────────────────────────
//  1.  Add  #include "enemy_functions\enemy_lvl_2.hpp"  in GameScreen.hpp
//  2.  Add  EnemyWaveManager waveManager;  as a GameScreen member
//  3.  In GameScreen::initgame_screen(level)  →  waveManager.init(level);
//      (call it AFTER all initenemy / initboss calls, and after setting
//       enemy1.isActive = false / boss.isActive = false)
//  4.  In GameScreen::resetgame()  →  waveManager.reset();
//      (call it before the end of resetgame, and make sure enemy1.isActive
//       is set to false there so the wave manager activates it itself)
//  5.  In enemy_movement() in iMain.cpp REPLACE the old scattered
//      enemy2Spawned / enemy3Spawned / enemy4Spawned / bossSpawned blocks
//      with ONE call:
//          game_screen.waveManager.update(
//              game_screen.enemy1, game_screen.enemy2,
//              game_screen.enemy3, game_screen.enemy4,
//              game_screen.boss,   game_screen.hero1);
//  6.  In all_50_ms_ticks() you may use  game_screen.waveManager.isLevelComplete()
//      as the win condition instead of checking each enemy health manually.
// =============================================================================

#include "enemy.hpp"
#include "../character_functions/Hero.hpp"

// ---------------------------------------------------------------------------
//  Which enemy-object does a slot address?
// ---------------------------------------------------------------------------
enum class WaveSlotType { ENEMY1, ENEMY2, ENEMY3, ENEMY4, BOSS };

// ---------------------------------------------------------------------------
//  One entry in the wave list
// ---------------------------------------------------------------------------
struct WaveSlot
{
    WaveSlotType type;
    double spawnX;          // X position the entity is placed at when activated
    double spawnY;          // Y position (ground = 100)
    double startHealth;     // full health to restore on spawn
};

// ---------------------------------------------------------------------------
//  EnemyWaveManager
//
//  Owns the wave definition and drives the per-tick spawn logic.
// ---------------------------------------------------------------------------
struct EnemyWaveManager
{
    static const int MAX_SLOTS = 12;

    WaveSlot slots[MAX_SLOTS];
    int      slotCount    = 0;
    int      currentIdx   = 0;     // index of slot waiting to be activated next
    bool     firstActivated = false; // guards the first-slot one-shot activation
    bool     levelComplete  = false;

    // ── public ───────────────────────────────────────────────────────────────

    // Call after initenemy/initboss in initgame_screen(level).
    // Make sure ALL enemy isActive flags are already set to false before calling.
    void init(int level)
    {
        slotCount       = 0;
        currentIdx      = 0;
        firstActivated  = false;
        levelComplete   = false;

        if      (level == 1) buildLevel1Wave();
        else if (level == 2) buildLevel2Wave();
        // else if (level == 3) buildLevel3Wave();
    }

    // Call inside resetgame() so the wave restarts cleanly.
    void reset()
    {
        currentIdx     = 0;
        firstActivated = false;
        levelComplete  = false;
    }

    // Call once per game-loop tick (inside enemy_movement in iMain.cpp).
    void update(Enemy &e1, Enemy &e2, Enemy &e3, Enemy &e4,
                Boss  &boss, Hero  & /*hero*/)
    {
        if (levelComplete || slotCount == 0)
            return;

        // ── activate slot 0 on the very first tick ──────────────────────────
        if (!firstActivated)
        {
            activateSlot(0, e1, e2, e3, e4, boss);
            currentIdx     = 1;
            firstActivated = true;
            return;
        }

        // ── check if the currently-active enemy has just been killed ─────────
        int activeIdx = currentIdx - 1;
        if (activeIdx < 0 || activeIdx >= slotCount)
            return;

        if (!isAlive(activeIdx, e1, e2, e3, e4, boss))
        {
            deactivateSlot(activeIdx, e1, e2, e3, e4, boss);

            if (currentIdx < slotCount)
            {
                activateSlot(currentIdx, e1, e2, e3, e4, boss);
                currentIdx++;
            }
            else
            {
                levelComplete = true;   // all enemies defeated – level done
            }
        }
    }

    bool isLevelComplete() const { return levelComplete; }

    // ── wave definitions ──────────────────────────────────────────────────────
private:

    void addSlot(WaveSlotType t, double x, double y = 100.0, double hp = 100.0)
    {
        if (slotCount >= MAX_SLOTS) return;
        slots[slotCount++] = { t, x, y, hp };
    }

    // =========================================================================
    //  LEVEL 1  –  5 sequential enemies
    //  ─────────────────────────────────────────────────────────────────────────
    //  Wave 1 : enemy1  – fast scout, spawns right edge
    //  Wave 2 : enemy2  – second scout, spawns left edge
    //  Wave 3 : enemy3  – mid-weight, closing from the right
    //  Wave 4 : enemy4  – heavy, bursts in from the left
    //  Wave 5 : boss    – final boss, centre-right of stage
    // =========================================================================
    void buildLevel1Wave()
    {
        addSlot(WaveSlotType::ENEMY1, 1216.0, 100.0, 100.0); // right edge
        addSlot(WaveSlotType::ENEMY2,   64.0, 100.0, 100.0); // left edge
        addSlot(WaveSlotType::ENEMY3, 1100.0, 100.0, 100.0); // right
        addSlot(WaveSlotType::ENEMY4,  -15.0, 100.0, 100.0); // off-screen left
        addSlot(WaveSlotType::BOSS,    900.0, 100.0, 200.0); // boss
    }

    // =========================================================================
    //  LEVEL 2  –  5 sequential enemies
    //  ─────────────────────────────────────────────────────────────────────────
    //  Wave 1 : enemy1  – patrol from the right
    //  Wave 2 : enemy2  – flanks from the left
    //  Wave 3 : enemy4  – heavy, charges off-screen right
    //  Wave 4 : enemy1  – respawns harder (higher health) from the left
    //  Wave 5 : boss    – final boss
    // =========================================================================
    void buildLevel2Wave()
    {
        addSlot(WaveSlotType::ENEMY1, 1216.0, 100.0, 100.0); // right edge
        addSlot(WaveSlotType::ENEMY2,   64.0, 100.0, 100.0); // left edge
        addSlot(WaveSlotType::ENEMY4, 1300.0, 100.0, 100.0); // off-screen right
        addSlot(WaveSlotType::ENEMY1,  -30.0, 100.0, 150.0); // harder respawn left
        addSlot(WaveSlotType::BOSS,    900.0, 100.0, 200.0); // boss
    }

    // ── internal helpers ──────────────────────────────────────────────────────

    void activateSlot(int idx, Enemy &e1, Enemy &e2, Enemy &e3, Enemy &e4, Boss &boss)
    {
        if (idx < 0 || idx >= slotCount) return;
        const WaveSlot &ws = slots[idx];

        switch (ws.type)
        {
        case WaveSlotType::ENEMY1:
            e1.enemyPosition_X = ws.spawnX;
            e1.enemyPosition_Y = ws.spawnY;
            e1.enemyHealth     = ws.startHealth;
            e1.isAttacking     = false;
            e1.enemyGettingHit = false;
            e1.enemy_movement_index = 0;
            e1.isActive        = true;
            break;
        case WaveSlotType::ENEMY2:
            e2.enemyPosition_X = ws.spawnX;
            e2.enemyPosition_Y = ws.spawnY;
            e2.enemyHealth     = ws.startHealth;
            e2.isAttacking     = false;
            e2.enemyGettingHit = false;
            e2.enemy_movement_index = 0;
            e2.isActive        = true;
            break;
        case WaveSlotType::ENEMY3:
            e3.enemyPosition_X = ws.spawnX;
            e3.enemyPosition_Y = ws.spawnY;
            e3.enemyHealth     = ws.startHealth;
            e3.isAttacking     = false;
            e3.enemyGettingHit = false;
            e3.enemy_movement_index = 0;
            e3.isActive        = true;
            break;
        case WaveSlotType::ENEMY4:
            e4.enemyPosition_X = ws.spawnX;
            e4.enemyPosition_Y = ws.spawnY;
            e4.enemyHealth     = ws.startHealth;
            e4.isAttacking     = false;
            e4.enemyGettingHit = false;
            e4.enemy_movement_index = 0;
            e4.isActive        = true;
            break;
        case WaveSlotType::BOSS:
            boss.bossPosition_X = ws.spawnX;
            boss.bossPosition_Y = ws.spawnY;
            boss.bossHealth     = ws.startHealth;
            boss.maxBossHealth  = ws.startHealth;
            boss.isAttacking    = false;
            boss.movement_index = 0;
            boss.isActive       = true;
            break;
        }
    }

    void deactivateSlot(int idx, Enemy &e1, Enemy &e2, Enemy &e3, Enemy &e4, Boss &boss)
    {
        if (idx < 0 || idx >= slotCount) return;
        switch (slots[idx].type)
        {
        case WaveSlotType::ENEMY1: e1.isActive   = false; break;
        case WaveSlotType::ENEMY2: e2.isActive   = false; break;
        case WaveSlotType::ENEMY3: e3.isActive   = false; break;
        case WaveSlotType::ENEMY4: e4.isActive   = false; break;
        case WaveSlotType::BOSS:   boss.isActive = false; break;
        }
    }

    bool isAlive(int idx, const Enemy &e1, const Enemy &e2,
                 const Enemy &e3, const Enemy &e4, const Boss &boss) const
    {
        if (idx < 0 || idx >= slotCount) return false;
        switch (slots[idx].type)
        {
        case WaveSlotType::ENEMY1: return e1.enemyHealth   > 0.0;
        case WaveSlotType::ENEMY2: return e2.enemyHealth   > 0.0;
        case WaveSlotType::ENEMY3: return e3.enemyHealth   > 0.0;
        case WaveSlotType::ENEMY4: return e4.enemyHealth   > 0.0;
        case WaveSlotType::BOSS:   return boss.bossHealth  > 0.0;
        }
        return false;
    }
};

#endif // ENEMY_LVL_2_HPP
