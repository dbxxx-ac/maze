// maze.h
#ifndef MAZE_H
#define MAZE_H

#include "common.h"

#include <algorithm>
#include <vector>

class Maze {
private:
	int w, h, sx, sy, ex, ey;
	std::vector <int> data;
	bool isValid(int x, int y) const;
public:
	Maze(int n = DEFAULT_SIZE, int m = DEFAULT_SIZE);
	int getWidth() const;
	int getHeight() const;
	int getCell(int x, int y) const;
	bool setCell(int x, int y, int val);
	bool toggleCell(int x, int y);
	int getStartX() const;
	int getStartY() const;
	bool setStart(int x, int y);
	int getEndX() const;
	int getEndY() const;
	bool setEnd(int x, int y);
	void clear();
	void resize(int w, int h);

	const std::vector <int>& getData() const;
	bool loadFromVector(const std::vector <int>& src);
};

#endif