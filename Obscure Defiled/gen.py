import sys

with open("iMain.cpp", "r") as f:
    lines = f.readlines()

def get_lines(start, end):
    return "".join(lines[start-1:end])

def duplicate_and_replace(code, func_suffix, old_var, new_var):
    # Rename functions
    code = code.replace("void character_movement()", f"void character_movement_{func_suffix}()")
    code = code.replace("void enemy_movement()", f"void enemy_movement_{func_suffix}()")
    code = code.replace("void update_attack_animation()", f"void update_attack_animation_{func_suffix}()")
    code = code.replace("void hero_hit_loop()", f"void hero_hit_loop_{func_suffix}()")
    code = code.replace("void character_idle_animation()", f"void character_idle_animation_{func_suffix}()")
    # Replace variable
    code = code.replace(old_var, new_var)
    # Also replace level_1_screen string in enemy_movement
    code = code.replace('"level_1_screen"', '"level_2_screen"')
    return code

movement_code = get_lines(352, 470)
idle_code = get_lines(497, 503)

new_movement_code = duplicate_and_replace(movement_code, "2", "level_1_screen", "level_2_screen")
new_idle_code = duplicate_and_replace(idle_code, "2", "level_1_screen", "level_2_screen")

all_50_ms = """void all_50_ms_ticks(){
	if (screens.top() == "level_1_screen")
	{
		if (level_1_screen.hero1.isDead){
			screens.pop();
			screens.push("gameOver");
		}
		// --- ADD YOUR LEVEL TRANSITION CONDITION HERE ---
		else if (level_1_screen.enemy1.enemyHealth == 0 && level_1_screen.enemy2.enemyHealth == 0 && level_1_screen.boss.bossHealth == 00)
		{
			// Note: Replace `.isDead` with however you actually track their deaths
			// e.g., `.enemyHealth <= 0`, `!isActive`, etc.

			screens.pop();                 // Remove level_1_screen
			screens.push("level_2_screen");  // Push level 2 (it will be under the intro screen)
			screens.push("After_lvl_1");     // Push intro screen on top
		}
		// ------------------------------------------------

		character_movement();
		enemy_movement();
		update_attack_animation();
		hero_hit_loop();
	}
	else if (screens.top() == "level_2_screen")
	{
		if (level_2_screen.hero1.isDead){
			screens.pop();
			screens.push("gameOver");
		}

		character_movement_2();
		enemy_movement_2();
		update_attack_animation_2();
		hero_hit_loop_2();
	}
}
"""

replacement = movement_code + new_movement_code + all_50_ms + idle_code + new_idle_code

with open("repl.txt", "w") as f:
    f.write(replacement)
