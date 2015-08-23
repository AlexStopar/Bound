#ifndef ENEMY_H
#define ENEMY_H
#include <random>
#include "movingobj.h"
#include "common.h"

enum EnemyType {SPIKEBALL, VORTEX};
class Enemy : public IMovingObject
{
public:
	enum Direction {NONE, UPLEFT, UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT};
	
	int angle = 0;
	Enemy(int x, int y, int w, int h, int v, EnemyType et) : IMovingObject(x, y, w, h, v) {
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> randomDirection(Direction::NONE, Direction::LEFT);
		enemyDirection = static_cast<Direction>(randomDirection(eng));
		eType = et;
	}
	void render(SDL_Renderer* renderer);
	void move(std::vector<SDL_Rect>& walls);
	void handleEvent(SDL_Event& e) {};
	void setX(int x) { pPosX = x; }
	void setY(int y) { pPosY = y; }
	EnemyType eType;
private:
	const int PULSE_LIMIT = 10 * (int)gameDifficulty;
	const int PULSE_CHANGE_DELAY = 9 - (int)gameDifficulty;
	int pulse = 0;
	bool isPulsing = true;
	Direction enemyDirection;
};
#endif 
