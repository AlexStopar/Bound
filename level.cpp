#include <SDL.h>
#include <vector>
#include <random>
#include "common.h"
#include "player.h"
#include "collectible.h"
#include "level.h"
#include "soundplayer.h"
#include "textdraw.h"
#include "enemy.h"
#include "skull.h"
#include "highscore.h"
#include "texturestorage.h"

int prevX, prevY;
int time = 0;
std::vector<Enemy> enemies;
int frameCount = 0;

bool loadMedia(SDL_Renderer* renderer)
{
	if (!TextureStorage::getInstance().loadTextures(renderer)) return false;
	SoundPlayer::getInstance().loadSounds();
	TextDraw::getInstance().loadText(renderer);
	return true;
}
void playLevel(SDL_Renderer* renderer, SDL_Window* window)
{
	TextureStorage::getInstance().setDifficultyBackground(renderer);
	bool isScoreRecording = false;
	bool isHighScore = false;
	bool isPaused = false;
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> randomX(2 * WALL_WIDTH, SCREEN_WIDTH - (2 * WALL_WIDTH));
	std::uniform_int_distribution<> randomY(2 * WALL_WIDTH, SCREEN_HEIGHT - (2 * WALL_WIDTH));
	std::uniform_int_distribution<> randomVortex(0, VORTEX_LIMIT);
	std::string inputText = "";

	SDL_Event e;

	Player player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_VEL);
	Collectible collectible(randomX(eng), randomY(eng), resolveCoinWidth(), COIN_HEIGHT, 0);
	Skull skull(0, 0, SKULL_WIDTH, SKULL_HEIGHT, 0);

	std::vector<SDL_Rect> walls = getBoundaries();
	SoundPlayer::getInstance().playMusic();

	while (!isQuitting)
	{
		if (player.isDead)
		{
			SoundPlayer::getInstance().stopMusic();
			if (!isScoreRecording)
			{
				isScoreRecording = HighScore::getInstance().checkAndAddNewScore(score, gameDifficulty);
				if (isScoreRecording)
				{
					isHighScore = true;
					SoundPlayer::getInstance().playHighScore();
				}
			}			
		}
		while (SDL_PollEvent(&e) != 0)
		{
			if (!isPaused) SDL_EventState(SDL_KEYUP, SDL_ENABLE);
			if (e.type == SDL_QUIT)
			{
				isQuitting = true;
				isResetting = false;
				reset();
			}		
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) toggleFullscreen(window);
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && !player.isDead)
			{
				SoundPlayer::getInstance().pauseMusic();
				SoundPlayer::getInstance().playPause();
				if (isPaused) isPaused = false;
				else
				{
					isPaused = true;
					SDL_EventState(SDL_KEYUP, SDL_IGNORE);
				}
					
			}
			if (isPaused) SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
			if (!player.isDead)
			{
				if (!isPaused) player.handleEvent(e);
			}
			else 
			{
				if (e.type == SDL_TEXTINPUT)
				{
					if (inputText.size() < 3 && e.text.text[0] != ',') inputText += e.text.text;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					if (e.key.keysym.sym == SDLK_n && !isHighScore)
					{
						isResetting = false;
						reset();
						return;
					}
					else if (e.key.keysym.sym == SDLK_y && !isHighScore)
					{
						isResetting = true;
						reset();
						return;
					}	
					else if (e.key.keysym.sym == SDLK_BACKSPACE)
					{
						if (inputText.size() != 0) inputText.pop_back();
					}
					else if (e.key.keysym.sym == SDLK_RETURN)
					{
						if (isHighScore) HighScore::getInstance().addInitials(inputText);
						isHighScore = false;
					}
				}
			}
			SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
		}
		if (!isPaused)
		{
			if (!player.isDead) player.move(walls, enemies, skull);
			else skull.move(walls);
			for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
				it->move(walls);
			}

			if (!collectible.isHit)
			{
				prevX = collectible.getX();
				prevY = collectible.getY();
			}

			collectible.move(player, randomX(eng), randomY(eng));
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		TextureStorage::getInstance().bgTexture.render(0, 0, renderer);
		renderWalls(renderer, walls);
		
		for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
			it->render(renderer);
		}
		collectible.render(renderer);

		if (!player.isDead) player.render(renderer);
		else skull.render(renderer);

		TextDraw::getInstance().renderHUD(renderer);
		if (collectible.isHit)
		{
			time++;
			TextDraw::getInstance().renderScoreGain(prevX, prevY, renderer);
			prevX++;
			prevY--;
			if (time == 20)
			{
				time = 0;
				Enemy enemy(randomX(eng), randomY(eng), ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_VEL * (int)gameDifficulty, EnemyType::SPIKEBALL);
				if (randomVortex(eng) > VORTEX_LIMIT / (int)gameDifficulty)
				{
					Enemy vortex(randomX(eng), randomY(eng), ENEMY_WIDTH, ENEMY_HEIGHT, 0, EnemyType::VORTEX);
					while (checkCollision(vortex.getHitbox(), player.getHitbox()))
					{
						vortex.setX(randomX(eng));
						vortex.setY(randomY(eng));
						vortex.setHitbox();
					}
					enemies.push_back(vortex);
				}
				while (checkCollision(enemy.getHitbox(), player.getHitbox()))
				{
					enemy.setX(randomX(eng));
					enemy.setY(randomY(eng));
					enemy.setHitbox();
				}
				enemies.push_back(enemy);
				collectible.isHit = false;
			}
		}
		if (player.isDead) TextDraw::getInstance().renderGameOver(renderer, isHighScore, inputText);
		if (isPaused)TextDraw::getInstance().renderPause(renderer);
		SDL_RenderPresent(renderer);
		frameCount++;
		if (frameCount == DISPLAY_LIMIT) frameCount = 0;
	}
}


void reset()
{
	TextDraw::getInstance().gameOverRise = 0;
	enemies.clear();
	score = 0;
}

