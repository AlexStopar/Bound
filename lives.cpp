#include "lives.h"
#include <SDL.h>
#include "texturestorage.h"
#include "common.h"

Lives::Lives()
{
	livesLeft = 3;
}

void Lives::changeLifeCount(int amount)
{
	livesLeft -= amount;
}

int Lives::getLives()
{
	return livesLeft;
}

void Lives::renderLives(SDL_Renderer* renderer)
{
	angle += 5;
	if (angle == 360) angle = 0;
	int startingPosition = WALL_WIDTH;
	for (int i = 0; i < livesLeft - 1; i++)
	{
		TextureStorage::getInstance().playerTexture.render(startingPosition, SCREEN_HEIGHT - 
			(TextureStorage::getInstance().playerTexture.getHeight() * 3)/2, renderer, NULL, angle);
		startingPosition += TextureStorage::getInstance().playerTexture.getWidth();
	}
}