#include "renderer.h"

#include <cstdio>
#include <graphics.h>
#include <string>

Renderer::Renderer() {}

void Renderer::getMazeOffset(const Maze& maze, int& ox, int& oy) const {
	int cellSize = GetCellSize(maze.getWidth(), maze.getHeight());
	int mazeW = maze.getWidth() * cellSize;
	int mazeH = maze.getHeight() * cellSize;
	ox = (WINDOW_WIDTH - mazeW) / 2;
	oy = TOP_UI_HEIGHT + (WINDOW_HEIGHT - TOP_UI_HEIGHT - mazeH) / 2;
}

void Renderer::drawMaze(const Maze& maze, const std::vector<int>& pathMask) const {
	int ox, oy;
	getMazeOffset(maze, ox, oy);
	int cellSize = GetCellSize(maze.getWidth(), maze.getHeight());
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
			int left = ox + x * cellSize;
			int top = oy + y * cellSize;
			int right = left + cellSize;
			int bottom = top + cellSize;
			setfillcolor(color);
			solidrectangle(left, top, right, bottom);
			if (maze.getCell(x, y) == 1) {
				setlinecolor(COLOR_GRID);
				setlinestyle(PS_SOLID, 2);
				rectangle(left, top, right, bottom);
				setlinestyle(PS_SOLID, GRID_LINE_WIDTH);
			}
		}
	}
}

void Renderer::drawMazeWithVisited(const Maze& maze, const std::vector<int>& pathMask, const std::vector<int>& visitedMask) const {
	int ox, oy;
	getMazeOffset(maze, ox, oy);
	int cellSize = GetCellSize(maze.getWidth(), maze.getHeight());
	setbkcolor(COLOR_BG);
	cleardevice();
	setlinecolor(COLOR_GRID);
	setlinestyle(PS_SOLID, GRID_LINE_WIDTH);
	for (int y = 0; y < maze.getHeight(); ++y) {
		for (int x = 0; x < maze.getWidth(); ++x) {
			int idx = y * maze.getWidth() + x;
			COLORREF color = (maze.getCell(x, y) == 1) ? COLOR_WALL : COLOR_EMPTY;
			if (!visitedMask.empty() && visitedMask[idx] == 1 && maze.getCell(x, y) == 0) color = COLOR_VISITED;
			if (!pathMask.empty() && pathMask[idx] == 1) color = COLOR_PATH;
			if (x == maze.getStartX() && y == maze.getStartY()) color = COLOR_START;
			if (x == maze.getEndX() && y == maze.getEndY()) color = COLOR_END;
			int left = ox + x * cellSize;
			int top = oy + y * cellSize;
			int right = left + cellSize;
			int bottom = top + cellSize;
			setfillcolor(color);
			solidrectangle(left, top, right, bottom);
			if (maze.getCell(x, y) == 1) {
				setlinecolor(COLOR_GRID);
				setlinestyle(PS_SOLID, 2);
				rectangle(left, top, right, bottom);
				setlinestyle(PS_SOLID, GRID_LINE_WIDTH);
			}
		}
	}
}

void Renderer::drawPathLength(int length) const {
	setbkmode(TRANSPARENT);
	settextcolor(COLOR_TEXT);
	char buf[64] = "";
	if (length < 0) {
		sprintf_s(buf, "Ready");
	} else {
		sprintf_s(buf, "Path length: %d", length);
	}
	outtextxy(10, 10, (LPCTSTR)buf);
}

void Renderer::drawPlayer(const Maze& maze, int cellX, int cellY) const {
	if (cellX < 0 || cellY < 0) return;
	int ox, oy;
	getMazeOffset(maze, ox, oy);
	int cellSize = GetCellSize(maze.getWidth(), maze.getHeight());
	int cx = ox + cellX * cellSize + cellSize / 2;
	int cy = oy + cellY * cellSize + cellSize / 2;
	setfillcolor(COLOR_PLAYER);
	solidcircle(cx, cy, cellSize / 3);
}

void Renderer::drawManualStats(int steps, int elapsedMs, bool finished) const {
	setbkmode(TRANSPARENT);
	settextcolor(COLOR_TEXT);
	char buf[64] = "";
	int seconds = elapsedMs / 1000;
	if (finished) {
		sprintf_s(buf, "Manual: %d steps, %ds (done, congrats!)", steps, seconds);
	} else {
		sprintf_s(buf, "Manual: %d steps, %ds", steps, seconds);
	}
	outtextxy(10, 30, (LPCTSTR)buf);
}

void Renderer::drawResizePrompt(const std::string& input) const {
	setbkmode(TRANSPARENT);
	settextcolor(COLOR_TEXT);
	char buf[128] = "";
	sprintf_s(buf, "Resize: W H. Enter to confirm, Esc to cancel: %s", input.c_str());
	outtextxy(10, 50, (LPCTSTR)buf);
}
