#include "menu.h"
#include <SDL.h>
#include "soundplayer.h"
#include "textdraw.h"
#include "texturestorage.h"
#include "common.h"

void playMenu(SDL_Renderer* renderer, SDL_Window* window)
{
	TextDraw::getInstance().gameOverRise = 0;
	int ballPosition = 0;
	bool isOnDifficultyMenu = false;
	bool isOnHighScoreMenu = false;
	int currentMenuSize = 0;
	isResetting = true;
	while (!isQuitting)
	{	
		if(!isOnDifficultyMenu) currentMenuSize = TextDraw::getInstance().menuTexture.size();
		else currentMenuSize = TextDraw::getInstance().difficultyTexture.size() + 1;
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				isQuitting = true;
				isResetting = false;
			}
			else if (e.type == SDL_KEYDOWN) 
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					toggleFullscreen(window);
					break;
				case SDLK_UP:
					if (ballPosition == 0) ballPosition = currentMenuSize-1;
					else ballPosition--;
					SoundPlayer::getInstance().playMenuSwitch();
					break;
				case SDLK_DOWN:
					if (ballPosition == currentMenuSize-1) ballPosition = 0;
					else ballPosition++;
					SoundPlayer::getInstance().playMenuSwitch();
					break;
				case SDLK_RETURN:
					if (!isOnHighScoreMenu){
						switch (ballPosition)
						{
						case 0:
							if (isOnDifficultyMenu)
							{
								gameDifficulty = Difficulty::EASY;
								return;
							}
							else isOnDifficultyMenu = true;
							break;
						case 1:
							if (isOnDifficultyMenu)
							{
								gameDifficulty = Difficulty::MEDIUM;
								return;
							}
							else isOnHighScoreMenu = true;
							break;
						case 2:
							if (isOnDifficultyMenu)
							{
								gameDifficulty = Difficulty::HARD;
								return;
							}
							else {
								isQuitting = true;
								isResetting = false;
							}
							break;
						case 3:
							gameDifficulty = Difficulty::WHOA;
							return;
						default:
							gameDifficulty = Difficulty::SECRET;
							return;
							break;
						}
					}
					else isOnHighScoreMenu = false;
					SoundPlayer::getInstance().playMenuPick();
					break;
			    }
			}	
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_Rect background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderFillRect(renderer, &background);

		if (!isOnHighScoreMenu)
		{
			TextDraw::getInstance().renderMenuTitle(renderer);
			if (!isOnDifficultyMenu) TextDraw::getInstance().renderMenu(renderer, ballPosition, false);
			else TextDraw::getInstance().renderMenu(renderer, ballPosition, true);
			TextDraw::getInstance().renderInstructions(renderer, false);
		}
		else
		{
			TextDraw::getInstance().renderHighScoreMenu(renderer);
			TextDraw::getInstance().renderInstructions(renderer, true);
		}
		SDL_RenderPresent(renderer);
	}
	
}