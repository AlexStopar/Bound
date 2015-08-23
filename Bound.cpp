#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "common.h"
#include "level.h"
#include "menu.h"
#include "soundplayer.h"
#include "textdraw.h"
#include "highscore.h"
#include "texturestorage.h"

bool init();

void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_NOPARACHUTE) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) printf("Warning: Linear texture filtering not enabled!");

		gWindow = SDL_CreateWindow("Bound - By Alex Stopar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					return false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					return false;
				}
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					return false;
				}
			}
		}
	}
	return true;
}

void close()
{	
	SoundPlayer::getInstance().stopMusic();
	SoundPlayer::getInstance().free();
	TextDraw::getInstance().free();
	TextureStorage::getInstance().free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
}

int main(int argc, char* args[])
{
	if (!init()) printf("Failed to initialize!\n");
	else
	{
		HighScore::getInstance().ReadScores();
		loadMedia(gRenderer);
		while (!isQuitting)
		{
			playMenu(gRenderer, gWindow);
			while (isResetting)
			{
				playLevel(gRenderer, gWindow);
			}
		}
		HighScore::getInstance().WriteScores();
	}
	close();
	return 0;
}