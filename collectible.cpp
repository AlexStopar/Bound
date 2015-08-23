#include <SDL.h>
#include <SDL_image.h>
#include <random>
#include "common.h"
#include "texturestorage.h"
#include "collectible.h"
#include "textdraw.h"
#include "player.h"
#include "soundplayer.h"

void Collectible::move(Player& player, int newX, int newY)
{
	if (checkCollision(pHitbox, player.getHitbox()))
	{
		isHit = true;
		pPosX = newX;
		pPosY = newY;
		setHitbox();
		score += COIN_VALUE;
		if (score % 25000 == 0)
		{
			player.playerLives.changeLifeCount(-1);
			SoundPlayer::getInstance().playCollect(true);
		}
		else SoundPlayer::getInstance().playCollect(false);
	}
}

void Collectible::render(SDL_Renderer* renderer)
{
	SDL_Rect* currentClip = &collectibleClips[frame / resolveCoinSpeed()];
	if(gameDifficulty != Difficulty::SECRET) TextureStorage::getInstance().coinTexture.render(pPosX - 
		pHitbox.radius, pPosY - pHitbox.radius, renderer, currentClip);
	else TextureStorage::getInstance().secretCoinTexture.render(pPosX -
		pHitbox.radius, pPosY - pHitbox.radius, renderer, currentClip);
	frame++;
	if (frame/resolveCoinSpeed() == resolveCoinFrames()-1) frame = 0;
}

int Collectible::resolveCoinSpeed()
{
	if (gameDifficulty == Difficulty::SECRET) return SECRET_COIN_SPEED;
	else return COIN_SPEED;
}
