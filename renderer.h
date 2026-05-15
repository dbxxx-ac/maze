#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>

#include "maze.h"
#include "common.h"

class Renderer {
public:
	Renderer();
	void drawMaze(const Maze& maze, const std::vector<int>& pathMask) const;
	void drawMazeWithVisited(const Maze& maze, const std::vector<int>& pathMask, const std::vector<int>& visitedMask) const;
	void drawPathLength(int length) const;
	void drawPlayer(const Maze& maze, int cellX, int cellY) const;
	void drawManualStats(int steps, int elapsedMs, bool finished) const;
	void drawResizePrompt(const std::string& input) const;
	void getMazeOffset(const Maze& maze, int& ox, int& oy) const;
};

#endif
