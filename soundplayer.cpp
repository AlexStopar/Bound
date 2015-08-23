#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "soundplayer.h"
#include "common.h"

Mix_Music* easyTheme = NULL;
Mix_Music* mediumTheme = NULL;
Mix_Music* hardTheme = NULL;
Mix_Music* whoaTheme = NULL;
Mix_Music* secretTheme = NULL;
Mix_Chunk* hitSound = NULL;
Mix_Chunk* collectSound = NULL;
Mix_Chunk* enemyHitSound = NULL;
Mix_Chunk* dieSound = NULL;
Mix_Chunk* loseLifeSound = NULL;
Mix_Chunk* gainLifeSound = NULL;
Mix_Chunk* menuPickSound = NULL;
Mix_Chunk* menuSwitchSound = NULL;
Mix_Chunk* titleDropSound = NULL;
Mix_Chunk* warpSound = NULL;
Mix_Chunk* highScoreSound = NULL;
Mix_Chunk* pauseSound = NULL;

bool SoundPlayer::loadSounds()
{
	easyTheme = Mix_LoadMUS("easyTheme.wav");
	mediumTheme = Mix_LoadMUS("mediumTheme.wav");
	hardTheme = Mix_LoadMUS("hardTheme.wav");
	whoaTheme = Mix_LoadMUS("whoaTheme.wav");
	secretTheme = Mix_LoadMUS("secretTheme.wav");
	if (easyTheme == NULL || mediumTheme == NULL || hardTheme == NULL || whoaTheme == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	dieSound = Mix_LoadWAV("dieSound.wav");
	hitSound = Mix_LoadWAV("hitSound.wav");
	pauseSound = Mix_LoadWAV("pauseSound.wav");
	loseLifeSound = Mix_LoadWAV("loseLifeSound.wav");
	gainLifeSound = Mix_LoadWAV("gainLifeSound.wav");
	highScoreSound = Mix_LoadWAV("highScoreSound.wav");
	warpSound = Mix_LoadWAV("warpSound.wav");
	if (hitSound == NULL || dieSound == NULL || loseLifeSound == NULL || gainLifeSound == NULL)
	{
		printf("Failed to load hit/die sound effects! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	collectSound = Mix_LoadWAV("collectSound.wav");
	if (collectSound == NULL)
	{
		printf("Failed to load collect sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	menuPickSound = Mix_LoadWAV("menuPickSound.wav");
	menuSwitchSound = Mix_LoadWAV("menuSwitchSound.wav");
	titleDropSound = Mix_LoadWAV("titleDropSound.wav");
	enemyHitSound = Mix_LoadWAV("enemyHitSound.wav");
	if (enemyHitSound == NULL)
	{
		printf("Failed to load collect sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	return true;
}

void SoundPlayer::playMusic()
{	
	switch (gameDifficulty)
	{
	case Difficulty::EASY:
		Mix_VolumeMusic(EASY_VOLUME);
		Mix_PlayMusic(easyTheme, -1);
		break;
	case Difficulty::MEDIUM:
		Mix_PlayMusic(mediumTheme, -1);
		break;
	case Difficulty::HARD:
		Mix_PlayMusic(hardTheme, -1);
		break;
	case Difficulty::WHOA:
		Mix_PlayMusic(whoaTheme, -1);
		break;
	default:
		Mix_PlayMusic(secretTheme, -1);
		break;
	}
}

void SoundPlayer::pauseMusic()
{
	if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
	else Mix_PauseMusic();
}

void SoundPlayer::stopMusic()
{
	Mix_HaltMusic();
}

void SoundPlayer::playWarp()
{
	Mix_PlayChannel(5, warpSound, 0);
}

void SoundPlayer::playWallHit()
{
	Mix_PlayChannel(1, hitSound, 0);
}

void SoundPlayer::playEnemyWallHit()
{
	Mix_VolumeChunk(enemyHitSound, SOUND_EFFECT_VOLUME);
	Mix_PlayChannel(2, enemyHitSound, 0);
}

void SoundPlayer::playLoseLife()
{
	Mix_PlayChannel(3, loseLifeSound, 0);
}

void SoundPlayer::playTitleDrop()
{
	Mix_PlayChannel(-1, titleDropSound, 0);
}

void SoundPlayer::playMenuPick()
{
	Mix_PlayChannel(-1, menuPickSound, 0);
}

void SoundPlayer::playMenuSwitch()
{
	Mix_PlayChannel(-1, menuSwitchSound, 0);
}
void SoundPlayer::playCollect(bool isLifeGained)
{
	Mix_VolumeChunk(collectSound, SOUND_EFFECT_VOLUME);
	if (!isLifeGained) Mix_PlayChannel(6, collectSound, 0);
	else Mix_PlayChannel(6, gainLifeSound, 0);
}

void SoundPlayer::playDie()
{
	Mix_PlayChannel(3, dieSound, 0);
}

void SoundPlayer::playHighScore()
{
	Mix_PlayChannel(4, highScoreSound, 0);
}

void SoundPlayer::playPause()
{
	Mix_PlayChannel(4, pauseSound, 0);
}

void SoundPlayer::free()
{
	Mix_FreeMusic(easyTheme);
	Mix_FreeMusic(mediumTheme);
	Mix_FreeMusic(hardTheme);
	Mix_FreeMusic(whoaTheme);
	Mix_FreeMusic(secretTheme);
	Mix_FreeChunk(hitSound);
	Mix_FreeChunk(collectSound);
	Mix_FreeChunk(enemyHitSound);
	Mix_FreeChunk(dieSound);
	Mix_FreeChunk(loseLifeSound);
	Mix_FreeChunk(gainLifeSound);
	Mix_FreeChunk(menuPickSound);
	Mix_FreeChunk(menuSwitchSound);
	Mix_FreeChunk(titleDropSound);
	Mix_FreeChunk(highScoreSound);
	Mix_FreeChunk(pauseSound);
	Mix_FreeChunk(warpSound);
	secretTheme = NULL;
	pauseSound = NULL;
	menuPickSound = NULL;
	menuSwitchSound = NULL;
	titleDropSound = NULL;
	easyTheme = NULL;
	mediumTheme = NULL;
	hardTheme = NULL;
	whoaTheme = NULL;
	warpSound = NULL;
	hitSound = NULL;
	collectSound = NULL;
	enemyHitSound = NULL;
	dieSound = NULL;
	loseLifeSound = NULL;
	gainLifeSound = NULL;
	highScoreSound = NULL;
}