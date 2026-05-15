#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

#include "maze.h"

class Renderer;

struct Cell {
	int x;
	int y;
};

class Solver {
public:
	Solver();
	std::vector<Cell> solveAnimated(const Maze& maze, const Renderer& renderer, int delayMs) const;
	void buildPathMask(const Maze& maze, const std::vector<Cell>& path, std::vector<int>& mask) const;
};

#endif
