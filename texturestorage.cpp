#include "texturestorage.h"
#include "texture.h"
#include "common.h"
#include <SDL.h>

bool TextureStorage::loadTextures(SDL_Renderer* renderer)
{
	if (!playerTexture.loadFromFile("ball.png", renderer))
	{
		printf("Failed to load ball texture!\n");
		return false;
	}
	if (!coinTexture.loadFromFile("coin.png", renderer))
	{
		printf("Failed to load collectible texture!\n");
		return false;
	}
	if (!enemyTexture.loadFromFile("enemy.png", renderer))
	{
		printf("Failed to load enemy texture!\n");
		return false;
	}
	skullTexture.loadFromFile("skull.png", renderer);
	secretEnemyTexture.loadFromFile("secretEnemy.png", renderer);
	secretVortexTexture.loadFromFile("secretVortex.png", renderer);
	secretCoinTexture.loadFromFile("secretCoin.png", renderer);
	vortexTexture.loadFromFile("vortex.png", renderer);
	return true;
}

void TextureStorage::free()
{
	playerTexture.free();
	bgTexture.free();
	coinTexture.free();
	enemyTexture.free();
	skullTexture.free();
	secretEnemyTexture.free();
	secretVortexTexture.free();
	secretCoinTexture.free();
	vortexTexture.free();
}

void TextureStorage::setDifficultyBackground(SDL_Renderer* renderer)
{
	switch (gameDifficulty)
	{
	case Difficulty::EASY:
		bgTexture.loadFromFile("bg1.png", renderer);
		break;
	case Difficulty::MEDIUM:
		bgTexture.loadFromFile("bg2.png", renderer);
		break;
	case Difficulty::HARD:
		bgTexture.loadFromFile("bg3.png", renderer);
		break;
	case Difficulty::WHOA:
		bgTexture.loadFromFile("bg4.png", renderer);
		break;
	default:
		bgTexture.loadFromFile("bg5.png", renderer);
		break;
	}
	bgTexture.setHeight(SCREEN_HEIGHT);
	bgTexture.setWidth(SCREEN_WIDTH);
}
