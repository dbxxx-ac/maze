#include "manual.h"

#include <windows.h>

ManualController::ManualController()
	: active(false), finished(false), playerX(-1), playerY(-1), steps(0), startTick(0), finishTick(0) {}

bool ManualController::isActive() const { return active; }
bool ManualController::isFinished() const { return finished; }

bool ManualController::toggle(const Maze& maze) {
	if (active) {
		active = false;
		return true;
	}
	int sx = maze.getStartX();
	int sy = maze.getStartY();
	if (sx < 0 || sy < 0) return false;
	playerX = sx;
	playerY = sy;
	steps = 0;
	finished = false;
	startTick = finishTick = GetTickCount();
	active = true;
	return true;
}

void ManualController::stop() {
	active = false;
	finished = false;
	playerX = -1;
	playerY = -1;
	steps = 0;
	startTick = 0;
	finishTick = 0;
}

bool ManualController::handleKey(int vkCode, const Maze& maze) {
	if (!active || finished) return false;
	int dx = 0;
	int dy = 0;
	if (vkCode == VK_UP) dy = -1;
	if (vkCode == VK_DOWN) dy = 1;
	if (vkCode == VK_LEFT) dx = -1;
	if (vkCode == VK_RIGHT) dx = 1;
	if (dx == 0 && dy == 0) return false;
	int nx = playerX + dx;
	int ny = playerY + dy;
	if (!maze.isValid(nx, ny)) return false;
	if (maze.getCell(nx, ny) == 1) return false;
	playerX = nx;
	playerY = ny;
	++steps;
	if (playerX == maze.getEndX() && playerY == maze.getEndY()) {
		finished = true;
		finishTick = GetTickCount();
	}
	return true;
}

int ManualController::getPlayerX() const { return playerX; }
int ManualController::getPlayerY() const { return playerY; }
int ManualController::getSteps() const { return steps; }

int ManualController::getElapsedMs() const {
	if (!active) return 0;
	if (finished) return (int)(finishTick - startTick);
	return (int)(GetTickCount() - startTick);
}
