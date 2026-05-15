#include "common.h"
#include "maze.h"
#include "renderer.h"
#include "solver.h"
#include "editor.h"
#include "file.h"

#include <graphics.h>
#include <vector>

int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	Maze maze(DEFAULT_MAZE_WIDTH, DEFAULT_MAZE_HEIGHT);
	maze.loadFromVector(DefaultMazeData());
	Renderer renderer;
	Solver solver;
	Editor editor;
	FileIO fileIO;

	std::vector<Cell> path;
	std::vector<int> pathMask;
	solver.buildPathMask(maze, path, pathMask);

	BeginBatchDraw();
	while (true) {
		ExMessage msg;
		while (peekmessage(&msg)) {
			if (msg.message == WM_KEYDOWN) {
				if (msg.vkcode == 'T') editor.setMode(0);
				if (msg.vkcode == '1') editor.setMode(1);
				if (msg.vkcode == '2') editor.setMode(2);
				if (msg.vkcode == VK_RETURN) {
					path = solver.solve(maze);
					solver.buildPathMask(maze, path, pathMask);
				}
				if (msg.vkcode == 'O') {
					char pathBuf[MAX_PATH] = "";
					if (fileIO.openFileDialog(pathBuf, MAX_PATH)) {
						if (fileIO.loadMaze(maze, pathBuf)) {
							path.clear();
							solver.buildPathMask(maze, path, pathMask);
						}
					}
				}
				if (msg.vkcode == 'S') {
					char pathBuf[MAX_PATH] = "";
					if (fileIO.saveFileDialog(pathBuf, MAX_PATH)) {
						fileIO.saveMaze(maze, pathBuf);
					}
				}
			}
			if (msg.message == WM_LBUTTONDOWN) {
				if (editor.handleClick(maze, renderer, msg.x, msg.y)) {
					path.clear();
					solver.buildPathMask(maze, path, pathMask);
				}
			}
		}

		renderer.drawMaze(maze, pathMask);
		int pathLen = path.empty() ? -1 : (int)path.size() - 1;
		renderer.drawPathLength(pathLen);
		FlushBatchDraw();
		Sleep(10);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}