#ifndef LIVES_H
#define LIVES_H
#include <SDL.h>

class Lives
{
public:
	Lives();
	void changeLifeCount(int amount);
	int getLives();
	void renderLives(SDL_Renderer* renderer);
private:
	int livesLeft;
	int angle = 0;
};

#endif