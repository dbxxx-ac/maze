#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

#include "maze.h"

struct Cell {
	int x;
	int y;
};

class Solver {
public:
	Solver();
	std::vector<Cell> solve(const Maze& maze) const;
	void buildPathMask(const Maze& maze, const std::vector<Cell>& path, std::vector<int>& mask) const;
};

#endif
