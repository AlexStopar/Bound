#ifndef LEVEL_H
#define LEVEL_H
#include <SDL.h>
#include "texture.h"
#include "enemy.h"
#include "player.h"

bool loadMedia(SDL_Renderer* renderer);
void setDifficultyBackground(SDL_Renderer* renderer);
void playLevel(SDL_Renderer* renderer, SDL_Window* window);
void reset();

#endif 
