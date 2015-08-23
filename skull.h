#ifndef SKULL_H
#define SKULL_H
#include "movingobj.h"


class Skull : public IMovingObject
{
public:
	Skull(int x, int y, int w, int h, int v) : IMovingObject(x, y, w, h, v) {}
	void handleEvent(SDL_Event& e) {}
	void move(std::vector<SDL_Rect>& walls);
	bool goingUp = true;
	int upTime = 0;
	void render(SDL_Renderer* renderer);
	void setXY(int x, int y);
};
#endif 
