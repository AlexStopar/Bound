#ifndef TEXTDRAW_H
#define TEXTDRAW_H
#include <vector>
#include <string>
#include "texture.h"

class TextDraw
{
public:
	static TextDraw& getInstance()
	{
		static TextDraw instance;
		return instance;
	}
	int gameOverRise = 0;
	std::vector<Texture> menuTexture;
	std::vector<Texture> difficultyTexture;
	std::vector<Texture> easyScoreTexture;
	std::vector<Texture> mediumScoreTexture;
	std::vector<Texture> hardScoreTexture;
	std::vector<Texture> whoaScoreTexture;
	bool loadText(SDL_Renderer* renderer);
	void loadHighScoreText(SDL_Renderer* renderer);
	void renderPause(SDL_Renderer* renderer);
	void renderHUD(SDL_Renderer* renderer);
	void renderGameOver(SDL_Renderer* renderer, bool isHighScore, std::string inputText);
	void renderMenuTitle(SDL_Renderer* renderer);
	void renderHighScoreMenu(SDL_Renderer* renderer);
	void renderMenu(SDL_Renderer* renderer, int ballPosition, bool isOnDifficultyMenu);
	void renderInstructions(SDL_Renderer* renderer, bool isOnHighScoreMenu);
	void renderScoreGain(int x, int y, SDL_Renderer* renderer);
	void free();
private:
	TextDraw() {};
	TextDraw(TextDraw const&);
	void operator=(TextDraw const&);
	void freeFonts();
	void freeVector(std::vector<Texture>& vecTex);
};

#endif