#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "maze.h"
#include "common.h"

class Renderer {
public:
	Renderer();
	void drawMaze(const Maze& maze, const std::vector<int>& pathMask) const;
	void drawPathLength(int length) const;
	void getMazeOffset(const Maze& maze, int& ox, int& oy) const;
};

#endif
