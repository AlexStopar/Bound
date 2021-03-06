#include <SDL.h>
#include "collision.h"

double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;


	if (bottomA <= topB) return false;

	if (topA >= bottomB) return false;

	if (rightA <= leftB) return false;

	if (leftA >= rightB) return false;

	return true;
}

bool checkCollision(Circle& a, Circle& b)
{
	int totalRadiusSquared = a.radius + b.radius;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;
	if (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared)) return true;
	return false;
}

bool checkCollision(Circle& a, SDL_Rect& b)
{
	int cX, cY;

	if (a.x < b.x) cX = b.x;
	else if (a.x > b.x + b.w) cX = b.x + b.w;
	else cX = a.x;

	if (a.y < b.y) cY = b.y;
	else if (a.y > b.y + b.h) cY = b.y + b.h;
	else cY = a.y;


	if (distanceSquared(a.x, a.y, cX, cY) < a.radius * a.radius) return true;
	return false;

}
