#include <vector>
#include <SDL.h>
#include "texturestorage.h"
#include "skull.h"

void Skull::move(std::vector<SDL_Rect>& walls)
{
	pPosX += 3;
	if (goingUp) pPosY -= 4;
	else pPosY += 4;
	upTime++;
	if (upTime == 10) goingUp = false;
}

void Skull::render(SDL_Renderer* renderer)
{
	TextureStorage::getInstance().skullTexture.render(pPosX - pHitbox.radius, pPosY - pHitbox.radius, renderer);
}

void Skull::setXY(int x, int y)
{
	pPosX = x;
	pPosY = y;
}