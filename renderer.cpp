#include "renderer.h"

#include <cstdio>
#include <graphics.h>

Renderer::Renderer() {}

void Renderer::getMazeOffset(const Maze& maze, int& ox, int& oy) const {
	ox = (WINDOW_WIDTH - maze.getWidth() * CELL_SIZE) / 2;
	oy = (WINDOW_HEIGHT - maze.getHeight() * CELL_SIZE) / 2;
}

void Renderer::drawMaze(const Maze& maze, const std::vector<int>& pathMask) const {
	int ox, oy;
	getMazeOffset(maze, ox, oy);
	setbkcolor(COLOR_BG);
	cleardevice();
	setlinecolor(COLOR_GRID);
	setlinestyle(PS_SOLID, GRID_LINE_WIDTH);
	for (int y = 0; y < maze.getHeight(); ++y) {
		for (int x = 0; x < maze.getWidth(); ++x) {
			int idx = y * maze.getWidth() + x;
			COLORREF color = (maze.getCell(x, y) == 1) ? COLOR_WALL : COLOR_EMPTY;
			if (!pathMask.empty() && pathMask[idx] == 1) color = COLOR_PATH;
			if (x == maze.getStartX() && y == maze.getStartY()) color = COLOR_START;
			if (x == maze.getEndX() && y == maze.getEndY()) color = COLOR_END;
			int left = ox + x * CELL_SIZE;
			int top = oy + y * CELL_SIZE;
			int right = left + CELL_SIZE;
			int bottom = top + CELL_SIZE;
			setfillcolor(color);
			solidrectangle(left, top, right, bottom);
		}
	}
}

void Renderer::drawPathLength(int length) const {
	setbkmode(TRANSPARENT);
	settextcolor(RGB(240, 240, 240));
	char buf[64] = "";
	if (length < 0) {
		sprintf_s(buf, "Path length: N/A");
	} else {
		sprintf_s(buf, "Path length: %d", length);
	}
	outtextxy(10, 10, (LPCTSTR)buf);
}
