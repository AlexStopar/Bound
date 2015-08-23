#ifndef TEXTURESTORAGE_H
#define TEXTURESTORAGE_H
#include "texture.h"
#include <SDL.h>

class TextureStorage
{
public:
	static TextureStorage& getInstance()
	{
		static TextureStorage instance;
		return instance;
	}
	Texture playerTexture;
	Texture bgTexture;
	Texture coinTexture;
	Texture enemyTexture;
	Texture secretEnemyTexture;
	Texture secretVortexTexture;
	Texture secretCoinTexture;
	Texture vortexTexture;
	Texture skullTexture;
	bool loadTextures(SDL_Renderer* renderer);
	void setDifficultyBackground(SDL_Renderer* renderer);
	void free();
private:
	TextureStorage() {};
	TextureStorage(TextureStorage const&);
	void operator=(TextureStorage const&);
};


#endif