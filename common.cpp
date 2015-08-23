#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "common.h"

bool isWindowed = true;
bool isResetting = true;
bool isQuitting = false;
int score = 0;
Difficulty gameDifficulty = Difficulty::WHOA;

std::vector<SDL_Rect> getBoundaries()
{
	std::vector<SDL_Rect> walls;
	walls.push_back({ 0, 0, SCREEN_WIDTH, WALL_WIDTH });
	walls.push_back({ 0, 0, WALL_WIDTH, SCREEN_HEIGHT });
	walls.push_back({ SCREEN_WIDTH - WALL_WIDTH, 0, WALL_WIDTH, SCREEN_HEIGHT });
	walls.push_back({ 0, SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH, WALL_WIDTH });
	return walls;
}
void renderWalls(SDL_Renderer* renderer, std::vector<SDL_Rect>& walls)
{
	setDifficultyColor(renderer);
	for (std::vector<SDL_Rect>::iterator it = walls.begin(); it != walls.end(); ++it) {
		SDL_RenderFillRect(renderer, &(*it));
	}

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

	SDL_RenderDrawLine(renderer, 0, 0, WALL_WIDTH, WALL_WIDTH);
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH - WALL_WIDTH, WALL_WIDTH, SCREEN_WIDTH, 0);
	SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT, WALL_WIDTH, SCREEN_HEIGHT - WALL_WIDTH);
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH - WALL_WIDTH, SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_RenderDrawLine(renderer, WALL_WIDTH, WALL_WIDTH, SCREEN_WIDTH - WALL_WIDTH, WALL_WIDTH);
	SDL_RenderDrawLine(renderer, WALL_WIDTH, WALL_WIDTH, WALL_WIDTH, SCREEN_HEIGHT - WALL_WIDTH);
	SDL_RenderDrawLine(renderer, SCREEN_WIDTH - WALL_WIDTH, WALL_WIDTH, SCREEN_WIDTH - WALL_WIDTH, SCREEN_HEIGHT - WALL_WIDTH);
	SDL_RenderDrawLine(renderer, WALL_WIDTH, SCREEN_HEIGHT - WALL_WIDTH, SCREEN_WIDTH - WALL_WIDTH, SCREEN_HEIGHT - WALL_WIDTH);
	
}

void setDifficultyColor(SDL_Renderer* renderer)
{
	switch (gameDifficulty)
	{
	case Difficulty::EASY:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x33, 0x66, 0xFF);
		break;
	case Difficulty::MEDIUM:
		SDL_SetRenderDrawColor(renderer, 0xDC, 0x14, 0x3C, 0xFF);
		break;
	case Difficulty::HARD:
		SDL_SetRenderDrawColor(renderer, 0xD2, 0x69, 0x1E, 0xFF);
		break;
	case Difficulty::WHOA:
		SDL_SetRenderDrawColor(renderer, 0x69, 0x69, 0x69, 0x69);
		break;
	default:
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		break;
	}
}
void toggleFullscreen(SDL_Window* window)
{
	if (isWindowed)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		isWindowed = false;
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		isWindowed = true;
	}
}

int resolveCoinFrames()
{
	if (gameDifficulty != Difficulty::SECRET) return COLLECTIBLE_FRAMES;
	else return SECRET_COLLECT_FRAMES;
}

int resolveCoinWidth()
{
	if (gameDifficulty != Difficulty::SECRET) return COIN_WIDTH;
	else return SECRET_COIN_WIDTH;
}


