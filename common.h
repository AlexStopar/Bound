#ifndef COMMON_H
#define COMMON_H
#include <SDL.h>
#include <SDL_image.h>
#include <vector>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int WALL_WIDTH = 50;
const int SECRET_COIN_WIDTH = 208;
const int COIN_WIDTH = 216;
const int COIN_HEIGHT = 32;
const int PLAYER_WIDTH = 30;
const int PLAYER_HEIGHT = 30;
const int ENEMY_WIDTH = 30;
const int ENEMY_HEIGHT = 30;
const int SKULL_WIDTH = 31;
const int SKULL_HEIGHT = 44;
const int PLAYER_VEL = 5;
const int ENEMY_VEL = 1;
const int VORTEX_LIMIT = 100;
const int COIN_VALUE = 1000;
const int COLLECTIBLE_FRAMES = 6;
const int SECRET_COLLECT_FRAMES = 8;
const int DISPLAY_LIMIT = 60; 

enum class Side {UP, LEFT, RIGHT, DOWN};
extern int score;
extern bool isResetting;
extern bool isQuitting;
extern bool isPaused;
extern int frameCount;

enum class Difficulty {NONE = 0, EASY = 1, MEDIUM = 2, HARD = 4, WHOA = 8, SECRET = 5};
extern Difficulty gameDifficulty;
extern bool isWindowed;
void toggleFullscreen(SDL_Window* window);
std::vector<SDL_Rect> getBoundaries();
void setDifficultyColor(SDL_Renderer* renderer);
void renderWalls(SDL_Renderer* renderer, std::vector<SDL_Rect>& walls);
int resolveCoinFrames();
int resolveCoinWidth();
#endif