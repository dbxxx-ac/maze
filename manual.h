#ifndef MANUAL_H
#define MANUAL_H

#include "maze.h"

class ManualController {
private:
	bool active;
	bool finished;
	int playerX;
	int playerY;
	int steps;
	unsigned int startTick;
	unsigned int finishTick;
public:
	ManualController();
	bool isActive() const;
	bool isFinished() const;
	bool toggle(const Maze& maze);
	void stop();
	bool handleKey(int vkCode, const Maze& maze);
	int getPlayerX() const;
	int getPlayerY() const;
	int getSteps() const;
	int getElapsedMs() const;
};

#endif
