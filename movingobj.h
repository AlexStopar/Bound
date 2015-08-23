#ifndef MOVINGOBJ_H
#define MOVINGOBJ_H
#include <SDL.h>
#include <vector>
#include "texture.h"
#include "collision.h"

class IMovingObject
{
public:
	IMovingObject(int x, int y, int w, int h, int v)
	{
		pPosX = x;
		pPosY = y;
		pWidth = w;
		pHeight = h;
		pVelocity = v;
		pHitbox.radius = w / 2;
		pVelX = 0;
		pVelY = 0;
		setHitbox();
	}
	virtual void handleEvent(SDL_Event& e) = 0;
	virtual void move(std::vector<SDL_Rect>& walls) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;
	Circle& getHitbox() { return pHitbox; }
	void setHitbox()
	{
		pHitbox.x = pPosX;
		pHitbox.y = pPosY;
	}
	int getX() { return pPosX; }
	int getY() { return pPosY; }
protected:
	int pWidth, pHeight;
	int pVelocity;
	int pPosX, pPosY;
	int pVelX, pVelY;
	Circle pHitbox;
};
#endif 
