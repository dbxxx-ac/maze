// maze.cpp
#include "maze.h"

#include <algorithm>

bool Maze::isValid(int x, int y) const {
	return x >= 0 && x < w && y >= 0 && y < h;
}

Maze::Maze(int w, int h) : w(w), h(h), sx(-1), sy(-1), ex(-1), ey(-1) {
	data.assign(w * h, 0);
}

int Maze::getWidth() const { return w;}
int Maze::getHeight() const { return h; }

int Maze::getCell(int x, int y) const {
	if (!isValid(x, y)) return 1;
	return data[y * w + x];
}

bool Maze::setCell(int x, int y, int val) {
	if (!isValid(x, y)) return false;
	if (x == sx && y == sy) return false;
	if (x == ex && y == ey) return false;
	data[y * w + x] = val;
	return true;
}

bool Maze::toggleCell(int x, int y) {
	if (!isValid(x, y)) return false;
	if (x == sx && y == sy) return false;
	if (x == ex && y == ey) return false;
	data[y * w + x] = 1 - data[y * w + x];
	return true;
} 

int Maze::getStartX() const { return sx; }
int Maze::getStartY() const { return sy; }

bool Maze::setStart(int x, int y) {
	if (!isValid(x, y)) return false;
	if (getCell(x, y) == 1) return false;
	if (x == ex && y == ey) return false;
	sx = x; sy = y;
	return true;
}

int Maze::getEndX() const { return ex; }
int Maze::getEndY() const { return ey; }

bool Maze::setEnd(int x, int y) {
	if (!isValid(x, y)) return false;
	if (getCell(x, y) == 1) return false;
	if (x == sx && y == sy) return false;
	ex = x; ey = y;
	return true;
}

void Maze::clear() {
	std::fill(data.begin(), data.end(), 0);
	sx = sy = ex = ey = -1;
}

void Maze::resize(int w, int h) {
	this -> w = w; this -> h = h;
	data.assign(w * h, 0);
	sx = sy = ex = ey = -1;
}

const std::vector <int>& Maze::getData() const {
	return data;
}

bool Maze::loadFromVector(const std::vector <int>& src) {
	if (src.size() != w * h) return false;
	data = src;
	sx = sy = ex = ey = -1;
	return true;
}