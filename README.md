# Tumble Pop Game 
**Authors:** M.Wajahat Jamshed and Izaan Ahmad
## Project Overview
This project is a 2D arcade-style platformer game inspired by the classic Tumble Pop.  
It uses **SFML** for rendering graphics, handling input, and managing textures, while the core gameplay mechanics are written in **C++**.  

The game features:
- Character movement
- Enemies
- Vacuum-based capturing mechanics
- Shooting
- Power-ups
- Multi-level progression  

It demonstrates real-time game loop programming and modular function-based design.

---

## Project Objectives
- Apply programming fundamentals to build a functional 2D game using C++.  
- Implement gameplay mechanics such as physics, collision detection, and enemy behavior.  
- Enhance problem-solving and game logic skills.

---

## Key Features

### Player Mechanics
- Move horizontally and jump across platforms.  
- Gravity affects the player for realistic physics.  
- Sprite flips direction when moving left or right for natural movement.

### Vacuum Capture System
- Pulls enemies inward when they enter the suction range.  
- Captured enemies are stored in the player's "bag" and can be shot as projectiles.

### Shooting System
- Each captured enemy produces a unique bullet sprite.  
- Adds variety to combat mechanics and visual feedback.

### Enemy Behavior
- Different enemy types with unique movement patterns and difficulty levels.  
- Some enemies (like Chelnov) shoot fireballs, increasing challenge.

### Level Design
- Multiple hand-designed tile-based levels.  
- Blocks, slanted platforms, enemy positions, and power-ups gradually increase difficulty.

### Power-ups
- Temporary or immediate benefits such as increased speed, extended suction range, extra lives, or additional score.

### Additional Features
- Title screen, character selection menu, level transitions, game over screen  
- Proper scoring and life system for a polished gameplay experience

---

## Technologies & Tools Used
- **Programming Language:** C++  
- **Graphics Library:** SFML (textures, sprites, fonts, sound, keyboard events, window management)  
- **Development Environment:** VS Code on Ubuntu  
- **Assets:** PNG, JPG, and sprite sheets for characters, enemies, projectiles, and backgrounds

---

## Game Workflow
1. The game starts at a **title screen** displaying background artwork.  
2. Player enters a **character selection screen** and chooses a character.  
3. **Level 1** begins; enemies roam and the player must capture them using the vacuum.  
4. After defeating all enemies, the game transitions to **Level 2**, increasing difficulty.  
5. If all lives are lost, the **Game Over screen** appears.  
6. Successfully clearing Level 2 completes the game.

---

## User Interface Design
- HUD displays important player data: lives, score, and active power-ups.  
- Title screen and character selection use centered artwork.  
- In-game HUD positioned at the top for clarity without blocking gameplay.

---

## Development Process
1. **Concept & Planning:** Sketch gameplay elements, character controls, level layout, and enemy behavior.  
2. **Player Movement & Physics:** Implement horizontal movement, jumping, gravity, and collision detection.  
3. **Enemy Implementation:** Add multiple enemy types with different movement styles; some shoot fireballs.  
4. **Vacuum Capture Mechanic:** Design suction range, gradual pulling, bagging, and conversion into projectiles.  
5. **Level Building:** Create tile-based maps using 2D arrays, including normal and slanted platforms.  
6. **Systems & Screens:** Implement scoring, lives, power-ups, title screen, character selection, level transitions, and game over handling.  
7. **Testing & Debugging:** Fix collision, gravity, enemy movement, and shooting issues for smooth gameplay.

---

## Testing & Evaluation
- Tested multiple scenarios, including edge cases: out-of-range suction, enemies stuck on blocks, and player-fireball interactions.  
- Confirmed stable frame rates, correct animation behavior, proper collision detection, and consistent logic flow across levels.

---

## Future Enhancements
- More levels with new mechanics  
- Boss battles with unique attack patterns  
- Background music per level  
- Improved animations and particle effects  
- Multiplayer compatibility  
- Save system for storing high scores

---

## Conclusion
This project successfully demonstrates the use of **C++ and SFML** to create a working 2D game with:
- Real-time mechanics  
- Enemy AI  
- Level progression  
- Smooth user interaction  

It strengthens core programming skills and provides a solid foundation in game development.

---
