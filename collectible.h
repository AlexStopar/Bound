#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H
#include <SDL.h>
#include <random>
#include "movingobj.h"
#include "player.h"

const int COIN_SPEED = 4;
const int SECRET_COIN_SPEED = 5;

class Collectible : public IMovingObject
{
public:
	Collectible(int x, int y, int w, int h, int v) : IMovingObject(x, y, w, h, v) {
		for (int i = 0; i < resolveCoinFrames() - 1; i++)
		{
			collectibleClips[i] = { (pWidth / resolveCoinFrames() * i), 0, pWidth / resolveCoinFrames(), pHeight };
		}
		pHitbox.radius = pWidth / resolveCoinFrames()/ 2;
	}
	void move(std::vector<SDL_Rect>& walls) {};

	void handleEvent(SDL_Event& e) {};

	void move(Player& player, int newX, int newY);

	bool isHit = false;

	int resolveCoinSpeed();

	void render(SDL_Renderer* renderer);
protected:
	int frame = 0;

	SDL_Rect collectibleClips[SECRET_COLLECT_FRAMES];
};
#endif