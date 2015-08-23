#include <SDL.h>
#include "enemy.h"
#include "texturestorage.h"
#include "common.h"
#include "soundplayer.h"


void Enemy::render(SDL_Renderer* renderer)
{
	angle = angle - 5;
	if (angle == -360) angle = 0;
	if (eType == EnemyType::SPIKEBALL)
	{
		if (gameDifficulty == Difficulty::SECRET) TextureStorage::getInstance().secretEnemyTexture.render(pPosX - pHitbox.radius, pPosY - pHitbox.radius, renderer, NULL, angle);
		else TextureStorage::getInstance().enemyTexture.render(pPosX - pHitbox.radius, pPosY - pHitbox.radius, renderer, NULL, angle);
	}
	else
	{
		if (frameCount % PULSE_CHANGE_DELAY == 0)
		{
			if (isPulsing)
			{
				pulse++;
				pWidth++;
				pHeight++;
			}
			else 
			{
				pulse--;
				pWidth--;
				pHeight--;
			}
			if (pulse == PULSE_LIMIT) isPulsing = false;
			else if (pulse == 0) isPulsing = true;
		}
		if (gameDifficulty != Difficulty::SECRET)
		{
			TextureStorage::getInstance().vortexTexture.setHeight(pHeight);
			TextureStorage::getInstance().vortexTexture.setWidth(pWidth);
			setHitbox();
			pHitbox.radius = pWidth / 2;
			TextureStorage::getInstance().vortexTexture.render(pPosX - pHitbox.radius, pPosY - pHitbox.radius, renderer, NULL, angle);
		}
		else
		{
			TextureStorage::getInstance().secretVortexTexture.setHeight(pHeight);
			TextureStorage::getInstance().secretVortexTexture.setWidth(pWidth);
			setHitbox();
			pHitbox.radius = pWidth / 2;
			TextureStorage::getInstance().secretVortexTexture.render(pPosX - pHitbox.radius, pPosY - pHitbox.radius, renderer, NULL, angle);
		}
	}
}

void Enemy::move(std::vector<SDL_Rect>& walls)
{
	bool isXColliding = false;
	bool isYColliding = false;
	Side side;
	switch (enemyDirection)
	{
	case Direction::UPLEFT:
		pVelX = -pVelocity;
		pVelY = -pVelocity;
		break;
	case Direction::UP:
		pVelX = 0;
		pVelY = -pVelocity;
		break;
	case Direction::UPRIGHT:
		pVelX = pVelocity;
		pVelY = -pVelocity;
		break;
	case Direction::LEFT:
		pVelX = -pVelocity;
		pVelY = 0;
		break;
	case Direction::DOWNLEFT:
		pVelX = -pVelocity;
		pVelY = pVelocity;
		break;
	case Direction::DOWN:
		pVelY = pVelocity;
		pVelX = 0;
		break;
	case Direction::DOWNRIGHT:
		pVelY = pVelocity;
		pVelX = pVelocity;
		break;
	case Direction::RIGHT:
		pVelY = 0;
		pVelX = pVelocity;
		break;
	default:
		break;
	}
	pPosX += pVelX;
	setHitbox();
	int sideCounter = 0;
	bool isSideDeclared = false;
	for (std::vector<SDL_Rect>::iterator it = walls.begin(); it != walls.end(); ++it) {
		if (!isXColliding) isXColliding = checkCollision(pHitbox, *it);
		if (isXColliding && !isSideDeclared)
		{
			isSideDeclared = true;
			side = static_cast<Side>(sideCounter);
		}
		sideCounter++;
	}
	if (isXColliding)
	{
		if (enemyDirection == Direction::LEFT) enemyDirection = Direction::RIGHT;
		else if (enemyDirection == Direction::RIGHT) enemyDirection = Direction::LEFT;
	}
	pPosY += pVelY;
	setHitbox();
	for (std::vector<SDL_Rect>::iterator it = walls.begin(); it != walls.end(); ++it) {
		if (!isYColliding) isYColliding = checkCollision(pHitbox, *it);
	}
	if (isYColliding)
	{
		if (enemyDirection == Direction::UP) enemyDirection = Direction::DOWN;
		else if (enemyDirection == Direction::DOWN) enemyDirection = Direction::UP;
	}


	if (isXColliding && isYColliding)
	{
		switch (enemyDirection)
		{
		case Direction::UPLEFT:
			if (side == Side::UP) enemyDirection = Direction::DOWNLEFT;
			else if(side == Side::LEFT) enemyDirection = Direction::UPRIGHT;
			break;
		case Direction::UPRIGHT:
			if (side == Side::UP) enemyDirection = Direction::DOWNRIGHT;
			else if (side == Side::RIGHT) enemyDirection = Direction::UPLEFT;
			break;
		case Direction::DOWNLEFT:
			if (side == Side::DOWN) enemyDirection = Direction::UPLEFT;
			else if (side == Side::LEFT) enemyDirection = Direction::DOWNRIGHT;
			break;
		case Direction::DOWNRIGHT:
			if (side == Side::DOWN) enemyDirection = Direction::UPRIGHT;
			else if (side == Side::RIGHT) enemyDirection = Direction::DOWNLEFT;
			break;
		default:
			break;
		}
	}
	if (isXColliding || isYColliding) SoundPlayer::getInstance().playEnemyWallHit();
}