

#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

//FUNCTION DECLERATIONS(Prototypes)

void display_level(RenderWindow& window, char** lvl, Texture& bgTex, Sprite& bgSprite, Texture& blockTexture, Sprite& blockSprite, const int height, const int width, const int cell_size);
void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth, int screen_x, int screen_y);
void GhostMovement(char** lvl, float ghost_x[], float ghost_y[], float ghostV_x[], Sprite GhostSprite[], int numGhosts, int cell_size, int width, int height, bool enemy_active[], int ghost_start_index);
void SkeletonMovement(char** lvl, float skeleton_x[], float skeleton_y[], float skeletonV_x[], Sprite SkeletonSprite[], int numSkeletons, int cell_size, int width, int height, bool enemy_active[], int skeleton_start_index);
void vacuum_pull_enemies(bool vacuum_active, int& enemies_in_bag, int max_bag_capacity,float player_x, float player_y, int PlayerWidth, int PlayerHeight, bool facingRight, int vacuum_range, int cell_size, float ghost_x[], float ghost_y[], int num_ghosts, int ghost_start_index, float skeleton_x[], float skeleton_y[], int num_skeletons, int skeleton_start_index, float chelnov_x[], float chelnov_y[], int num_chelnov, int chelnov_start_index, bool enemy_active[], int bagged_enemies[], char bagged_enemy_types[],int& playerScore);
bool collision_with_enemy(float player_x, float player_y, int PlayerWidth, int PlayerHeight, float ghost_x[], float ghost_y[], int num_ghosts, int ghost_start_index, float skeleton_x[], float skeleton_y[], int num_skeletons, int skeleton_start_index, float chelnov_x[], float chelnov_y[], int num_chelnov, int chelnov_start_index, float invisibleman_x[], float invisibleman_y[], int num_invisibleman, int invisibleman_start_index, bool enemy_active[]);
bool collision_with_fireball(float player_x, float player_y, int PlayerWidth, int PlayerHeight, float fireball_x[], float fireball_y[], bool fireball_active[], int num_fireballs);
void shoot_enemy(float player_x, float player_y, int PlayerWidth, int PlayerHeight, bool facingRight,
                 int& enemies_in_bag, int bagged_enemies[], char bagged_enemy_types[],
                 float shot_x[], float shot_y[], float shot_speed[], bool shot_active[], char shot_type[],
                 Sprite ghostShotSprite[], Sprite skeletonShotSprite[], Sprite chelnovShotSprite[],Sprite InvisibleManShotSprite[],
                 int max_shots);
void update_shots(RenderWindow& window,
                  float shot_x[], float shot_y[], float shot_speed[],
                  bool shot_active[], char shot_type[],
                  Sprite ghostShotSprite[], Sprite skeletonShotSprite[], Sprite chelnovShotSprite[],
                  int max_shots);
bool collision_with_powerup(float player_x, float player_y, int PlayerWidth, int PlayerHeight, float powerup_x, float powerup_y, float powerup_width, float powerup_height);
bool check_level_complete(bool enemy_active[], int total_enemies);
void setup_level_1(char** lvl, int height, int width, float ghost_x[], float ghost_y[], float ghostV_x[], float skeleton_x[], float skeleton_y[], float skeletonV_x[], Sprite GhostSprite[], Sprite SkeletonSprite[], Texture& GhostTexture, Texture& SkeletonTexture, bool enemy_active[], int total_enemies);
void setup_level_2(char** lvl, int height, int width, float ghost_x[], float ghost_y[], float ghostV_x[], float skeleton_x[], float skeleton_y[], float skeletonV_x[], Sprite GhostSprite[], Sprite SkeletonSprite[], Texture& GhostTexture, Texture& SkeletonTexture, bool enemy_active[], int total_enemies, float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[], Sprite ChelnovSprite[], Texture& ChelnovTexture, int num_chelnov, float fireball_x[], float fireball_y[], float fireball_vx[], bool fireball_active[], Sprite FireballSprite[], Texture& FireballTexture, int num_fireballs, int fireballs_cooldown[], float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[], Sprite InvisibleManSprite[], Texture& InvisibleManTexture, int num_invisibleman);
void create_slant_platform(char** lvl, int height, int width, bool direction);
void mechanism_chelnov_and_fireballs(float chelnov_x[], float chelnov_y[], bool chelnov_facing_right[], int num_chelnov, float fireball_x[], float fireball_y[], float fireball_vx[], bool fireball_active[], Sprite FireballSprite[], int fireballs_cooldown[], int fire_rate, int num_fireballs, int screen_x);
void ChelnovMovement(char** lvl, float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[], Sprite ChelnovSprite[], int num_chelnov, int cell_size, int width, int height, bool enemy_active[], int chelnov_start_index);
void ChelnovGravity(char** lvl, float chelnov_x[], float chelnov_y[], Sprite ChelnovSprite[], int num_chelnov, int cell_size, int width, int height, bool enemy_active[], int chelnov_start_index);
void InvisibleManMovement(char** lvl, float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[], Sprite InvisibleManSprite[], int num_invisibleman, int cell_size, int width, int height, bool enemy_active[], int invisibleman_start_index);
void Sprites_Textures(Texture& char1Tex, Texture& char2Tex, Texture& menuBgTex, Sprite& Player1Sprite, Sprite& Player2Sprite, Sprite& menuBgSprite, Texture& vacuumTex, Sprite& vacuumSprite, Texture& tsTex, Sprite& tsSprite, Texture& level2ScreenTex, Sprite& level2ScreenSprite, Texture& GhostTexture, Sprite GhostSprite[], Texture& SkeletonTexture, Sprite SkeletonSprite[], Texture& ChelnovTexture, Sprite ChelnovSprite[], Texture& FireballTexture, Sprite FireballSprite[], Texture& InvisibleManTexture, Sprite InvisibleManSprite[], Texture& bgTex, Sprite& bgSprite, Texture& blockTexture, Sprite& blockSprite, Texture& ppuTex, Sprite& ppuSprite, Texture& rpuTex, Sprite& rpuSprite, Texture& elpuTex, Sprite& elpuSprite, Texture& spuTex, Sprite& spuSprite, Texture& ghostShotTexture, Sprite ghostShotSprite[], Texture& skeletonShotTexture, Sprite skeletonShotSprite[], Texture& chelnovShotTexture, Sprite chelnovShotSprite[],  Texture& InvisibleManShotTexture, Sprite InvisibleManShotSprite[], int screen_x, int screen_y, int ppu_x, int ppu_y, int rpu_x, int rpu_y, int elpu_x, int elpu_y, int spu_x, int spu_y);
void handleTitleScreen(RenderWindow& window, Sprite& tsSprite, bool& TitleScreenOn, bool& CharacterSelectOn);
void handleCharacterSelect(RenderWindow& window, Sprite& menuBgSprite, Sprite& Player1Sprite, Sprite& Player2Sprite, bool& CharacterSelectOn, bool& GameOn, int& chosenPlayer, Sprite*& chosenCharacter, float& Speed, int& vacuum_range, float player1speed, float player2speed, int player1range, int player2range);
void handlePlayerInput(Sprite& chosenCharacter, float& player_x, float& player_y, float& velocityY, bool& onGround, float Speed, bool& facingRight, float jumpStrength, int PlayerHeight, int cell_size, int screen_y);
void handlePowerups(float player_x, float player_y, int PlayerWidth, int PlayerHeight, bool& ppu_active, bool& rpu_active, bool& elpu_active, bool& spu_active, int ppu_x, int ppu_y, int rpu_x, int rpu_y, int elpu_x, int elpu_y, int spu_x, int spu_y, Sprite& ppuSprite, Sprite& rpuSprite, Sprite& elpuSprite, Sprite& spuSprite, float& Speed, int& playerLives, int& vacuum_range, int& playerScore);
void handleCollisions(float player_x, float player_y, int PlayerWidth, int PlayerHeight, float ghost_x[], float ghost_y[], float skeleton_x[], float skeleton_y[], float chelnov_x[], float chelnov_y[], float invisibleman_x[], float invisibleman_y[], float fireball_x[], float fireball_y[], bool fireball_active[], bool enemy_active[], bool& Collision, int& playerLives, int& rTimer, bool vacuum_active, int currentLevel, int num_chelnov, int num_invisibleman, int num_fireballs, int ghost_start_index, int skeleton_start_index, int chelnov_start_index, int invisibleman_start_index, int& playerScore, Sound& collisionSound);
void resetLevel1(float ghost_x[], float ghost_y[], float ghostV_x[], float skeleton_x[], float skeleton_y[], float skeletonV_x[], Sprite GhostSprite[], Sprite SkeletonSprite[], Texture& GhostTexture, Texture& SkeletonTexture);
void resetLevel2(float ghost_x[], float ghost_y[], float ghostV_x[], float skeleton_x[], float skeleton_y[], float skeletonV_x[], Sprite GhostSprite[], Sprite SkeletonSprite[], Texture& GhostTexture, Texture& SkeletonTexture, float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[], Sprite ChelnovSprite[], Texture& ChelnovTexture, int num_chelnov, float fireball_x[], float fireball_y[], float fireball_vx[], bool fireball_active[], Sprite FireballSprite[], Texture& FireballTexture, int num_fireballs, int fireballs_cooldown[], float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[], Sprite InvisibleManSprite[], Texture& InvisibleManTexture, int num_invisibleman);
void handleGameOver(bool& GameOn, bool& TitleScreenOn, int& currentLevel, bool& levelComplete, Music& lvl2Music, Music& lvlMusic, int& playerLives, float& player_x, float& player_y, float& velocityY, int& enemies_in_bag, bool enemy_active[], int total_enemies, float ghost_x[], float ghost_y[], float ghostV_x[], float skeleton_x[], float skeleton_y[], float skeletonV_x[], Sprite GhostSprite[], Sprite SkeletonSprite[], Texture& GhostTexture, Texture& SkeletonTexture, float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[], Sprite ChelnovSprite[], Texture& ChelnovTexture, int num_chelnov, float fireball_x[], float fireball_y[], float fireball_vx[], bool fireball_active[], Sprite FireballSprite[], Texture& FireballTexture, int num_fireballs, int fireballs_cooldown[], float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[], Sprite InvisibleManSprite[], Texture& InvisibleManTexture, int num_invisibleman, int& playerScore);
void handleLevelTransition(bool& levelComplete, Clock& levelCompleteTimer, int& currentLevel, bool& GameOn, bool& showLevelScreen, bool& TitleScreenOn, Music& lvlMusic, Music& lvl2Music, char** lvl, int height, int width, float ghost_x[], float ghost_y[], float ghostV_x[], float skeleton_x[], float skeleton_y[], float skeletonV_x[], Sprite GhostSprite[], Sprite SkeletonSprite[], Texture& GhostTexture, Texture& SkeletonTexture, bool enemy_active[], int total_enemies, float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[], Sprite ChelnovSprite[], Texture& ChelnovTexture, int num_chelnov, float fireball_x[], float fireball_y[], float fireball_vx[], bool fireball_active[], Sprite FireballSprite[], Texture& FireballTexture, int num_fireballs, int fireballs_cooldown[], float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[], Sprite InvisibleManSprite[], Texture& InvisibleManTexture, int num_invisibleman, float& player_x, float& player_y, float& velocityY, int& enemies_in_bag, int& playerLives,int total_enemies_level1, int total_enemies_level2);
void renderGame(RenderWindow& window, char** lvl, Texture& bgTex, Sprite& bgSprite, Texture& blockTexture, Sprite& blockSprite, int height, int width, int cell_size, Sprite& chosenCharacter, Sprite& vacuumSprite, bool vacuum_active, float player_x, float player_y, int PlayerWidth, int PlayerHeight, bool facingRight, Texture& vacuumTex, Sprite GhostSprite[], Sprite SkeletonSprite[],Sprite ghostShotSprite[], Sprite skeletonShotSprite[],Sprite ChelnovSprite[],Sprite InvisibleManShotSprite[],Sprite chelnovShotSprite[], Sprite FireballSprite[], Sprite InvisibleManSprite[], Sprite& ppuSprite, Sprite& rpuSprite, Sprite& elpuSprite, Sprite& spuSprite, bool enemy_active[], bool fireball_active[], int currentLevel, int ghost_start_index, int skeleton_start_index, int chelnov_start_index, int num_chelnov, int num_fireballs, int invisibleman_start_index, int num_invisibleman,bool shot_active[],int max_shots, char shot_type[]);
void create_slant_platform(char** lvl, int height, int width, bool direction);

//Functions

void display_level(RenderWindow& window, char** lvl, Texture& bgTex, Sprite& bgSprite, Texture& blockTexture, Sprite& blockSprite, const int height, const int width, const int cell_size)
{
    window.draw(bgSprite);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (lvl[i][j] == '#')
            {
                blockSprite.setPosition(j * cell_size, i * cell_size);
                window.draw(blockSprite);
            }
        }
    }
}

void player_gravity(char** lvl, float& offset_y, float& velocityY, bool& onGround, const float& gravity, float& terminal_Velocity, float& player_x, float& player_y, const int cell_size, int& Pheight, int& Pwidth, int screen_x, int screen_y)
{
    offset_y = player_y;
    offset_y += velocityY;

    char bottom_left_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x) / cell_size];
    char bottom_right_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth) / cell_size];
    char bottom_mid_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth / 2) / cell_size];

    if ((bottom_left_down == '#' || bottom_mid_down == '#' || bottom_right_down == '#') && velocityY >= 0)
    {
        onGround = true;
    }
    else
    {
        player_y = offset_y;
        onGround = false;
    }

    if (!onGround)
    {
        velocityY += gravity;
        if (velocityY >= terminal_Velocity) velocityY = terminal_Velocity;
    }
    else
    {
        velocityY = 0;
    }

    if (player_x < 0) player_x = 0;
    if (player_x + Pwidth > screen_x) player_x = screen_x - Pwidth;
    if (player_y < 0)
    {
        player_y = 0;
        if (velocityY < 0) velocityY = 0;
    }
    if (player_y + Pheight > screen_y)
    {
        player_y = screen_y - Pheight;
        onGround = true;
        if (velocityY < 0) velocityY = 0;
    }
}
// Ensures that the Ghosts move on the platform directly below them
void GhostMovement(char** lvl, float ghost_x[], float ghost_y[], float ghostV_x[], Sprite GhostSprite[], int numGhosts, int cell_size, int width, int height, bool enemy_active[], int ghost_start_index) {
    int Ghost_Width = 52, Ghost_Height=31;
    for (int i = 0; i < numGhosts; i++) {
        int enemy_index = ghost_start_index + i;
        if (!enemy_active[enemy_index]) continue;
        
        ghost_x[i]= ghost_x[i]+ ghostV_x[i];

        int middleCol= static_cast<int>(ghost_x[i] + Ghost_Width/2) / cell_size;

        int startingRow = static_cast<int>(ghost_y[i] + Ghost_Height) / cell_size;
        int endingRow = startingRow + 2;

        for (int row = startingRow; row <= endingRow; row++) {
            if (lvl[row][middleCol] == '#') {
                ghost_y[i] = row * cell_size - 90;
                break;
            }
        }

        int frontX = (ghostV_x[i] > 0) ? static_cast<int>(ghost_x[i] + 52) / cell_size : static_cast<int>(ghost_x[i] - 1) / cell_size;
        int downY = static_cast<int>(ghost_y[i] + 90) / cell_size; // +90 because it has to hover, 90 because of hit and trial

        if (frontX < 0 || frontX >= width || lvl[downY][frontX] != '#') {
            ghostV_x[i] = -ghostV_x[i];
        }

        GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
    }
}
// Ensures that the Skeletons moves on the platforms directly below them
void SkeletonMovement(char** lvl, float skeleton_x[], float skeleton_y[], float skeletonV_x[], Sprite SkeletonSprite[], int numSkeletons, int cell_size, int width, int height, bool enemy_active[], int skeleton_start_index) {
    int Skeleton_Width= 32, Skeleton_Height=38;
    for (int i = 0; i < numSkeletons; i++) {
        int enemy_index = skeleton_start_index + i;
        if (!enemy_active[enemy_index]) 
        continue;
        
        skeleton_x[i] = skeleton_x[i] + skeletonV_x[i];

        int Middle_Col = static_cast<int>(skeleton_x[i] + Skeleton_Width/2) / cell_size;

        int startRow = static_cast<int>(skeleton_y[i] + 14) / cell_size; 
        int endRow = startRow + 2;

        for (int row = startRow; row <= endRow; row++) {
            if (lvl[row][Middle_Col] == '#') {
                skeleton_y[i] = row * cell_size - 114;
                break;
            }
        }

        int frontX = (skeletonV_x[i] > 0) ? static_cast<int>(skeleton_x[i] + 96) / cell_size : static_cast<int>(skeleton_x[i] - 1) / cell_size;
        int footY = static_cast<int>(skeleton_y[i] + 114) / cell_size;

        if (frontX < 0 || frontX >= width || lvl[footY][frontX] != '#') {
            skeletonV_x[i] = -skeletonV_x[i];
        }

        SkeletonSprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
    }
}
// Function for the vacuum suction mechanism
void vacuum_pull_enemies(bool vacuum_active, int& enemies_in_bag, int max_bag_capacity,
                        float player_x, float player_y, int PlayerWidth, int PlayerHeight,
                        bool facingRight, int vacuum_range, int cell_size,
                        float ghost_x[], float ghost_y[], int num_ghosts, int ghost_start_index,
                        float skeleton_x[], float skeleton_y[], int num_skeletons, int skeleton_start_index,
                        float chelnov_x[], float chelnov_y[], int num_chelnov, int chelnov_start_index,
                        bool enemy_active[], int bagged_enemies[], char bagged_enemy_types[],
                        int& playerScore) {
    
    if (!vacuum_active || enemies_in_bag >= max_bag_capacity) return;
    
    float vacuum_center_x = facingRight ? player_x + PlayerWidth : player_x;
    int player_platform_row = static_cast<int>(player_y + PlayerHeight) / cell_size;
    float pull_speed = 5.0f;
    
    // Process for pulling Ghosts
    for (int i = 0; i < num_ghosts && enemies_in_bag < max_bag_capacity; i++) {
        int enemy_index = ghost_start_index + i;
        if (!enemy_active[enemy_index])
        continue;
        
        float enemy_center_x = ghost_x[i]/cell_size;
             int enemy_platform_row = static_cast<int>(ghost_y[i] + PlayerHeight) / cell_size;
        
        if (enemy_platform_row != player_platform_row) 
        continue;
        
        float displacement = enemy_center_x - vacuum_center_x; // distance between enemy and the vacuum
        bool in_front = facingRight ? (displacement > 0) : (displacement< 0);
        int distance;
        if(displacement<0){
            distance = displacement;
        }
        else{
            distance = displacement;
        }
        if (distance <= vacuum_range && in_front) {
             // Pull enemy toward vacuum
            if (facingRight) {
            ghost_x[i] -= pull_speed; // As enemey is toward the right of plyer so, pull left (toward player)
        } else {
        ghost_x[i] += pull_speed; // Here enemy is on the left of the player so, Pull right (toward player)
        }
            // Bag enemy when close enough
            int remove = -1; // when enemy captured its removed from the screen as the coordinates of screen are (0,0)
            if (distance < 48.0f) {
                enemy_active[enemy_index] = false; // that enemy not processed anymore
                ghost_x[i] = remove; 
                ghost_y[i] = remove;
                bagged_enemies[enemies_in_bag] = enemy_index; // add the bagged enemies in a new array
                bagged_enemy_types[enemies_in_bag] = 'G';
                enemies_in_bag++;
                playerScore+=50;
            }
        }
    }
    
    // Process for pulling Skeletons
    for (int i = 0; i < num_skeletons && enemies_in_bag < max_bag_capacity; i++) {
        int enemy_index = skeleton_start_index + i;
        if (!enemy_active[enemy_index]) continue;
        
        float enemy_center_x = skeleton_x[i] + 48.0f;
        int enemy_platform_row = static_cast<int>(skeleton_y[i] + 102) / cell_size;
        
        if (enemy_platform_row != player_platform_row) continue;
        
        float displacement = enemy_center_x - vacuum_center_x;
        bool in_front = facingRight ? (displacement> 0) : (displacement < 0);
        int distance;
        if(displacement<0){
            distance = displacement;
        }
        else{
            distance = displacement;
        }
        if (distance <= vacuum_range && in_front) {
             if (facingRight) {
            skeleton_x[i] -= pull_speed;
        } else {
        skeleton_x[i] += pull_speed;
        }
            
            if (distance < 30.0f) {
                enemy_active[enemy_index] = false;
                skeleton_x[i] = -1;
                skeleton_y[i] = -1;
                bagged_enemies[enemies_in_bag] = enemy_index;
                bagged_enemy_types[enemies_in_bag] = 'S';
                enemies_in_bag++;
                playerScore+= 75;
            }
        }
    }
    // Process for pulling chelnoves
 for (int i = 0; i < num_chelnov && enemies_in_bag < max_bag_capacity; i++) {
        int enemy_index = chelnov_start_index + i;
        if (!enemy_active[enemy_index]) continue;
        
        float enemy_center_x = chelnov_x[i] + 48.0f;
        int enemy_platform_row = static_cast<int>(chelnov_y[i] + 102) / cell_size;
        
        if (enemy_platform_row != player_platform_row) continue;
        
        float displacement = enemy_center_x - vacuum_center_x;
        bool in_front = facingRight ? (displacement> 0) : (displacement < 0);
        int distance;
        if(displacement<0){
            distance = displacement;
        }
        else{
            distance = displacement;
        }
        if (distance <= vacuum_range && in_front) {
             if (facingRight) {
            chelnov_x[i] -= pull_speed;
        } else {
        chelnov_x[i] += pull_speed;
        }
            
            if (distance < 30.0f) {
                enemy_active[enemy_index] = false;
                chelnov_x[i] = -1;
                chelnov_y[i] = -1;
                bagged_enemies[enemies_in_bag] = enemy_index;
                bagged_enemy_types[enemies_in_bag] = 'C';
                enemies_in_bag++;
                playerScore+=200;
            }
        }
    }
}

bool collision_with_enemy(float player_x, float player_y, int PlayerWidth, int PlayerHeight,
                           float ghost_x[], float ghost_y[], int num_ghosts, int ghost_start_index,
                           float skeleton_x[], float skeleton_y[], int num_skeletons, int skeleton_start_index,
                           float chelnov_x[], float chelnov_y[],int num_chelnov, int chelnov_start_index,
                           float invisibleman_x[], float invisibleman_y[],int num_invisibleman, int invisibleman_start_index,bool enemy_active[]) {
    // here we are checking collision with ghosts
    for (int i = 0; i < num_ghosts; i++) {
        int enemy_index = ghost_start_index + i;
        if (!enemy_active[enemy_index])
        continue;
        
        float ghost_width = 52;
        float ghost_height = 31;
        
        if (player_x < ghost_x[i] + ghost_width && player_x + PlayerWidth > ghost_x[i] && player_y < ghost_y[i] + ghost_height && player_y + PlayerHeight > ghost_y[i]) {
            return true;
        }
    }
    // here we are checking collision with the skeletons
    for (int i = 0; i < num_skeletons; i++) {
        int enemy_index = skeleton_start_index + i;
        if (!enemy_active[enemy_index])
         continue;
        
        float skeleton_width = 32;
        float skeleton_height = 38;
        
        if (player_x < skeleton_x[i] + skeleton_width && player_x + PlayerWidth > skeleton_x[i] && player_y < skeleton_y[i] + skeleton_height && player_y + PlayerHeight > skeleton_y[i]) {
            return true;
        }
    }
    //here we are checking collision with chelnovs
     for (int i = 0; i < num_chelnov; i++) {
        int enemy_index = chelnov_start_index + i;
        if (!enemy_active[enemy_index])
         continue;
        
        float chelnov_width = 26;
        float chelnov_height = 38;
        
        if (player_x < chelnov_x[i] + chelnov_width && player_x + PlayerWidth >chelnov_x[i] && player_y < chelnov_y[i] + chelnov_height && player_y + PlayerHeight > chelnov_y[i]) {
            return true;
        }
    }
    //here we are checking collision with invisible man
     for (int i = 0; i < num_invisibleman; i++) {
        int enemy_index = invisibleman_start_index + i;
        if (!enemy_active[enemy_index])
         continue;
        
        float invisibleman_width = 30;
        float invisibleman_height = 40;
        
        if (player_x < invisibleman_x[i] + invisibleman_width && player_x + PlayerWidth >invisibleman_x[i] && player_y < invisibleman_y[i] + invisibleman_height && player_y + PlayerHeight > invisibleman_y[i]) {
            return true;
        }
    }
    
    return false;
}

bool collision_with_fireball(float player_x, float player_y, int PlayerWidth, int PlayerHeight, float fireball_x[], float fireball_y[], bool fireball_active[], int num_fireballs) {
    
    float fireball_width = 17;  // This is the height and width of the fire ball
    float fireball_height = 17;
    
    for(int i = 0; i < num_fireballs; i++){
        if(fireball_active[i]){
            if(player_x < fireball_x[i] + fireball_width && player_x + PlayerWidth > fireball_x[i] && player_y < fireball_y[i] + fireball_height && player_y + PlayerHeight > fireball_y[i]){
                fireball_active[i] = false;  // This will destroy the fireball if we hit them
                return true;
            }
        }
    }
    return false;
}

void shoot_enemy(float player_x, float player_y, int PlayerWidth, int PlayerHeight, bool facingRight,
                 int& enemies_in_bag, int bagged_enemies[], char bagged_enemy_types[],
                 float shot_x[], float shot_y[], float shot_speed[], bool shot_active[], char shot_type[],
                 Sprite ghostShotSprite[], Sprite skeletonShotSprite[], Sprite chelnovShotSprite[], Sprite InvisibleManShotSprite[],
                 int max_shots) 
{
    if (enemies_in_bag <= 0) return; 

    int slot = -1;
    for (int i = 0; i < max_shots; i++) {
        if (!shot_active[i]) {
            slot = i;
            break;
        }
    }
    if (slot == -1) return;

    // Activate
    shot_active[slot] = true;
    shot_type[slot] = bagged_enemy_types[enemies_in_bag - 1];

    shot_speed[slot] = facingRight ? 10.0f : -10.0f;
    shot_x[slot] = facingRight ? player_x + PlayerWidth : player_x;
    shot_y[slot] = player_y + PlayerHeight * 0.5f;

    // Set correct sprite position
    if (shot_type[slot] == 'G')
        ghostShotSprite[slot].setPosition(shot_x[slot], shot_y[slot]);
    else if (shot_type[slot] == 'S')
        skeletonShotSprite[slot].setPosition(shot_x[slot], shot_y[slot]);
    else if (shot_type[slot] == 'C')
        chelnovShotSprite[slot].setPosition(shot_x[slot], shot_y[slot]);
     else if (shot_type[slot] == 'I')
        InvisibleManShotSprite[slot].setPosition(shot_x[slot], shot_y[slot]);
            
        

    // Remove last item from bag
    enemies_in_bag--;
}
void update_shots(RenderWindow& window,
                  float shot_x[], float shot_y[], float shot_speed[],
                  bool shot_active[], char shot_type[],
                  Sprite ghostShotSprite[], Sprite skeletonShotSprite[], Sprite chelnovShotSprite[],
                  int max_shots)
{
    for (int i = 0; i < max_shots; i++) {

        if (!shot_active[i]) continue;

        // Move
        shot_x[i] += shot_speed[i];

        // Update correct sprite
        if (shot_type[i] == 'G')
            ghostShotSprite[i].setPosition(shot_x[i], shot_y[i]);

        else if (shot_type[i] == 'S')
            skeletonShotSprite[i].setPosition(shot_x[i], shot_y[i]);

        else if (shot_type[i] == 'C')
            chelnovShotSprite[i].setPosition(shot_x[i], shot_y[i]);

        // Deactivate if out of screen
        if (shot_x[i] < 0 || shot_x[i] > 1136) {
            shot_active[i] = false;
            continue;
        }

        // Draw correct sprite
        if (shot_type[i] == 'G')
            window.draw(ghostShotSprite[i]);

        else if (shot_type[i] == 'S')
            window.draw(skeletonShotSprite[i]);

        else if (shot_type[i] == 'C')
            window.draw(chelnovShotSprite[i]);
    }
}



bool collision_with_powerup(float player_x, float player_y, int PlayerWidth, int PlayerHeight,
float powerup_x, float powerup_y, float powerup_width, float powerup_height) {
    if (player_x < powerup_x + powerup_width && player_x + PlayerWidth > powerup_x && player_y < powerup_y + powerup_height && player_y + PlayerHeight > powerup_y)
    { return true;
    }
    else
    return false;
            
}

bool check_level_complete(bool enemy_active[], int total_enemies) {
    for(int i = 0; i < total_enemies; i++) {
        if(enemy_active[i]) return false;
    }
    return true;
}

void setup_level_1(char** lvl, int height, int width,
                   float ghost_x[], float ghost_y[], float ghostV_x[],
                   float skeleton_x[], float skeleton_y[], float skeletonV_x[],
                   Sprite GhostSprite[], Sprite SkeletonSprite[],
                   Texture& GhostTexture, Texture& SkeletonTexture,
                   bool enemy_active[], int total_enemies) {
    
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            lvl[i][j] = ' ';
    
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            if (i ==4 && (j >= 0 && j <= 4)) lvl[i][j] = '#';
            else if (i == 9 && (j >= 0 && j <= 2)) lvl[i][j] = '#';
            else if (i == 4 && (j >= 13 && j <= 17)) lvl[i][j] = '#';
            else if (i == 9 && (j >= 15 && j <= 17)) lvl[i][j] = '#';
            else if (i == 11 && (j >= 6 && j <= 11)) lvl[i][j] = '#';
            else if (i == 2 && (j >= 7 && j <= 10)) lvl[i][j] = '#';
            else if (i == 7 && (j >= 4 && j <= 13)) lvl[i][j] = '#';
            else if (i == 13 && (j >= 0 && j <= 17)) lvl[i][j] = '#';
            else lvl[i][j] = ' ';
        }
    }
    
    for(int i = 0; i < total_enemies; i++)
        enemy_active[i] = true;
    
    for(int i=0; i<8; i++){
        GhostSprite[i].setTexture(GhostTexture);
        GhostSprite[i].setScale(3,3);
        if(i==0){
            ghost_x[i]=100;
            ghost_y[i]=218;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==1){
            ghost_x[i]=1000;
            ghost_y[i]=216;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==2){
            ghost_x[i]=480;
            ghost_y[i]=98;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==3){
            ghost_x[i]=600;
            ghost_y[i]=98;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==4){
            ghost_x[i]=350;
            ghost_y[i]=404;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==5){
            ghost_x[i]=750;
            ghost_y[i]=404;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==6){
            ghost_x[i]=350;
            ghost_y[i]=644;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==7){
            ghost_x[i]=750;
            ghost_y[i]=644;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        
        if(rand()%2==0)
            ghostV_x[i]=-2.0f;
        else
            ghostV_x[i]=2.0f;
    }
    
    for(int i=0; i<4; i++){
        SkeletonSprite[i].setTexture(SkeletonTexture);
        SkeletonSprite[i].setScale(3,3);
        if(i==0){
            skeleton_x[i]=100;
            skeleton_y[i]=218;
            SkeletonSprite[i].setPosition(skeleton_x[i],skeleton_y[i]);
        }
        if(i==1){
            skeleton_x[i]=1000;
            skeleton_y[i]=216;
            SkeletonSprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
        }
        if(i==2){
            skeleton_x[i]=480;
            skeleton_y[i]=700;
            SkeletonSprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
        }
        if(i==3){
            skeleton_x[i]=600;
            skeleton_y[i]=400;
            SkeletonSprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
        }
        
        if(rand()%2==0)
            skeletonV_x[i]=-1.5f;
        else
            skeletonV_x[i]=1.5f;
    }
}
// This function adds level 2 specific things
void create_slant_platform(char** lvl, int height, int width, bool direction) {
    // direction: true = top-left to bottom-right, false = top-right to bottom-left
    
    int start_row = 2; // Start from row 2
    int platform_length = 9; // Longer slant platform
    
    if (direction) {
        // Slant from top-left to bottom-right
        int start_col = 2; // Start from column 2
        
        for (int i = 0; i < platform_length; i++) {
            int row = start_row + i;
            int col = start_col + i;
            
            if (row < height && col < width) {
                lvl[row][col] = '#';
                // Make it 2 tiles thick by adding block below
                if (row + 1 < height) {
                    lvl[row + 1][col] = '#';
                }
            }
        }
    } else {
        // Slant from top-right to bottom-left
        int start_col = 15; // Start from column 15
        
        for (int i = 0; i < platform_length; i++) {
            int row = start_row + i;
            int col = start_col - i;
            
            if (row < height && col >= 0) {
                lvl[row][col] = '#';
                // Make it 2 tiles thick by adding block below
                if (row + 1 < height) {
                    lvl[row + 1][col] = '#';
                }
            }
        }
    }
}

// Modified setup_level_2 function - replace the level generation part:
void setup_level_2(char** lvl, int height, int width,
                   float ghost_x[], float ghost_y[], float ghostV_x[],
                   float skeleton_x[], float skeleton_y[], float skeletonV_x[],
                   Sprite GhostSprite[], Sprite SkeletonSprite[],
                   Texture& GhostTexture, Texture& SkeletonTexture,
                   bool enemy_active[], int total_enemies,
                   float chelnov_x[], float chelnov_y[], float chelnovV_x[],
                   bool chelnov_facing_right[], Sprite ChelnovSprite[],
                   Texture& ChelnovTexture, int num_chelnov,
                   float fireball_x[], float fireball_y[], float fireball_vx[],
                   bool fireball_active[], Sprite FireballSprite[],
                   Texture& FireballTexture, int num_fireballs,
                   int fireballs_cooldown[],
                   float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[],
                   Sprite InvisibleManSprite[], Texture& InvisibleManTexture, int num_invisibleman) {
    
    // Clear the level first
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            lvl[i][j] = ' ';
    
    // Create modified platforms (removed top middle and some platforms to make room for slant)
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            if (i == 4 && (j >= 0 && j <= 3)) lvl[i][j] = '#';  // Left top platform (shorter)
            else if (i == 9 && (j >= 0 && j <= 2)) lvl[i][j] = '#';
            else if (i == 4 && (j >= 14 && j <= 17)) lvl[i][j] = '#';  // Right top platform (shorter)
            else if (i == 9 && (j >= 15 && j <= 17)) lvl[i][j] = '#';
            else if (i == 11 && (j >= 6 && j <= 11)) lvl[i][j] = '#';
            // Removed middle top platform to make room for slant
            else if (i == 13 && (j >= 0 && j <= 17)) lvl[i][j] = '#';  // Ground
        }
    }
    
    // Add random slant platform
    bool slant_direction = rand() % 2; // Random direction
    create_slant_platform(lvl, height, width, slant_direction);
    
    // Rest of the setup_level_2 code remains the same...
    for(int i = 0; i < total_enemies; i++)
        enemy_active[i] = true;
    
    for(int i=0; i<8; i++){
        GhostSprite[i].setTexture(GhostTexture);
        GhostSprite[i].setScale(3,3);
        if(i==0){
            ghost_x[i]=100;
            ghost_y[i]=218;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==1){
            ghost_x[i]=1000;
            ghost_y[i]=216;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==2){
            ghost_x[i]=480;
            ghost_y[i]=98;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==3){
            ghost_x[i]=600;
            ghost_y[i]=98;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==4){
            ghost_x[i]=350;
            ghost_y[i]=404;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==5){
            ghost_x[i]=750;
            ghost_y[i]=404;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==6){
            ghost_x[i]=350;
            ghost_y[i]=644;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        if(i==7){
            ghost_x[i]=750;
            ghost_y[i]=644;
            GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        }
        
        if(rand()%2==0)
            ghostV_x[i]=-2.5f;
        else
            ghostV_x[i]=2.5f;
    }
    
    for(int i=0; i<4; i++){
        SkeletonSprite[i].setTexture(SkeletonTexture);
        SkeletonSprite[i].setScale(3,3);
        if(i==0){
            skeleton_x[i]=150;
            skeleton_y[i]=284;
            SkeletonSprite[i].setPosition(skeleton_x[i],skeleton_y[i]);
        }
        if(i==1){
            skeleton_x[i]=950;
            skeleton_y[i]=284;
            SkeletonSprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
        }
        if(i==2){
            skeleton_x[i]=400;
            skeleton_y[i]=668;
            SkeletonSprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
        }
        if(i==3){
            skeleton_x[i]=700;
            skeleton_y[i]=470;
            SkeletonSprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
        }
        
        if(rand()%2==0)
            skeletonV_x[i]=-2.0f;
        else
            skeletonV_x[i]=2.0f;
    }
    
    for(int i = 0; i < num_chelnov; i++){
        ChelnovSprite[i].setTexture(ChelnovTexture);
        ChelnovSprite[i].setScale(3, 3);
        fireballs_cooldown[i] = 0;
        
        if(i == 0){
            chelnov_x[i] = 100;
            chelnov_y[i] = 218;
            ChelnovSprite[i].setPosition(chelnov_x[i], chelnov_y[i]);
        }
        if(i == 1){
            chelnov_x[i] = 900;
            chelnov_y[i] = 300;
            ChelnovSprite[i].setPosition(chelnov_x[i], chelnov_y[i]);
        }
        if(i == 2){
            chelnov_x[i] = 900;
            chelnov_y[i] = 200;
            ChelnovSprite[i].setPosition(chelnov_x[i], chelnov_y[i]);
        }
        if(i == 3){
            chelnov_x[i] = 600;
            chelnov_y[i] = 300;
            ChelnovSprite[i].setPosition(chelnov_x[i], chelnov_y[i]);
        }
        
        if(rand()%2==0){
            chelnovV_x[i]=-1.5f;
            chelnov_facing_right[i] = false;
        }
        else
        {
            chelnovV_x[i]=1.5f;
            chelnov_facing_right[i] = true; 
        }
    }

    for(int i = 0; i < num_fireballs; i++){
        FireballSprite[i].setTexture(FireballTexture);
        FireballSprite[i].setScale(2, 2);
        fireball_active[i] = false;
        fireball_x[i] = -100;
        fireball_y[i] = -100;
        fireball_vx[i] = 0;
    }

    for(int i = 0; i < num_invisibleman; i++){
        InvisibleManSprite[i].setTexture(InvisibleManTexture);
        InvisibleManSprite[i].setScale(3, 3);
        
        if(i == 0){
            invisibleman_x[i] = 170;
            invisibleman_y[i] = 318;
            InvisibleManSprite[i].setPosition(invisibleman_x[i], invisibleman_y[i]);
        }
        if(i == 1){
            invisibleman_x[i] = 900;
            invisibleman_y[i] = 316;
            InvisibleManSprite[i].setPosition(invisibleman_x[i], invisibleman_y[i]);
        }
        if(i == 2){
            invisibleman_x[i] = 150;
            invisibleman_y[i] = 250;
            InvisibleManSprite[i].setPosition(invisibleman_x[i], invisibleman_y[i]);
        }
        
        if(rand()%2==0)
            invisiblemanV_x[i]=-1.5f;
        else
            invisiblemanV_x[i]=1.5f;
    }
}

void mechanism_chelnov_and_fireballs(float chelnov_x[], float chelnov_y[], bool chelnov_facing_right[],
                                   int num_chelnov, float fireball_x[], float fireball_y[], 
                                   float fireball_vx[], bool fireball_active[], 
                                   Sprite FireballSprite[], int fireballs_cooldown[], 
                                   int fire_rate, int num_fireballs, int screen_x){
    // This step loop through each chelnov to find out  if  it is  available to fire
    for(int i = 0; i < num_chelnov; i++){
        fireballs_cooldown[i]--;    //Here we are checking the cooldown time, when the cooldown turn 0 shoot
        
        if( fireballs_cooldown[i] <= 0){
    //This step is to find out if we have fireballs available to  shoot
            for(int j = 0; j < num_fireballs; j++){
                if(!fireball_active[j]){
                    fireball_active[j] = true;
                    fireball_x[j] = chelnov_x[i] + 48; // These are just the coordinates where we need to spawn fireballs,ideally its the center of chelnov
                    fireball_y[j] = chelnov_y[i] + 48;
                    
                  if(chelnov_facing_right[i]){
                        fireball_vx[j] = 5.0f;  // This step will determine the direction, where the ball should be fired
                    } else {
                        fireball_vx[j] = -5.0f; 
                    }

                    
                     fireballs_cooldown[i] = fire_rate;
                    break;
                }
            }
        }
    }
    // This step is updating the fireballs to fire 
    for(int i = 0; i < num_fireballs; i++){
        if(fireball_active[i]){
            fireball_x[i] += fireball_vx[i];
     // Here if the fireball is out of the screen it vanishes        
            if(fireball_x[i] < -50 || fireball_x[i] > screen_x + 50){
                fireball_active[i] = false;
                fireball_x[i] = -100;
                fireball_y[i] = -100;
            }
            
            FireballSprite[i].setPosition(fireball_x[i], fireball_y[i]);
        }
    }
}

void ChelnovMovement(char** lvl, float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[], Sprite ChelnovSprite[], int num_chelnov, int cell_size, int width, int height, bool enemy_active[], int chelnov_start_index) {
    int Chelnov_Width = 26 , Chelnov_Height = 38;
    for (int i = 0; i < num_chelnov; i++) {
        int enemy_index = chelnov_start_index + i;
        if (!enemy_active[enemy_index]) 
        continue;
        
        chelnov_x[i] = chelnov_x[i] + chelnovV_x[i];

        int Middle_Col = static_cast<int>(chelnov_x[i] + Chelnov_Width/2) / cell_size;

        int startRow = static_cast<int>(chelnov_y[i] + 14) / cell_size; 
        int endRow = startRow + 2;

        for (int row = startRow; row <= endRow; row++) {
            if (lvl[row][Middle_Col] == '#') {
                chelnov_y[i] = row * cell_size - 114;
                break;
            }
        }

        int frontX = (chelnovV_x[i] > 0) ? static_cast<int>(chelnov_x[i] + 90) / cell_size : static_cast<int>(chelnov_x[i] - 1) / cell_size;
        int footY = static_cast<int>(chelnov_y[i] + 114) / cell_size;

        if (frontX < 0 || frontX >= width || lvl[footY][frontX] != '#') {
            chelnovV_x[i] = -chelnovV_x[i];
            chelnov_facing_right[i] = !chelnov_facing_right[i]; // Flipping the facing direction
        }

        ChelnovSprite[i].setPosition(chelnov_x[i], chelnov_y[i]);
    }
}

void ChelnovGravity(char** lvl, float chelnov_x[], float chelnov_y[], Sprite ChelnovSprite[], int num_chelnov, int cell_size, int width, int height, bool enemy_active[], int chelnov_start_index) {
    int Chelnov_Width = 32, Chelnov_Height = 38;
    for (int i = 0; i < num_chelnov; i++) {
        int enemy_index = chelnov_start_index + i;
        if (!enemy_active[enemy_index]) continue;
        
        int middleCol = static_cast<int>(chelnov_x[i] + Chelnov_Width/2) / cell_size;
        int startingRow = static_cast<int>(chelnov_y[i] + Chelnov_Height) / cell_size;
        int endingRow = startingRow + 2;
        
        for (int row = startingRow; row <= endingRow; row++) {
            if (lvl[row][middleCol] == '#') {
                chelnov_y[i] = row * cell_size - 114;
                break;
            }
        }
        
        ChelnovSprite[i].setPosition(chelnov_x[i], chelnov_y[i]);
    }
}

void InvisibleManMovement(char** lvl, float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[], Sprite InvisibleManSprite[], int num_invisibleman, int cell_size, int width, int height, bool enemy_active[], int invisibleman_start_index) {
    int InvisibleMan_Width = 30, InvisibleMan_Height = 40; 
    for (int i = 0; i < num_invisibleman; i++) {
        int enemy_index = invisibleman_start_index + i;
        if (!enemy_active[enemy_index]) 
        continue;
        
        invisibleman_x[i] = invisibleman_x[i] + invisiblemanV_x[i];

        int Middle_Col = static_cast<int>(invisibleman_x[i] + InvisibleMan_Width/2) / cell_size;

        int startRow = static_cast<int>(invisibleman_y[i] + InvisibleMan_Height) / cell_size; 
        int endRow = startRow + 2;

        for (int row = startRow; row <= endRow; row++) {
            if (lvl[row][Middle_Col] == '#') {
                invisibleman_y[i] = row * cell_size - InvisibleMan_Height;
                break;
            }
        }

        int frontX = (invisiblemanV_x[i] > 0) ? static_cast<int>(invisibleman_x[i] + InvisibleMan_Width) / cell_size : static_cast<int>(invisibleman_x[i] - 1) / cell_size;
        int footY = static_cast<int>(invisibleman_y[i] + InvisibleMan_Height) / cell_size;

        if (frontX < 0 || frontX >= width || lvl[footY][frontX] != '#') {
            invisiblemanV_x[i] = -invisiblemanV_x[i];
        }

        InvisibleManSprite[i].setPosition(invisibleman_x[i], invisibleman_y[i]);
    }
}


void Sprites_Textures(Texture& char1Tex, Texture& char2Tex, Texture& menuBgTex, 
                        Sprite& Player1Sprite, Sprite& Player2Sprite, Sprite& menuBgSprite,
                        Texture& vacuumTex, Sprite& vacuumSprite,
                        Texture& tsTex, Sprite& tsSprite,
                        Texture& level2ScreenTex, Sprite& level2ScreenSprite,
                        Texture& GhostTexture, Sprite GhostSprite[],
                        Texture& SkeletonTexture, Sprite SkeletonSprite[],
                        Texture& ChelnovTexture, Sprite ChelnovSprite[],
                        Texture& FireballTexture, Sprite FireballSprite[],
                        Texture& InvisibleManTexture, Sprite InvisibleManSprite[],
                        Texture& bgTex, Sprite& bgSprite,
                        Texture& blockTexture, Sprite& blockSprite,
                        Texture& ppuTex, Sprite& ppuSprite,
                        Texture& rpuTex, Sprite& rpuSprite,
                        Texture& elpuTex, Sprite& elpuSprite,
                        Texture& spuTex, Sprite& spuSprite,
                        Texture& ghostShotTexture, Sprite ghostShotSprite[],
                        Texture& skeletonShotTexture, Sprite skeletonShotSprite[],
                        Texture& chelnovShotTexture, Sprite chelnovShotSprite[],
                        Texture& InvisibleManShotTexture, Sprite InvisibleManShotSprite[],
                        int screen_x, int screen_y,
                        int ppu_x, int ppu_y, int rpu_x, int rpu_y,
                        int elpu_x, int elpu_y, int spu_x, int spu_y) {
    
    menuBgTex.loadFromFile("Assets/Sprites/menu.jpg");
    menuBgSprite.setTexture(menuBgTex);
    menuBgSprite.setScale(
        (float)screen_x / menuBgTex.getSize().x,
        (float)screen_y / menuBgTex.getSize().y
    );

    char1Tex.loadFromFile("Assets/Sprites/player.png");
    Player1Sprite.setTexture(char1Tex);
    Player1Sprite.setScale(3, 3);
    Player1Sprite.setPosition(200, 350);

    char2Tex.loadFromFile("Assets/Sprites/player2.png");
    Player2Sprite.setTexture(char2Tex);
    Player2Sprite.setScale(3, 3);
    Player2Sprite.setPosition(800, 350);

    vacuumTex.loadFromFile("Assets/Sprites/vaccum.png");
    vacuumSprite.setTexture(vacuumTex);
    vacuumSprite.setScale(1.5f, 1.5f);

    tsTex.loadFromFile("Assets/Sprites/ts.png");
    tsSprite.setTexture(tsTex);
    tsSprite.setScale(
        (float)screen_x / tsTex.getSize().x,
        (float)screen_y / tsTex.getSize().y
    );

    level2ScreenTex.loadFromFile("Assets/Sprites/level2.jpg");
    level2ScreenSprite.setTexture(level2ScreenTex);
    level2ScreenSprite.setScale(
        (float)screen_x / level2ScreenTex.getSize().x,
        (float)screen_y / level2ScreenTex.getSize().y
    );

    GhostTexture.loadFromFile("Assets/Sprites/ghost.png");
    for(int i = 0; i < 8; i++) {
        GhostSprite[i].setTexture(GhostTexture);
        GhostSprite[i].setScale(3, 3);
    }

    SkeletonTexture.loadFromFile("Assets/Sprites/skeleton.png");
    for(int i = 0; i < 4; i++) {
        SkeletonSprite[i].setTexture(SkeletonTexture);
        SkeletonSprite[i].setScale(3, 3);
    }

    ChelnovTexture.loadFromFile("Assets/Sprites/chelnov.png");
    for(int i = 0; i < 4; i++) {
        ChelnovSprite[i].setTexture(ChelnovTexture);
        ChelnovSprite[i].setScale(3, 3);
    }

    FireballTexture.loadFromFile("Assets/Sprites/fireball.png");
    for(int i = 0; i < 10; i++) {
        FireballSprite[i].setTexture(FireballTexture);
        FireballSprite[i].setScale(2, 2);
    }

    InvisibleManTexture.loadFromFile("Assets/Sprites/invisibleman.png");
    for(int i = 0; i < 3; i++) {
        InvisibleManSprite[i].setTexture(InvisibleManTexture);
        InvisibleManSprite[i].setScale(3, 3);
    }

    bgTex.loadFromFile("Assets/Sprites/background.jpg");
    bgSprite.setTexture(bgTex);

    blockTexture.loadFromFile("Assets/Sprites/blocks.png");
    blockSprite.setTexture(blockTexture);

    ppuTex.loadFromFile("Assets/Sprites/powerpu.png");
    ppuSprite.setTexture(ppuTex);
    ppuSprite.setScale(2, 2);
    ppuSprite.setPosition(ppu_x, ppu_y);

    rpuTex.loadFromFile("Assets/Sprites/rangepu.png");
    rpuSprite.setTexture(rpuTex);
    rpuSprite.setScale(2, 2);
    rpuSprite.setPosition(rpu_x, rpu_y);

    elpuTex.loadFromFile("Assets/Sprites/extralifepu.png");
    elpuSprite.setTexture(elpuTex);
    elpuSprite.setScale(2, 2);
    elpuSprite.setPosition(elpu_x, elpu_y);

    spuTex.loadFromFile("Assets/Sprites/speedpu.png");
    spuSprite.setTexture(spuTex);
    spuSprite.setScale(2, 2);
    spuSprite.setPosition(spu_x, spu_y);

    ghostShotTexture.loadFromFile("Assets/Sprites/ghostshot.png");
    skeletonShotTexture.loadFromFile("Assets/Sprites/shot.png");
    chelnovShotTexture.loadFromFile("Assets/Sprites/chelnovshot.png");
    InvisibleManShotTexture.loadFromFile("Assets/Sprites/invisiblemanshot.png");

    for (int i = 0; i < 10; i++) {
        ghostShotSprite[i].setTexture(ghostShotTexture);
        ghostShotSprite[i].setScale(2.0f, 2.0f);

        skeletonShotSprite[i].setTexture(skeletonShotTexture);
        skeletonShotSprite[i].setScale(2.0f, 2.0f);

        chelnovShotSprite[i].setTexture(chelnovShotTexture);
        chelnovShotSprite[i].setScale(2.0f, 2.0f);
    }
}

void handleTitleScreen(RenderWindow& window, Sprite& tsSprite, bool& TitleScreenOn, bool& CharacterSelectOn) {
    window.draw(tsSprite);
    window.display();

    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
        TitleScreenOn = false;
        CharacterSelectOn = true;
    }
}

void handleCharacterSelect(RenderWindow& window, Sprite& menuBgSprite, Sprite& Player1Sprite, Sprite& Player2Sprite, 
                          bool& CharacterSelectOn, bool& GameOn, int& chosenPlayer, 
                          Sprite*& chosenCharacter, float& Speed, int& vacuum_range,
                          float player1speed, float player2speed, int player1range, int player2range) {
    window.draw(menuBgSprite);
    window.draw(Player1Sprite);
    window.draw(Player2Sprite);

    if (Keyboard::isKeyPressed(Keyboard::Num1))
        chosenPlayer = 1;
    if (Keyboard::isKeyPressed(Keyboard::Num2))
        chosenPlayer = 2;

    if (chosenPlayer != 0) {
        switch (chosenPlayer) {
            case 1:
                chosenCharacter = &Player1Sprite;
                Speed = player1speed;
                vacuum_range = player1range;
                break;
            case 2:
                chosenCharacter = &Player2Sprite;
                Speed = player2speed;
                vacuum_range = player2range;
                break;
        }

        CharacterSelectOn = false;
        GameOn = true;
    }

    window.display();
}

void handlePlayerInput(Sprite& chosenCharacter, float& player_x, float& player_y, float& velocityY, bool& onGround, 
                      float Speed, bool& facingRight, float jumpStrength, int PlayerHeight, int cell_size, int screen_y) {
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        chosenCharacter.move(Speed, 0);
        player_x = chosenCharacter.getPosition().x;
        chosenCharacter.setScale(-3, 3);
        facingRight = true;
    }

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        chosenCharacter.move(-Speed, 0);
        player_x = chosenCharacter.getPosition().x;
        chosenCharacter.setScale(3, 3);
        facingRight = false;
    }

    if (Keyboard::isKeyPressed(Keyboard::Up) && onGround) {
        velocityY = jumpStrength;
        onGround = false;
    }

    if (Keyboard::isKeyPressed(Keyboard::Down) && onGround) {
        if(!(player_y + PlayerHeight == screen_y - cell_size)) {
            player_y += 20;
            velocityY = 0;
        }
        onGround = false;
    }
}

void handlePowerups(float player_x, float player_y, int PlayerWidth, int PlayerHeight,
                   bool& ppu_active, bool& rpu_active, bool& elpu_active, bool& spu_active,
                   int ppu_x, int ppu_y, int rpu_x, int rpu_y, int elpu_x, int elpu_y, int spu_x, int spu_y,
                   Sprite& ppuSprite, Sprite& rpuSprite, Sprite& elpuSprite, Sprite& spuSprite,
                   float& Speed, int& playerLives, int& vacuum_range, int& playerScore) {
    
    if (spu_active && collision_with_powerup(player_x, player_y, PlayerWidth, PlayerHeight, spu_x, spu_y, 32, 32)) {
        spu_active = false;
        Speed *= 1.5f;
        spuSprite.setPosition(-100, -100);
        playerScore+=50;
    }
    
    if (elpu_active && collision_with_powerup(player_x, player_y, PlayerWidth, PlayerHeight, elpu_x, elpu_y, 64, 64)) {
        elpu_active = false;
        playerLives++;
        elpuSprite.setPosition(-100, -100);
        playerScore+=100;
    }

    if (rpu_active && collision_with_powerup(player_x, player_y, PlayerWidth, PlayerHeight, rpu_x, rpu_y, 32, 32)) {
        rpu_active = false;
        vacuum_range = 600;
        rpuSprite.setPosition(-100, -100);
        playerScore+=75;
    }
}
// This function resets level 1 once player collides with the enemies 3 times
void resetLevel1(float ghost_x[], float ghost_y[], float ghostV_x[],
                float skeleton_x[], float skeleton_y[], float skeletonV_x[],
                Sprite GhostSprite[], Sprite SkeletonSprite[],
                Texture& GhostTexture, Texture& SkeletonTexture) {
    
    for(int i=0; i<8; i++){
        GhostSprite[i].setTexture(GhostTexture);
        GhostSprite[i].setScale(3,3);
        if(i==0){ 
        ghost_x[i]=100; 
        ghost_y[i]=218; 
    }
        if(i==1){ 
        ghost_x[i]=1000; 
        ghost_y[i]=216; 
    }
        if(i==2){ 
        ghost_x[i]=480; 
        ghost_y[i]=98; 
    }
        if(i==3){ 
        ghost_x[i]=600; 
        ghost_y[i]=98; 
    }
        if(i==4){ 
        ghost_x[i]=350; 
        ghost_y[i]=404; 
    }
        if(i==5){ 
        ghost_x[i]=750; 
        ghost_y[i]=404; 
    }
        if(i==6){ 
        ghost_x[i]=350; 
        ghost_y[i]=644; 
    }
        if(i==7){ 
        ghost_x[i]=750; 
        ghost_y[i]=644; 
    }
        GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        ghostV_x[i] = (rand()%2==0) ? -2.0f : 2.0f;
    }
    
    for(int i=0; i<4; i++){
        SkeletonSprite[i].setTexture(SkeletonTexture);
        SkeletonSprite[i].setScale(3,3);
        if(i==0){ 
        skeleton_x[i]=100; 
        skeleton_y[i]=218; 
    }
        if(i==1){ 
        skeleton_x[i]=1000; 
        skeleton_y[i]=216; 
    }
        if(i==2){ 
        skeleton_x[i]=480; 
        skeleton_y[i]=700; 
    }
        if(i==3){ 
        skeleton_x[i]=600; 
        skeleton_y[i]=400; 
    }
        SkeletonSprite[i].setPosition(skeleton_x[i],skeleton_y[i]);
        skeletonV_x[i] = (rand()%2==0) ? -1.5f : 1.5f;
    }
}
// This function resets level 2 once player collides with enemies in level 2 thrice
void resetLevel2(float ghost_x[], float ghost_y[], float ghostV_x[],
                float skeleton_x[], float skeleton_y[], float skeletonV_x[],
                Sprite GhostSprite[], Sprite SkeletonSprite[],
                Texture& GhostTexture, Texture& SkeletonTexture,
                float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[],
                Sprite ChelnovSprite[], Texture& ChelnovTexture, int num_chelnov,
                float fireball_x[], float fireball_y[], float fireball_vx[], bool fireball_active[],
                Sprite FireballSprite[], Texture& FireballTexture, int num_fireballs, int fireballs_cooldown[],
                float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[],
                Sprite InvisibleManSprite[], Texture& InvisibleManTexture, int num_invisibleman) {
    
    for(int i=0; i<8; i++){
        GhostSprite[i].setTexture(GhostTexture);
        GhostSprite[i].setScale(3,3);
        if(i==0){ 
        ghost_x[i]=200; 
        ghost_y[i]=98; 
    }
        if(i==1){ 
        ghost_x[i]=900; 
        ghost_y[i]=98; 
    }
        if(i==2){ 
        ghost_x[i]=150; 
        ghost_y[i]=284; 
    }
        if(i==3){ 
        ghost_x[i]=950; 
        ghost_y[i]=284; 
    }
        if(i==4){ 
        ghost_x[i]=400; 
        ghost_y[i]=470; 
    }
        if(i==5){ 
        ghost_x[i]=700; 
        ghost_y[i]=470; 
    }
        if(i==6){ 
        ghost_x[i]=250; 
        ghost_y[i]=668; 
    }
        if(i==7){ 
        ghost_x[i]=850; 
        ghost_y[i]=668; 
    }
        GhostSprite[i].setPosition(ghost_x[i], ghost_y[i]);
        ghostV_x[i] = (rand()%2==0) ? -2.5f : 2.5f;
    }
    
    for(int i=0; i<4; i++){
        SkeletonSprite[i].setTexture(SkeletonTexture);
        SkeletonSprite[i].setScale(3,3);
        if(i==0){
        skeleton_x[i]=150; 
        skeleton_y[i]=284; 
    }
        if(i==1){ 
        skeleton_x[i]=950; 
        skeleton_y[i]=284; 
    }
        if(i==2){ 
        skeleton_x[i]=400; 
        skeleton_y[i]=668; 
    }
        if(i==3){ 
        skeleton_x[i]=700; 
        skeleton_y[i]=470; 
    }
        SkeletonSprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
        skeletonV_x[i] = (rand()%2==0) ? -2.0f : 2.0f;
    }
    
    for(int i = 0; i < num_chelnov; i++){
        ChelnovSprite[i].setTexture(ChelnovTexture);
        ChelnovSprite[i].setScale(3, 3);
        fireballs_cooldown[i] = 0;
        if(i == 0){ 
        chelnov_x[i] = 200; 
        chelnov_y[i] = 500; 
    }
        if(i == 1){ 
        chelnov_x[i] = 900; 
        chelnov_y[i] = 300; 
    }
        if(i == 2){ 
        chelnov_x[i] = 900; 
        chelnov_y[i] = 200; 
    }
        if(i == 3){ 
        chelnov_x[i] = 600; 
        chelnov_y[i] = 300; 
    }
        ChelnovSprite[i].setPosition(chelnov_x[i], chelnov_y[i]);
        if(rand()%2==0){ chelnovV_x[i]=-1.5f; chelnov_facing_right[i] = false; }
        else{ chelnovV_x[i]=1.5f; chelnov_facing_right[i] = true; }
    }

    for(int i = 0; i < num_fireballs; i++){
        FireballSprite[i].setTexture(FireballTexture);
        FireballSprite[i].setScale(2, 2);
        fireball_active[i] = false;
        fireball_x[i] = -100;
        fireball_y[i] = -100;
        fireball_vx[i] = 0;
    }
    
    for(int i = 0; i < num_invisibleman; i++){
        InvisibleManSprite[i].setTexture(InvisibleManTexture);
        InvisibleManSprite[i].setScale(3, 3);
        if(i == 0){ 
        invisibleman_x[i] = 170; 
        invisibleman_y[i] = 318; 
    }
        if(i == 1){ 
        invisibleman_x[i] = 900; 
        invisibleman_y[i] = 316; 
    }
        if(i == 2){ 
        invisibleman_x[i] = 150; 
        invisibleman_y[i] = 250; 
    }
        InvisibleManSprite[i].setPosition(invisibleman_x[i], invisibleman_y[i]);
        invisiblemanV_x[i] = (rand()%2==0) ? -1.5f : 1.5f;
    }
}
// THis functions handles the collisions
void handleCollisions(float player_x, float player_y, int PlayerWidth, int PlayerHeight,
                     float ghost_x[], float ghost_y[], float skeleton_x[], float skeleton_y[],
                     float chelnov_x[], float chelnov_y[], float invisibleman_x[], float invisibleman_y[],
                     float fireball_x[], float fireball_y[], bool fireball_active[],
                     bool enemy_active[], bool& Collision, int& playerLives, int& rTimer,
                     bool vacuum_active, int currentLevel, int num_chelnov, int num_invisibleman, int num_fireballs,
                     int ghost_start_index, int skeleton_start_index, int chelnov_start_index, int invisibleman_start_index,int& playerScore, Sound& collisionSound ) {
    
    bool enemy_collision = false;

    if (!Collision && !vacuum_active) {
        if (currentLevel == 1) {
            enemy_collision = collision_with_enemy(player_x, player_y, PlayerWidth, PlayerHeight,
                                                  ghost_x, ghost_y, 8, ghost_start_index,
                                                  skeleton_x, skeleton_y, 4, skeleton_start_index,
                                                  chelnov_x, chelnov_y, 0, chelnov_start_index,
                                                  invisibleman_x, invisibleman_y, 0, invisibleman_start_index,
                                                  enemy_active);
        }
        else if (currentLevel == 2) {
            enemy_collision = collision_with_enemy(player_x, player_y, PlayerWidth, PlayerHeight,
                                                  ghost_x, ghost_y, 8, ghost_start_index,
                                                  skeleton_x, skeleton_y, 4, skeleton_start_index,
                                                  chelnov_x, chelnov_y, num_chelnov, chelnov_start_index,
                                                  invisibleman_x, invisibleman_y, num_invisibleman, invisibleman_start_index,
                                                  enemy_active);
            
            if (collision_with_fireball(player_x, player_y, PlayerWidth, PlayerHeight,
                                        fireball_x, fireball_y, fireball_active, num_fireballs)) {
                enemy_collision = true;
            }
        }
        
        if (enemy_collision) {
            playerLives--;
            Collision = true;
            playerScore -= 50;
            rTimer = 0;

             // PLAY COLLISION SOUND
            collisionSound.play();
        }
    }

    if (Collision) {
        rTimer++;
        if (rTimer >= 60) {
            Collision = false;
            rTimer = 0;
        }
    }
}
// This function handles when game is over
void handleGameOver(bool& GameOn, bool& TitleScreenOn, int& currentLevel, bool& levelComplete,
                   Music& lvl2Music, Music& lvlMusic, int& playerLives,
                   float& player_x, float& player_y, float& velocityY, int& enemies_in_bag,
                   bool enemy_active[], int total_enemies,
                   float ghost_x[], float ghost_y[], float ghostV_x[],
                   float skeleton_x[], float skeleton_y[], float skeletonV_x[],
                   Sprite GhostSprite[], Sprite SkeletonSprite[],
                   Texture& GhostTexture, Texture& SkeletonTexture,
                   float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[],
                   Sprite ChelnovSprite[], Texture& ChelnovTexture, int num_chelnov,
                   float fireball_x[], float fireball_y[], float fireball_vx[], bool fireball_active[],
                   Sprite FireballSprite[], Texture& FireballTexture, int num_fireballs, int fireballs_cooldown[],
                   float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[],
                   Sprite InvisibleManSprite[], Texture& InvisibleManTexture, int num_invisibleman, int& playerScore) {
    
    if(playerLives <= 0) {
        GameOn = false;
        TitleScreenOn = true;
        levelComplete = false;
        
        lvl2Music.stop();
        lvlMusic.setLoop(true);
        lvlMusic.setVolume(20);
        
        playerLives = 3;
        playerScore=0;
        player_x = 500;
        player_y = 700;
        velocityY = 0;
        enemies_in_bag = 0;
        
        for(int i = 0; i < total_enemies; i++)
            enemy_active[i] = true;
        
        if(currentLevel == 1) {
            resetLevel1(ghost_x, ghost_y, ghostV_x, skeleton_x, skeleton_y, skeletonV_x,
                       GhostSprite, SkeletonSprite, GhostTexture, SkeletonTexture);
        }
        else if(currentLevel == 2) {
            resetLevel2(ghost_x, ghost_y, ghostV_x, skeleton_x, skeleton_y, skeletonV_x,
                       GhostSprite, SkeletonSprite, GhostTexture, SkeletonTexture,
                       chelnov_x, chelnov_y, chelnovV_x, chelnov_facing_right,
                       ChelnovSprite, ChelnovTexture, num_chelnov,
                       fireball_x, fireball_y, fireball_vx, fireball_active,
                       FireballSprite, FireballTexture, num_fireballs, fireballs_cooldown,
                       invisibleman_x, invisibleman_y, invisiblemanV_x,
                       InvisibleManSprite, InvisibleManTexture, num_invisibleman);
        }
    }
    else {
        player_x = 500;
        player_y = 700;
        velocityY = 0;
        enemies_in_bag = 0;
    }
}
// Handles transition between level 1 and 2
void handleLevelTransition(bool& levelComplete, Clock& levelCompleteTimer, int& currentLevel,
                          bool& GameOn, bool& showLevelScreen, bool& TitleScreenOn,
                          Music& lvlMusic, Music& lvl2Music,
                          char** lvl, int height, int width,
                          float ghost_x[], float ghost_y[], float ghostV_x[],
                          float skeleton_x[], float skeleton_y[], float skeletonV_x[],
                          Sprite GhostSprite[], Sprite SkeletonSprite[],
                          Texture& GhostTexture, Texture& SkeletonTexture,
                          bool enemy_active[], int total_enemies,
                          float chelnov_x[], float chelnov_y[], float chelnovV_x[], bool chelnov_facing_right[],
                          Sprite ChelnovSprite[], Texture& ChelnovTexture, int num_chelnov,
                          float fireball_x[], float fireball_y[], float fireball_vx[], bool fireball_active[],
                          Sprite FireballSprite[], Texture& FireballTexture, int num_fireballs, int fireballs_cooldown[],
                          float invisibleman_x[], float invisibleman_y[], float invisiblemanV_x[],
                          Sprite InvisibleManSprite[], Texture& InvisibleManTexture, int num_invisibleman,
                          float& player_x, float& player_y, float& velocityY, int& enemies_in_bag, int& playerLives,int total_enemies_level1, int total_enemies_level2) {
    
    int enemies_to_check = (currentLevel == 1) ? total_enemies_level1 : total_enemies_level2;
if (!levelComplete && check_level_complete(enemy_active, enemies_to_check)) {
        levelComplete = true;
        levelCompleteTimer.restart();
    }

    if (levelComplete) {
        if (levelCompleteTimer.getElapsedTime().asSeconds() > 2.0f) {
            if (currentLevel == 1) {
                currentLevel = 2;
                GameOn = false;
                showLevelScreen = true;
                
                lvlMusic.stop();
                
                setup_level_2(lvl, height, width, 
                ghost_x, ghost_y, ghostV_x,
                skeleton_x, skeleton_y, skeletonV_x,
                GhostSprite, SkeletonSprite,
                GhostTexture, SkeletonTexture,
                enemy_active, total_enemies,
                chelnov_x, chelnov_y, chelnovV_x,
                chelnov_facing_right, ChelnovSprite,
                ChelnovTexture, num_chelnov,
                fireball_x, fireball_y, fireball_vx,
                fireball_active, FireballSprite,
                FireballTexture, num_fireballs,
                fireballs_cooldown,
                invisibleman_x, invisibleman_y, invisiblemanV_x,
                InvisibleManSprite, InvisibleManTexture, num_invisibleman);
                
                player_x = 500;
                player_y = 700;
                velocityY = 0;
                enemies_in_bag = 0;
                
                levelComplete = false;
            } else {
                GameOn = false;
                TitleScreenOn = true;
                currentLevel = 1;
                playerLives = 3;
                
                lvl2Music.stop();
                lvlMusic.setLoop(true);
                lvlMusic.setVolume(20);
            }
        }
    }
}

void renderGame(RenderWindow& window, char** lvl, Texture& bgTex, Sprite& bgSprite, 
               Texture& blockTexture, Sprite& blockSprite, int height, int width, int cell_size,
               Sprite& chosenCharacter, Sprite& vacuumSprite, bool vacuum_active,
               float player_x, float player_y, int PlayerWidth, int PlayerHeight, bool facingRight,
               Texture& vacuumTex, Sprite GhostSprite[], Sprite SkeletonSprite[],Sprite ghostShotSprite[], Sprite skeletonShotSprite[],
               Sprite ChelnovSprite[],Sprite InvisibleManShotSprite[],Sprite chelnovShotSprite[], Sprite FireballSprite[], Sprite InvisibleManSprite[],
               Sprite& ppuSprite, Sprite& rpuSprite, Sprite& elpuSprite, Sprite& spuSprite,
               bool enemy_active[], bool fireball_active[], int currentLevel,
               int ghost_start_index, int skeleton_start_index, int chelnov_start_index,
               int num_chelnov, int num_fireballs, int invisibleman_start_index, int num_invisibleman,bool shot_active[],int max_shots, char shot_type[] ) {
    
    display_level(window, lvl, bgTex, bgSprite, blockTexture, blockSprite, height, width, cell_size);
    
    chosenCharacter.setPosition(player_x, player_y);
    window.draw(chosenCharacter);

    if (vacuum_active) {
        float vac_y = player_y + PlayerHeight * 0.25f;
        float vac_x;

        if (facingRight) {
            vac_x = player_x + PlayerWidth + 5;
            vacuumSprite.setScale(-2.0f, 2.0f);
        }
        else {
            vac_x = player_x - vacuumTex.getSize().x * 2.0f;
            vacuumSprite.setScale(2.0f, 2.0f);
        }

        vacuumSprite.setPosition(vac_x, vac_y);
        window.draw(vacuumSprite);
    }

    for(int i = 0; i < 8; i++){
        if(enemy_active[ghost_start_index + i])
            window.draw(GhostSprite[i]);
    }
    
    for(int i = 0; i < 4; i++){
        if(enemy_active[skeleton_start_index + i])
            window.draw(SkeletonSprite[i]);
    }
    
    window.draw(ppuSprite);
    window.draw(rpuSprite);
    window.draw(elpuSprite);
    window.draw(spuSprite);

    if(currentLevel == 2) {
        for(int i = 0; i < num_chelnov; i++){
            if(enemy_active[chelnov_start_index + i])
                window.draw(ChelnovSprite[i]);
        }

        for(int i = 0; i < num_fireballs; i++){
            if(fireball_active[i]){
                window.draw(FireballSprite[i]);
            }
        }
        
        for(int i = 0; i < num_invisibleman; i++){
            if(enemy_active[invisibleman_start_index + i])
                window.draw(InvisibleManSprite[i]);
        }
    }
    for (int i = 0; i < max_shots; i++) {
    if (!shot_active[i]) continue;
    
    if (shot_type[i] == 'G')
        window.draw(ghostShotSprite[i]);
    else if (shot_type[i] == 'S')
        window.draw(skeletonShotSprite[i]);
    else if (shot_type[i] == 'C')
        window.draw(chelnovShotSprite[i]);
}
}

//Main Function

int main()
{
    srand(time(0));
    
    // Constants
    int screen_x = 1136;
    int screen_y = 896;
    const int max_shots = 10;
    const int cell_size = 64;
    const int height = 14;
    const int width = 18;
    int PlayerHeight = 102;
    int PlayerWidth = 96;
    const float player1speed = 6;
    const float player2speed = 4;
    const float jumpStrength = -20;
    const float gravity = 0.9;
    float terminal_Velocity = 20;
    const int rDelay = 60;
    const int total_enemies = 19;  
    const int total_enemies_level1 = 12;  
    const int total_enemies_level2 = 19;    
    const int num_chelnov = 4;
    const int num_fireballs = 10;
    const int num_invisibleman = 3;
    const int fire_rate = 270;
    const int max_bag_capacity = 3;
    const int ghost_start_index = 0;
    const int skeleton_start_index = 8;
    const int chelnov_start_index = 12;
    const int invisibleman_start_index = 16;
    const int player1range = 300;
    const int player2range = 360;
    
    RenderWindow window(VideoMode(screen_x, screen_y), "Tumble-POP");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    // Game state variables
    bool TitleScreenOn = true;
    bool CharacterSelectOn = false;
    bool GameOn = false;
    bool GameOver = false;
    int playerLives = 3;
    int playerScore = 0;
    bool Collision = false;
    int rTimer = 0;
    int currentLevel = 1;
    bool levelComplete = false;
    Clock levelCompleteTimer;
    bool showLevelScreen = false;
    int chosenPlayer = 0;
    float Speed = 0;
    int vacuum_range = 0;
    
    // Player variables
    float player_x = 500;
    float player_y = 700;
    float offset_x = 0;
    float offset_y = 0;
    float velocityY = 0;
    bool onGround = false;
    bool facingRight = true;
    int enemies_in_bag = 0;
    
    // Powerup variables
    bool ppu_active = true;
    bool rpu_active = true;
    bool elpu_active = true;
    bool spu_active = true;
    int ppu_x = rand() % 1072 + 1;
    int ppu_y = rand() % 832 + 1;
    int rpu_x = rand() % 1072 + 1;
    int rpu_y = rand() % 832 + 1;
    int elpu_x = rand() % 1072 + 1;
    int elpu_y = rand() % 832 + 1;
    int spu_x = rand() % 1072 + 1;
    int spu_y = rand() % 832 + 1;
    
    // Enemy arrays
    float ghost_x[8];
    float ghost_y[8];
    float ghostV_x[8];
    float skeleton_x[4];
    float skeleton_y[4];
    float skeletonV_x[4];
    float chelnov_x[4];
    float chelnov_y[4];
    float chelnovV_x[4];
    bool chelnov_facing_right[4];
    float invisibleman_x[3];
    float invisibleman_y[3];
    float invisiblemanV_x[3];
    float fireball_x[10];
    float fireball_y[10];
    float fireball_vx[10];
    bool fireball_active[10];
    int fireballs_cooldown[4];
    bool enemy_active[19];
    int bagged_enemies[19];
    char bagged_enemy_types[10];
    
    // Shot arrays
    float shot_x[10];
    float shot_y[10];
    float shot_speed[10];
    bool shot_active[10];
    char shot_type[10];
    
    for (int i = 0; i < 10; i++) {
        shot_active[i] = false;
    }
    
    // Textures, Sprites and Text 

    Texture char1Tex, char2Tex, menuBgTex;
    Sprite Player1Sprite, Player2Sprite, menuBgSprite;
    Sprite* chosenCharacter = nullptr;
    
    Texture vacuumTex;
    Sprite vacuumSprite;
    
    Texture tsTex;
    Sprite tsSprite;
    
    Texture level2ScreenTex;
    Sprite level2ScreenSprite;
    
    Texture GhostTexture;
    Sprite GhostSprite[8];
    
    Texture SkeletonTexture;
    Sprite SkeletonSprite[4];
    
    Texture ChelnovTexture;
    Sprite ChelnovSprite[4];
    
    Texture FireballTexture;
    Sprite FireballSprite[10];
    
    Texture InvisibleManTexture;
    Sprite InvisibleManSprite[3];
    
    Texture bgTex;
    Sprite bgSprite;
    
    Texture blockTexture;
    Sprite blockSprite;
    
    Texture ppuTex, rpuTex, elpuTex, spuTex;
    Sprite ppuSprite, rpuSprite, elpuSprite, spuSprite;
    
    Texture ghostShotTexture;
    Texture skeletonShotTexture;
    Texture chelnovShotTexture;
    Texture InvisibleManShotTexture;
    Sprite ghostShotSprite[10];
    Sprite skeletonShotSprite[10];
    Sprite chelnovShotSprite[10];
    Sprite InvisibleManShotSprite[10];
    
    
    Music lvlMusic;
    Music lvl2Music;
    SoundBuffer collisionSoundBuffer;
    Sound collisionSound;
    Font gameFont;
    Text scoreText;
    Text healthText;

    gameFont.loadFromFile("Assets/Font//American Captain.ttf");  // Make sure you have a font file!

    scoreText.setFont(gameFont);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);

    healthText.setFont(gameFont);
    healthText.setCharacterSize(30);
    healthText.setFillColor(Color::Red);
    healthText.setPosition(20, 60);

 
    // Initialize all assets(sprites)
    Sprites_Textures(char1Tex, char2Tex, menuBgTex, Player1Sprite, Player2Sprite, menuBgSprite,
                       vacuumTex, vacuumSprite, tsTex, tsSprite, level2ScreenTex, level2ScreenSprite,
                       GhostTexture, GhostSprite, SkeletonTexture, SkeletonSprite,
                       ChelnovTexture, ChelnovSprite, FireballTexture, FireballSprite,
                       InvisibleManTexture, InvisibleManSprite, bgTex, bgSprite,
                       blockTexture, blockSprite, ppuTex, ppuSprite, rpuTex, rpuSprite,
                       elpuTex, elpuSprite, spuTex, spuSprite,
                       ghostShotTexture, ghostShotSprite, skeletonShotTexture, skeletonShotSprite,
                       chelnovShotTexture, chelnovShotSprite,InvisibleManShotTexture,InvisibleManShotSprite,
                       screen_x, screen_y, ppu_x, ppu_y, rpu_x, rpu_y, elpu_x, elpu_y, spu_x, spu_y);
    
    // Setup music
    lvlMusic.openFromFile("Assets/Sound/muslvl1.ogg");
    lvlMusic.setVolume(20);
    lvlMusic.setLoop(true);
    lvlMusic.play();
    
    lvl2Music.openFromFile("Assets/Sound/muslvl2.ogg");
    lvl2Music.setVolume(20);
    lvl2Music.setLoop(true);

    // After loading lvlMusic and lvl2Music:
    collisionSoundBuffer.loadFromFile("Assets/Sound/collision.ogg");
    collisionSound.setBuffer(collisionSoundBuffer);
    collisionSound.setVolume(50); // Adjust volume as needed
    
    // Create level
    char** lvl = new char*[height];
    for (int i = 0; i < height; i++) lvl[i] = new char[width];
    
    setup_level_1(lvl, height, width,
                 ghost_x, ghost_y, ghostV_x,
                 skeleton_x, skeleton_y, skeletonV_x,
                 GhostSprite, SkeletonSprite,
                 GhostTexture, SkeletonTexture,
                 enemy_active, total_enemies);
    
    Event ev;
    
    // Main game loop
    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                window.close();
        }

        window.clear();

        if (TitleScreenOn)
        {
            handleTitleScreen(window, tsSprite, TitleScreenOn, CharacterSelectOn);
            continue;
        }

        if (CharacterSelectOn)
        {
            handleCharacterSelect(window, menuBgSprite, Player1Sprite, Player2Sprite,
                                CharacterSelectOn, GameOn, chosenPlayer, chosenCharacter,
                                Speed, vacuum_range, player1speed, player2speed,
                                player1range, player2range);
            continue;
        }

        if (showLevelScreen)
        {
            window.draw(level2ScreenSprite);
            window.display();

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                showLevelScreen = false;
                GameOn = true;
                lvl2Music.play();
            }
            continue;
        }

        if (GameOn)
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

            bool vacuum_active = Keyboard::isKeyPressed(Keyboard::Space);

            // Handle player input
            handlePlayerInput(*chosenCharacter, player_x, player_y, velocityY, onGround,
                            Speed, facingRight, jumpStrength, PlayerHeight, cell_size, screen_y);

            // Handle shooting
          static bool sKeyWasPressed = false;
bool sKeyIsPressed = Keyboard::isKeyPressed(Keyboard::S);

if (sKeyIsPressed && !sKeyWasPressed) {  // Only shoot on key press, not hold
    shoot_enemy(player_x, player_y, PlayerWidth, PlayerHeight, facingRight,
                enemies_in_bag, bagged_enemies, bagged_enemy_types,
                shot_x, shot_y, shot_speed, shot_active, shot_type,
                ghostShotSprite, skeletonShotSprite, chelnovShotSprite,InvisibleManShotSprite,
                max_shots);
                }

            // Update enemy movements
            GhostMovement(lvl, ghost_x, ghost_y, ghostV_x, GhostSprite, 8, cell_size, width, height, enemy_active, ghost_start_index);
            SkeletonMovement(lvl, skeleton_x, skeleton_y, skeletonV_x, SkeletonSprite, 4, cell_size, width, height, enemy_active, skeleton_start_index);

            // Vacuum system
           vacuum_pull_enemies(vacuum_active, enemies_in_bag, max_bag_capacity,
                                player_x, player_y, PlayerWidth, PlayerHeight,
                                facingRight, vacuum_range, cell_size,
                                ghost_x, ghost_y, 8, ghost_start_index,
                                skeleton_x, skeleton_y, 4, skeleton_start_index,
                                chelnov_x, chelnov_y, num_chelnov, chelnov_start_index,
                                enemy_active, bagged_enemies, bagged_enemy_types,
                                playerScore);

            // Level 2 specific updates
            if(currentLevel == 2) {
                ChelnovMovement(lvl, chelnov_x, chelnov_y, chelnovV_x, chelnov_facing_right, ChelnovSprite, num_chelnov, cell_size, width, height, enemy_active, chelnov_start_index);
                ChelnovGravity(lvl, chelnov_x, chelnov_y, ChelnovSprite, num_chelnov, cell_size, width, height, enemy_active, chelnov_start_index);
                mechanism_chelnov_and_fireballs(chelnov_x, chelnov_y, chelnov_facing_right,
                                               num_chelnov, fireball_x, fireball_y, 
                                               fireball_vx, fireball_active, 
                                               FireballSprite, fireballs_cooldown, 
                                               fire_rate, num_fireballs, screen_x);
                InvisibleManMovement(lvl, invisibleman_x, invisibleman_y, invisiblemanV_x, InvisibleManSprite, 3, cell_size, width, height, enemy_active, invisibleman_start_index);
            }

            // Handle powerups
            handlePowerups(player_x, player_y, PlayerWidth, PlayerHeight,
                          ppu_active, rpu_active, elpu_active, spu_active,
                          ppu_x, ppu_y, rpu_x, rpu_y, elpu_x, elpu_y, spu_x, spu_y,
                          ppuSprite, rpuSprite, elpuSprite, spuSprite,
                          Speed, playerLives, vacuum_range, playerScore);

            // Handle collisions
            handleCollisions(player_x, player_y, PlayerWidth, PlayerHeight,
            ghost_x, ghost_y, skeleton_x, skeleton_y,
            chelnov_x, chelnov_y, invisibleman_x, invisibleman_y,
            fireball_x, fireball_y, fireball_active,
            enemy_active, Collision, playerLives, rTimer,
            vacuum_active, currentLevel, num_chelnov, num_invisibleman, num_fireballs,
            ghost_start_index, skeleton_start_index, chelnov_start_index, invisibleman_start_index,
            playerScore, collisionSound);

            // Handle game over
            if(playerLives <= 0) {
                handleGameOver(GameOn, TitleScreenOn, currentLevel, levelComplete,
                             lvl2Music, lvlMusic, playerLives,
                             player_x, player_y, velocityY, enemies_in_bag,
                             enemy_active, total_enemies,
                             ghost_x, ghost_y, ghostV_x,
                             skeleton_x, skeleton_y, skeletonV_x,
                             GhostSprite, SkeletonSprite,
                             GhostTexture, SkeletonTexture,
                             chelnov_x, chelnov_y, chelnovV_x, chelnov_facing_right,
                             ChelnovSprite, ChelnovTexture, num_chelnov,
                             fireball_x, fireball_y, fireball_vx, fireball_active,
                             FireballSprite, FireballTexture, num_fireballs, fireballs_cooldown,
                             invisibleman_x, invisibleman_y, invisiblemanV_x,
                             InvisibleManSprite, InvisibleManTexture, num_invisibleman, playerScore);
            }

            // Handle level transition
            handleLevelTransition(levelComplete, levelCompleteTimer, currentLevel,
                                GameOn, showLevelScreen, TitleScreenOn,
                                lvlMusic, lvl2Music,
                                lvl, height, width,
                                ghost_x, ghost_y, ghostV_x,
                                skeleton_x, skeleton_y, skeletonV_x,
                                GhostSprite, SkeletonSprite,
                                GhostTexture, SkeletonTexture,
                                enemy_active, total_enemies,
                                chelnov_x, chelnov_y, chelnovV_x, chelnov_facing_right,
                                ChelnovSprite, ChelnovTexture, num_chelnov,
                                fireball_x, fireball_y, fireball_vx, fireball_active,
                                FireballSprite, FireballTexture, num_fireballs, fireballs_cooldown,
                                invisibleman_x, invisibleman_y, invisiblemanV_x,
                                InvisibleManSprite, InvisibleManTexture, num_invisibleman,
                                player_x, player_y, velocityY, enemies_in_bag, playerLives,total_enemies_level1, total_enemies_level2);

            // Update gravity and physics
            player_gravity(lvl, offset_y, velocityY, onGround, gravity, terminal_Velocity, 
                          player_x, player_y, cell_size, PlayerHeight, PlayerWidth, screen_x, screen_y);

            // Update shots
              update_shots(window, shot_x, shot_y, shot_speed, shot_active, shot_type,
             ghostShotSprite, skeletonShotSprite, chelnovShotSprite, max_shots);

            scoreText.setString("Score: " + to_string(playerScore));
            healthText.setString("Lives: " + to_string(playerLives)); 

            // Render everything
            renderGame(window, lvl, bgTex, bgSprite, blockTexture, blockSprite,
                      height, width, cell_size, *chosenCharacter, vacuumSprite,
                      vacuum_active, player_x, player_y, PlayerWidth, PlayerHeight,
                      facingRight, vacuumTex, GhostSprite, SkeletonSprite,ghostShotSprite,skeletonShotSprite,
                      ChelnovSprite,InvisibleManShotSprite,chelnovShotSprite, FireballSprite, InvisibleManSprite,
                      ppuSprite, rpuSprite, elpuSprite, spuSprite,
                      enemy_active, fireball_active, currentLevel,
                      ghost_start_index, skeleton_start_index, chelnov_start_index,
                      num_chelnov, num_fireballs, invisibleman_start_index, num_invisibleman,shot_active, max_shots, shot_type);  
                      
             window.draw(scoreText);
             window.draw(healthText);            

            window.display();
        }
    }

    // Cleanup
    lvlMusic.stop();
    lvl2Music.stop();
    for (int i = 0; i < height; i++) delete[] lvl[i];
    delete[] lvl;
    
return 0;
}
