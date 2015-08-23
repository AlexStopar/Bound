#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "player.h"
#include "common.h"
#include "texturestorage.h"
#include "collision.h"
#include "movingobj.h"
#include "soundplayer.h"
#include "enemy.h"

void Player::handleEvent(SDL_Event& e) 
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: pVelY -= pVelocity; break;
		case SDLK_DOWN: pVelY += pVelocity; break;
		case SDLK_LEFT: pVelX -= pVelocity; break;
		case SDLK_RIGHT: pVelX += pVelocity; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: pVelY += pVelocity; break;
		case SDLK_DOWN: pVelY -= pVelocity; break;
		case SDLK_LEFT: pVelX += pVelocity; break;
		case SDLK_RIGHT: pVelX -= pVelocity; break;
		}
	}
}

void Player::move(std::vector<SDL_Rect>& walls, std::vector<Enemy>& enemies, Skull& skull)
{
	bool isColliding = false;	
	pPosX += pVelX;
	setHitbox();
	for (std::vector<SDL_Rect>::iterator it = walls.begin(); it != walls.end(); ++it) {
		if (!isColliding) isColliding = checkCollision(pHitbox, *it);
	}

	if ((pPosX < 0) || (pPosX + pWidth > SCREEN_WIDTH) || isColliding)
	{
		pPosX -= pVelX;
		setHitbox();
		SoundPlayer::getInstance().playWallHit();
	}

	isColliding = false;
	pPosY += pVelY;
	setHitbox();

	for (std::vector<SDL_Rect>::iterator it = walls.begin(); it != walls.end(); ++it) {
		if (!isColliding) isColliding = checkCollision(pHitbox, *it);		
	}

	if ((pPosY < 0) || (pPosY + pHeight > SCREEN_HEIGHT) || isColliding)
	{
		pPosY -= pVelY;
		SoundPlayer::getInstance().playWallHit();
		setHitbox();
	}
	
	if (invincibilityCount == FULL_INVINCIBILITY_COUNT)
	{
		for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
			if (checkCollision(pHitbox, it->getHitbox()))
			{
				if ((it->eType == EnemyType::SPIKEBALL && gameDifficulty != Difficulty::SECRET) || 
					(it->eType == EnemyType::VORTEX && gameDifficulty == Difficulty::SECRET))
				{
					playerLives.changeLifeCount(1);
					invincibilityCount = 0;
					if (playerLives.getLives() == 0) die(skull);
					else SoundPlayer::getInstance().playLoseLife();
				}
				else
				{
					std::random_device rd;
					std::mt19937 eng(rd());
					std::uniform_int_distribution<> randomX(2 * WALL_WIDTH, SCREEN_WIDTH - (2 * WALL_WIDTH));
					std::uniform_int_distribution<> randomY(2 * WALL_WIDTH, SCREEN_HEIGHT - (2 * WALL_WIDTH));
					pPosX = randomX(eng);
					pPosY = randomY(eng);
					SoundPlayer::getInstance().playWarp();
				}
				
			}
		}
	}
	else invincibilityCount++;
}

void Player::render(SDL_Renderer* renderer)
{
	angle = angle + 5;
	if (angle == 360) angle = 0;
	if (invincibilityCount == FULL_INVINCIBILITY_COUNT || invincibilityCount % 2 != 0) 
		TextureStorage::getInstance().playerTexture.render(pPosX - pHitbox.radius, 
		pPosY - pHitbox.radius, renderer, NULL, angle);
	playerLives.renderLives(renderer);
}

void Player::die(Skull& skull)
{
	skull.setXY(pPosX, pPosY);
	SoundPlayer::getInstance().playDie();
	isDead = true;
}