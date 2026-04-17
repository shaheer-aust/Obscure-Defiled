# Obscure Defiled

## Game Description

**Obscure Defiled** is a 2D side-scrolling action-adventure game developed in C++ using the **iGraphics** library. The game features an immersive combat system, multiple challenging levels with unique environmental hazards, diverse enemies, boss battles, and a progressive difficulty curve. Players navigate through a dark and dangerous world, upgrading their abilities through power-ups and collectibles.

## Features

- **Three Progressive Levels** with increasing difficulty and unique environmental themes
- **Dynamic Combat System** with smooth character animations and responsive controls
- **Multiple Enemy Types** including regular enemies and boss encounters
- **Power-Up System** featuring damage boost and speed enhancement abilities
- **Environmental Hazards** including lava, lightning, rain effects, and animated obstacles
- **Health Bar System** for both player and enemies with visual feedback
- **Score System** with time-based scoring and kill counting
- **Player Profile System** with persistent save data (player name, level reached, kills, score)
- **Settings & Options Menu** for audio and gameplay adjustments
- **Immersive Audio** with background music, sound effects for hits, attacks, and deaths
- **Smooth Animations** for character states (idle, run, jump, attack, hit, dead)
- **Interactive UI** with menu navigation and controls screen

## Project Details

| Aspect | Details |
|--------|---------|
| **IDE** | Visual Studio 2013 / 2010 |
| **Language** | C and C++ |
| **Platform** | Windows PC |
| **Genre** | 2D Action-Adventure |
| **Graphics Library** | iGraphics |
| **Screen Resolution** | 1280 x 720 pixels |
| **Build System** | Visual Studio Project (.vcxproj) |

## How to Run the Project

### Prerequisites
- **Visual Studio 2013** or **Visual Studio 2010**
- **iGraphics Library** (included in the repository)
- **MinGW Compiler** (optional, if needed for specific builds)

### Setup & Execution Steps

1. **Clone or Download the Repository**
   - Navigate to the project directory
   
2. **Open in Visual Studio**
   - Open Visual Studio 2013
   - Go to **File → Open → Project/Solution**
   - Select the `.sln` file from the repository
   
3. **Build the Project**
   - Click **Build → Build Solution** (or press Ctrl+Shift+B)
   - Wait for the build to complete successfully
   
4. **Run the Game**
   - Click **Debug → Start Without Debugging** (or press Ctrl+F5)
   - The game window will launch automatically

## How to Play

### Game Screens

| Screen | Purpose |
|--------|---------|
| **Main Menu** | Navigation hub for Play, Settings, Credits, and Quit |
| **Create Account** | Player profile creation screen |
| **Profile** | View/manage your player statistics |
| **Controls** | Learn all keyboard controls |
| **Settings** | Adjust audio and gameplay options |
| **Levels** | Three progressively harder levels |
| **Score Board** | View high scores and player statistics |

### Game Controls

| Action | Keyboard | Alternative |
|--------|----------|-------------|
| **Move Left** | `A` | - |
| **Move Right** | `D` | - |
| **Jump** | `W` | `SPACEBAR` |
| **Attack** | Left Mouse Click (in-game) | - |
| **Use Health Recovery** | `H` | - |
| **Activate Power-Up** | `P` | - |
| **Go Back/Pause** | `ESC` | - |
| **Confirm/Next** | `ENTER` | - |

### Game Rules

1. **Health System**
   - Each player starts with 100 health points
   - Defeat enemies and avoid hazards to progress

2. **Combat Mechanics**
   - Attack enemies to reduce their health
   - Different enemies have varying damage outputs
   - Blocking can reduce incoming damage

3. **Scoring System**
   - Earn points for defeating enemies
   - Time-based score bonuses
   - Multipliers based on consecutive kills

4. **Power-Up Effects**
   - **Damage Boost** (+50% attack damage)
   - **Speed Boost** (+25% movement speed)
   - **Health Recovery** (restores 50 health points)

5. **Enemy Types**
   - **Regular Enemies** (Small enemies with basic AI)
   - **Elite Enemies** (Faster, stronger variants)
   - **Boss Enemies** (Level unique bosses with special attacks)

6. **Environmental Hazards**
   - **Lava Zones** (continuous damage when touched)
   - **Lightning** (sudden strikes, avoid collision)
   - **Rain Effects** (reduces visibility)
   - **Animated Obstacles** (collision damage)

7. **Progression**
   - Level 1: Introduction to game mechanics
   - Level 2: Increased enemy count and obstacle difficulty
   - Level 3: Maximum challenge with alpha boss fight
   - Reach the end of Level 3 to complete the game

8. **Victory Conditions**
   - Defeat all enemies and the level boss
   - Reach the end of the stage without losing all health
   - Unlock the next level progression

## Level Breakdown

### Level 1: The Awakening
- **Environment**: Dark forest with clouds
- **Enemies**: 2-4 regular enemies + Boss
- **Hazards**: Animated obstacles, basic traps
- **Boss**: Level 1 Boss Enemy
- **Objective**: Survive and defeat the boss

### Level 2: The Descent
- **Environment**: Industrial area with traps and lava
- **Enemies**: 3-4 elite enemies + Boss
- **Hazards**: Moving traps, lava pools
- **Boss**: Level 2 Boss Enemy
- **Special Mechanics**: Power-up collection system
- **Objective**: Navigate hazards and defeat the boss

### Level 3: The Final Stand
- **Environment**: Corrupted realm with lightning and rain
- **Enemies**: 4-5 elite enemies + Alpha Boss
- **Hazards**: Lightning strikes, rain effects, lava, obstacles
- **Boss**: Alpha Boss (Final Challenge)
- **Special Mechanics**: Enhanced power-ups and special abilities
- **Objective**: Defeat the alpha boss and save the world

## Project Structure

```
Obscure Defiled/
├── iMain.cpp                          # Main game entry point
├── iGraphics.h                        # Graphics library header
├── character_functions/
│   └── Hero.hpp                       # Player character class
├── enemy_functions/
│   └── enemy.hpp                      # Enemy classes and AI
├── Screens/
│   ├── menu_screen.hpp               # Main menu implementation
│   ├── GameScreen.hpp                # Main gameplay screen
│   ├── game_over_screen.hpp          # Game over screen
│   ├── controls_screen.hpp           # Controls display
│   ├── setting_screen.hpp            # Settings menu
│   ├── after_lvl_1_screen.hpp       # Level 1 completion screen
│   ├── after_lvl_2_screen.hpp       # Level 2 completion screen
│   └── ...                           # Additional screen files
├── level_handler.hpp                 # Level management and progression
├── power.hpp                         # Power-up system
├── trap.hpp                          # Trap mechanics
├── lava.hpp                          # Lava hazard system
├── lightning.hpp                     # Lightning effects
├── rain.hpp                          # Rain particle system
├── cloud.hpp & cloud2.hpp           # Cloud effects
├── fireball.hpp                      # Fireball projectiles
├── icon.hpp                          # UI icons
├── resources/                        # Game assets
│   ├── audio/                       # Sound effects and music
│   ├── game_screen/                 # Level backgrounds
│   ├── Main_Character/              # Player sprites
│   ├── Enemy/                       # Enemy sprites
│   ├── menu_screen/                 # Menu assets
│   ├── Health Bar/                  # Health bar graphics
│   └── ...                          # Additional asset folders
└── player.txt                        # Player profile save file
```

## Game Features in Detail

### Character System
- **Smooth Animations**: Idle, running, jumping, attacking, taking damage, death
- **Combat Mechanics**: Direct melee attacks with damage calculation
- **Movement**: Horizontal movement with gravity-based jumping
- **Health Management**: Real-time health display and damage feedback

### Enemy AI
- **Pathfinding**: Enemies pursue the player intelligently
- **Attack Patterns**: Varied attack strategies based on enemy type
- **Health System**: Each enemy has individual health points
- **Collision Detection**: Accurate hit detection for attacks and damage

### Audio System
- **Background Music**: Level-specific background tracks
- **Sound Effects**: 
  - Attack sounds (knife, pistol)
  - Hit and damage noises
  - Enemy death sounds
  - Menu button interactions

### UI/UX
- **Health Display**: Visual health bars for player and enemies
- **Score Display**: Real-time score tracking
- **Enemy Counter**: Shows active enemies on screen
- **Time Counter**: Displays elapsed time in level
- **Menu System**: Intuitive navigation with visual feedback

## Compilation Notes

- The project uses DirectX/Windows-specific audio libraries (`mmsystem.h`)
- Ensure all resource paths are relative and correctly configured
- The iGraphics library must be linked during compilation
- Audio playback uses Windows Media Command Interface (MCI)

## Performance Optimization

- Sprite batching for efficient rendering
- Enemy spawning based on progression
- Optimized collision detection algorithms
- Frame-rate independent movement calculations
- Efficient memory management for animations

## Known Limitations

- Windows PC only (platform-specific audio and graphics)
- Requires Visual Studio 2010 or later
- Resolution locked at 1280x720 pixels
- Single-player gameplay only

## Troubleshooting

| Issue | Solution |
|-------|----------|
| Game won't start | Ensure Visual Studio build tools are installed, check all dependencies |
| Audio not playing | Verify Windows Media Player is installed and audio files exist in resources folder |
| Graphics not rendering | Update graphics drivers, ensure iGraphics library is properly linked |
| Game crashes on level load | Check resource file paths are correctly configured, verify all asset files exist |
| Controls unresponsive | Ensure the game window is in focus, check keyboard input handler is active |

## Project Contributors

Example:
```
Team Members:
- Sheikh Zubayer Kabir — Developed core gameplay systems including hero weapons, projectiles, boss mechanics, and level transitions with environmental elements.

- Rahul Podder — Designed environment effects, assets, and power-up systems while contributing to level visuals and gameplay improvements.

- Mahammad Shaheer Imam — Built GameScreen architecture, UI features, and implemented gameplay mechanics like enemies, obstacles, health, projectiles, and bug fixes.
```

## Technical Implementation

### Game Loop
- **Initialization**: Load resources and game state
- **Update**: Process input, update game logic
- **Render**: Draw all game elements to screen
- **Loop**: Repeat at 60 FPS

### Memory Management
- Dynamic vector-based sprite storage
- Efficient resource pooling for GUI elements
- Proper cleanup on level transitions

### Code Architecture
- Header-only implementation for most game systems
- Struct-based entity system for characters and enemies
- Modular screen system for UI management
- Stack-based screen navigation

## Development Environment

The project is configured for development in Visual Studio with the following setup:
- C++ standard library usage
- STL containers (vector, stack, string)
- Windows-specific APIs for audio
- OpenGL via iGraphics wrapper

## Future Enhancement Possibilities

- [ ] Multiplayer cooperative gameplay
- [ ] Additional levels and difficulty modes
- [ ] More diverse enemy types
- [ ] Advanced weapon system
- [ ] Achievement/badge system
- [ ] Custom difficulty settings
- [ ] Leaderboard system
- [ ] Mobile platform ports

## Installation & Resources

**GitHub Repository**: [Obscure-Defiled](https://github.com/shaheer-aust/Obscure-Defiled)

**Resources Required**:
- Visual Studio 2013 (or compatible version)
- iGraphics library (included)
- Windows OS (XP or newer)
- 100 MB free disk space (including assets)

## YouTube Gameplay

https://youtu.be/G9lf9bwOPps?si=swqRY7FBrrb9LD-g

## Project Report

https://docs.google.com/document/d/1N86ZTuzzUBsmdKiKu7gcNbKR2HKFLb9R/edit?usp=sharing&ouid=117345656574837460376&rtpof=true&sd=true


## License

This project was developed as part of CSE 1200: Software Development - I course.

---

**Last Updated**: April 2026  
**Version**: 3.O (Final Release)
