#ifndef PLAYER_H
#define PLAYER_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "enemy.h"
#include "collision.h"
#include "movingobj.h"
#include "skull.h"
#include "lives.h"

class Player : public IMovingObject
{
public:
	int angle = 0;
	bool isDead = false;
	Player(int x, int y, int w, int h, int v) : IMovingObject(x, y, w, h, v) {
		playerLives = Lives();
	}
	Lives playerLives;
	void handleEvent(SDL_Event& e);
	void move(std::vector<SDL_Rect>& walls) {}
	void move(std::vector<SDL_Rect>& walls, std::vector<Enemy>& enemies, Skull& skull);
	void die(Skull& skull);
	void render(SDL_Renderer* renderer);
private:
	const int FULL_INVINCIBILITY_COUNT = 20;
	int invincibilityCount = FULL_INVINCIBILITY_COUNT;
};

#endif