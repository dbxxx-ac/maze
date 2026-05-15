#include "generator.h"

#include <algorithm>
#include <random>
#include <vector>

struct Cell {
	int x;
	int y;
};

Generator::Generator() {}

void Generator::generate(Maze& maze) const {
	int w = maze.getWidth();
	int h = maze.getHeight();
	std::vector<int> data(w * h, 1);
	if (w < 3 || h < 3) {
		maze.loadFromVector(std::vector<int>(w * h, 0));
		return;
	}
	auto idx = [w](int x, int y) { return y * w + x; };
	int startX = (w % 2 == 0) ? 1 : 0;
	int startY = (h % 2 == 0) ? 1 : 0;
	std::vector<Cell> stack;
	stack.push_back({ startX, startY });
	data[idx(startX, startY)] = 0;
	std::random_device rd;
	std::mt19937 rng(rd());
	int dx[4] = { 1, -1, 0, 0 };
	int dy[4] = { 0, 0, 1, -1 };
	while (!stack.empty()) {
		Cell cur = stack.back();
		int dirs[4] = { 0, 1, 2, 3 };
		std::shuffle(dirs, dirs + 4, rng);
		bool moved = false;
		for (int i = 0; i < 4; ++i) {
			int dir = dirs[i];
			int nx = cur.x + dx[dir] * 2;
			int ny = cur.y + dy[dir] * 2;
			if (!maze.isValid(nx, ny)) continue;
			if (data[idx(nx, ny)] == 0) continue;
			int midx = cur.x + dx[dir];
			int midy = cur.y + dy[dir];
			if (!maze.isValid(midx, midy)) continue;
			data[idx(midx, midy)] = 0;
			data[idx(nx, ny)] = 0;
			stack.push_back({ nx, ny });
			moved = true;
			break;
		}
		if (!moved) stack.pop_back();
	}
	maze.loadFromVector(data);
}
