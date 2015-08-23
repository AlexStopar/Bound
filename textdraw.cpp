#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include "texture.h"
#include "common.h"
#include "textdraw.h"
#include "highscore.h"
#include "texturestorage.h"
#include "soundplayer.h"

TTF_Font* titleFont = NULL;
TTF_Font* scoreFont = NULL;
TTF_Font* gainFont = NULL;
TTF_Font* congratsFont = NULL;
TTF_Font* gameOverFont = NULL;
TTF_Font* menuTitleFont = NULL;
Texture titleTexture;
Texture gainTexture;
Texture gameOverTexture;
Texture retryTexture;
Texture menuTitleTexture;
Texture congratsTexture;
Texture inputTexture;
Texture pauseTexture;
Texture highScoreTitleTexture;
Texture instructionTexture;
Texture newLifeTexture;
SDL_Rect gameOverRect;
SDL_Color textColor = { 255, 255, 255 };
SDL_Color gainColor = { 0, 255, 255 };
int angle = 0;
bool TextDraw::loadText(SDL_Renderer* renderer)
{
	titleFont = TTF_OpenFont("metalord.ttf", 36);
	scoreFont = TTF_OpenFont("metalord.ttf", 28);
	gainFont = TTF_OpenFont("metalord.ttf", 16);
	gameOverFont = TTF_OpenFont("metalord.ttf", 77);
	menuTitleFont = TTF_OpenFont("metalord.ttf", 120);
	congratsFont = TTF_OpenFont("metalord.ttf", 55);

	if (titleFont == NULL || scoreFont == NULL || gainFont == NULL || gameOverFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	SDL_Color gameOverColor = { 136, 0, 0 };
	if (!titleTexture.loadFromRenderedText("BOUND", textColor, renderer, titleFont) || 
		!gainTexture.loadFromRenderedText(std::to_string(COIN_VALUE), gainColor, renderer, gainFont)||
		!gameOverTexture.loadFromRenderedText("DEATH IS UPON YOU", gameOverColor, renderer, gameOverFont) ||
		!retryTexture.loadFromRenderedText("Will you retry? Y/N", gameOverColor, renderer, titleFont) )
	{
		printf("Failed to render text texture!\n");
		return false;
	}
	menuTitleTexture.loadFromRenderedText("BOUND", textColor, renderer, menuTitleFont);
	pauseTexture.loadFromRenderedText("PAUSE", textColor, renderer, titleFont);
	congratsTexture.loadFromRenderedText("NEW RECORD! ENTER INITIALS", gainColor, renderer, congratsFont);
	newLifeTexture.loadFromRenderedText("Get coins for 1000 points. 25000 for new life.", gainColor, renderer, scoreFont);
	highScoreTitleTexture.loadFromRenderedText("HIGH SCORES", textColor, renderer, menuTitleFont);
	for (int i = 0; i < 3; i++)
	{
		menuTexture.push_back(Texture());
	}
	for (int i = 0; i < 4; i++)
	{
		difficultyTexture.push_back(Texture());
	}
	for (int i = 0; i < 6; i++)
	{
		easyScoreTexture.push_back(Texture());
	}
	for (int i = 0; i < 6; i++)
	{
		mediumScoreTexture.push_back(Texture());
	}
	for (int i = 0; i < 6; i++)
	{
		hardScoreTexture.push_back(Texture());
	}
	for (int i = 0; i < 6; i++)
	{
		whoaScoreTexture.push_back(Texture());
	}
	menuTexture[0].loadFromRenderedText("NEW GAME", textColor, renderer, scoreFont);
	menuTexture[1].loadFromRenderedText("VIEW HIGH SCORES", textColor, renderer, scoreFont);
	menuTexture[2].loadFromRenderedText("EXIT", textColor, renderer, scoreFont);
	difficultyTexture[0].loadFromRenderedText("EASY", textColor, renderer, scoreFont);
	difficultyTexture[1].loadFromRenderedText("MEDIUM", textColor, renderer, scoreFont);
	difficultyTexture[2].loadFromRenderedText("HARD", textColor, renderer, scoreFont);
	difficultyTexture[3].loadFromRenderedText("WHOA", textColor, renderer, scoreFont);
	easyScoreTexture[0].loadFromRenderedText("EASY", textColor, renderer, scoreFont);
	mediumScoreTexture[0].loadFromRenderedText("MEDIUM", textColor, renderer, scoreFont);
	hardScoreTexture[0].loadFromRenderedText("HARD", textColor, renderer, scoreFont);
	whoaScoreTexture[0].loadFromRenderedText("WHOA", textColor, renderer, scoreFont);
	return true;
}

void TextDraw::renderHUD(SDL_Renderer* renderer)
{
	titleTexture.render(WALL_WIDTH, 0, renderer);
	SDL_Color textColor = { 255, 255, 255 };
	Texture scoreTexture;
	std::stringstream scoreText;
	scoreText.str("");
	scoreText << "Score: " << score;
	scoreTexture.loadFromRenderedText(scoreText.str(), textColor, renderer, scoreFont);
	scoreTexture.render((2 * WALL_WIDTH) + titleTexture.getWidth(), 0, renderer);
	scoreTexture.free();
}

void TextDraw::renderScoreGain(int x, int y, SDL_Renderer* renderer)
{
	gainTexture.render(x, y, renderer);
}

void TextDraw::renderGameOver(SDL_Renderer* renderer, bool isHighScore, std::string inputText)
{
	
	if (!isHighScore)
	{		
		gameOverRect = { WALL_WIDTH, SCREEN_HEIGHT - gameOverRise,
			SCREEN_WIDTH - (2 * WALL_WIDTH), gameOverTexture.getHeight() + retryTexture.getHeight() };
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &gameOverRect);
		gameOverTexture.render(WALL_WIDTH, SCREEN_HEIGHT - gameOverRise, renderer);
		retryTexture.render(SCREEN_WIDTH / 3 - WALL_WIDTH, SCREEN_HEIGHT - gameOverRise + gameOverTexture.getHeight(), renderer);
		if (gameOverRise != (SCREEN_HEIGHT / 2) + WALL_WIDTH) gameOverRise += 2;
	}
	else
	{
		gameOverRect = { WALL_WIDTH, SCREEN_HEIGHT - gameOverRise,
			SCREEN_WIDTH - (2 * WALL_WIDTH), congratsTexture.getHeight() + retryTexture.getHeight() };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer, &gameOverRect);
		congratsTexture.render(WALL_WIDTH, SCREEN_HEIGHT - gameOverRise, renderer);
		inputTexture.loadFromRenderedText(inputText, gainColor, renderer, titleFont);
		inputTexture.render(SCREEN_WIDTH / 2 - WALL_WIDTH, SCREEN_HEIGHT - gameOverRise + congratsTexture.getHeight(), renderer);
		if (gameOverRise != (SCREEN_HEIGHT / 2) + WALL_WIDTH) gameOverRise += 2;
	}
}

void TextDraw::renderMenuTitle(SDL_Renderer* renderer)
{
	menuTitleTexture.render(SCREEN_WIDTH/4, gameOverRise, renderer);
	if (gameOverRise == (SCREEN_HEIGHT / 3) - WALL_WIDTH - 1
		|| gameOverRise == (SCREEN_HEIGHT / 3) - WALL_WIDTH - 2) SoundPlayer::getInstance().playTitleDrop();
	if (gameOverRise != (SCREEN_HEIGHT / 3)- WALL_WIDTH) gameOverRise += 2;
}

void TextDraw::renderMenu(SDL_Renderer* renderer, int ballPosition, bool isOnDifficultyMenu)
{
	angle = angle + 5;
	if (angle == 360) angle = 0;
	if (!isOnDifficultyMenu)
	{
		for (size_t i = 0; i < menuTexture.size(); i++)
		{
			menuTexture[i].render(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2 + WALL_WIDTH * i, renderer);
		}
	}
	else
	{
		for (size_t i = 0; i < difficultyTexture.size(); i++)
		{
			difficultyTexture[i].render(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2 + WALL_WIDTH * i, renderer);
		}
	}
	TextureStorage::getInstance().playerTexture.render((SCREEN_WIDTH / 3) - PLAYER_WIDTH, SCREEN_HEIGHT / 2 + WALL_WIDTH * ballPosition, renderer, NULL, angle);
}

void TextDraw::renderInstructions(SDL_Renderer* renderer, bool isOnHighScoreMenu)
{
	if (isOnHighScoreMenu)
	{
		instructionTexture.loadFromRenderedText("Press enter to exit high scores.", textColor, renderer, scoreFont);
		instructionTexture.render(WALL_WIDTH, SCREEN_HEIGHT - instructionTexture.getHeight(), renderer);
	}
	else
	{
		instructionTexture.loadFromRenderedText("Use arrow keys to move ball and enter to select.", textColor, renderer, scoreFont);
		instructionTexture.render(WALL_WIDTH * 2, SCREEN_HEIGHT - (2 * instructionTexture.getHeight()), renderer);
		newLifeTexture.render(WALL_WIDTH * 2, SCREEN_HEIGHT - instructionTexture.getHeight(), renderer);
	}
	
}

void TextDraw::renderPause(SDL_Renderer* renderer)
{
	pauseTexture.render((SCREEN_WIDTH / 2) - pauseTexture.getWidth() / 2, (SCREEN_HEIGHT / 2) - pauseTexture.getHeight(), renderer);
}

void TextDraw::renderHighScoreMenu(SDL_Renderer* renderer)
{
	loadHighScoreText(renderer);
	int startingPoint = highScoreTitleTexture.getHeight();
	highScoreTitleTexture.render(WALL_WIDTH, 0, renderer);
	for (std::vector<Texture>::iterator it = easyScoreTexture.begin(); it != easyScoreTexture.end(); ++it) {
		it->render(WALL_WIDTH, startingPoint, renderer);
		startingPoint += easyScoreTexture[0].getHeight();
	}	
	for (std::vector<Texture>::iterator it = mediumScoreTexture.begin(); it != mediumScoreTexture.end(); ++it) {
		it->render(WALL_WIDTH, startingPoint, renderer);
		startingPoint += mediumScoreTexture[0].getHeight();
	}
	startingPoint = highScoreTitleTexture.getHeight();
	for (std::vector<Texture>::iterator it = hardScoreTexture.begin(); it != hardScoreTexture.end(); ++it) {
		it->render(SCREEN_WIDTH/2 + WALL_WIDTH, startingPoint, renderer);
		startingPoint += hardScoreTexture[0].getHeight();
	}
	for (std::vector<Texture>::iterator it = whoaScoreTexture.begin(); it != whoaScoreTexture.end(); ++it) {
		it->render(SCREEN_WIDTH / 2 + WALL_WIDTH, startingPoint, renderer);
		startingPoint += whoaScoreTexture[0].getHeight();
	}

}

void TextDraw::loadHighScoreText(SDL_Renderer* renderer)
{
	for (int i = 1; i < 6; i++)
	{
		easyScoreTexture[i].loadFromRenderedText(HighScore::getInstance().getEasyScores()[i - 1].first +
			" " + std::to_string(HighScore::getInstance().getEasyScores()[i - 1].second), textColor, renderer, scoreFont);
	}
	for (int i = 1; i < 6; i++)
	{
		mediumScoreTexture[i].loadFromRenderedText(HighScore::getInstance().getMediumScores()[i - 1].first +
			" " + std::to_string(HighScore::getInstance().getMediumScores()[i - 1].second), textColor, renderer, scoreFont);
	}
	for (int i = 1; i < 6; i++)
	{
		hardScoreTexture[i].loadFromRenderedText(HighScore::getInstance().getHardScores()[i - 1].first +
			" " + std::to_string(HighScore::getInstance().getHardScores()[i - 1].second), textColor, renderer, scoreFont);
	}
	for (int i = 1; i < 6; i++)
	{
		whoaScoreTexture[i].loadFromRenderedText(HighScore::getInstance().getWhoaScores()[i - 1].first +
			" " + std::to_string(HighScore::getInstance().getWhoaScores()[i - 1].second), textColor, renderer, scoreFont);
	}
}

void TextDraw::free()
{
	titleTexture.free();
	gainTexture.free();
	gameOverTexture.free();
	retryTexture.free();
	menuTitleTexture.free();
	congratsTexture.free();
	inputTexture.free();
	instructionTexture.free();
	newLifeTexture.free();
	pauseTexture.free();
	highScoreTitleTexture.free();
	freeVector(menuTexture);
	freeVector(difficultyTexture);
	freeVector(easyScoreTexture);
	freeVector(mediumScoreTexture);
	freeVector(hardScoreTexture);
	freeVector(whoaScoreTexture);
	freeFonts();
	gameOverRise = 0;
}

void TextDraw::freeVector(std::vector<Texture>& vecTex)
{
	for (std::vector<Texture>::iterator it = vecTex.begin(); it != vecTex.end(); ++it) {
		it->free();
	}
}

void TextDraw::freeFonts()
{
	TTF_CloseFont(titleFont);
	TTF_CloseFont(scoreFont);
	TTF_CloseFont(gainFont);
	TTF_CloseFont(congratsFont);
	TTF_CloseFont(gameOverFont);
	TTF_CloseFont(menuTitleFont);
	titleFont = NULL;
	scoreFont = NULL;
	gainFont = NULL;
	congratsFont = NULL;
	gameOverFont = NULL;
	menuTitleFont = NULL;
}