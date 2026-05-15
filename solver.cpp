#include "solver.h"

#include <algorithm>
#include <queue>

#include <graphics.h>
#include <windows.h>

#include "renderer.h"

Solver::Solver() {}

std::vector<Cell> Solver::solveAnimated(const Maze& maze, const Renderer& renderer, int delayMs) const {
	std::vector<Cell> empty;
	int w = maze.getWidth();
	int h = maze.getHeight();
	int sx = maze.getStartX();
	int sy = maze.getStartY();
	int ex = maze.getEndX();
	int ey = maze.getEndY();
	if (sx < 0 || sy < 0 || ex < 0 || ey < 0) return empty;
	std::vector<int> prev(w * h, -1);
	std::vector<int> visitedMask(w * h, 0);
	std::vector<int> pathMask;
	std::queue<Cell> q;
	q.push({ sx, sy });
	prev[sy * w + sx] = sy * w + sx;
	visitedMask[sy * w + sx] = 1;
	int dx[4] = { 1, -1, 0, 0 };
	int dy[4] = { 0, 0, 1, -1 };
	while (!q.empty()) {
		Cell cur = q.front();
		q.pop();
		if (cur.x == ex && cur.y == ey) break;
		for (int dir = 0; dir < 4; ++dir) {
			int nx = cur.x + dx[dir];
			int ny = cur.y + dy[dir];
			if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
			if (maze.getCell(nx, ny) == 1) continue;
			int ni = ny * w + nx;
			if (prev[ni] != -1) continue;
			prev[ni] = cur.y * w + cur.x;
			visitedMask[ni] = 1;
			q.push({ nx, ny });
			renderer.drawMazeWithVisited(maze, pathMask, visitedMask);
			renderer.drawPathLength(-1);
			FlushBatchDraw();
			Sleep(delayMs);
		}
	}
	int endIdx = ey * w + ex;
	if (prev[endIdx] == -1) return empty;
	std::vector<Cell> path;
	int cur = endIdx;
	while (true) {
		int x = cur % w;
		int y = cur / w;
		path.push_back({ x, y });
		if (cur == prev[cur]) break;
		cur = prev[cur];
	}
	std::reverse(path.begin(), path.end());
	return path;
}

void Solver::buildPathMask(const Maze& maze, const std::vector<Cell>& path, std::vector<int>& mask) const {
	mask.assign(maze.getWidth() * maze.getHeight(), 0);
	for (const auto& c : path) {
		int idx = c.y * maze.getWidth() + c.x;
		if (idx >= 0 && idx < (int)mask.size()) mask[idx] = 1;
	}
}
