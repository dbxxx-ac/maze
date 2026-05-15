#include "common.h"
#include "maze.h"
#include "renderer.h"
#include "solver.h"
#include "editor.h"
#include "file.h"
#include "generator.h"
#include "manual.h"

#include <graphics.h>
#include <cstdio>
#include <string>
#include <windows.h>
#include <vector>

int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	Maze maze(DEFAULT_MAZE_WIDTH, DEFAULT_MAZE_HEIGHT);
	maze.loadFromVector(DefaultMazeData());
	Renderer renderer;
	Solver solver;
	Editor editor;
	FileIO fileIO;
	Generator generator;
	ManualController manual;
	bool resizing = false;
	std::string resizeInput;

	std::vector<Cell> path;
	std::vector<int> pathMask;
	solver.buildPathMask(maze, path, pathMask);

	BeginBatchDraw();
	while (true) {
		ExMessage msg;
		while (peekmessage(&msg)) {
			if (msg.message == WM_KEYDOWN) {
				if (resizing) {
					if (msg.vkcode == VK_ESCAPE) {
						resizing = false;
						resizeInput.clear();
						continue;
					}
					if (msg.vkcode == VK_BACK) {
						if (!resizeInput.empty()) resizeInput.pop_back();
						continue;
					}
					if (msg.vkcode == VK_RETURN) {
						int newW = 0;
						int newH = 0;
						if (sscanf_s(resizeInput.c_str(), "%d %d", &newW, &newH) == 2) {
							if (newW >= MIN_SIZE && newH >= MIN_SIZE && newW <= MAX_SIZE && newH <= MAX_SIZE) {
								maze.resize(newW, newH);
								path.clear();
								solver.buildPathMask(maze, path, pathMask);
								manual.stop();
							}
						}
						resizing = false;
						resizeInput.clear();
						continue;
					}
					if (msg.vkcode == VK_SPACE) {
						resizeInput.push_back(' ');
						continue;
					}
					char c = (char)msg.vkcode;
					if (c >= '0' && c <= '9') {
						resizeInput.push_back(c);
					}
					continue;
				}
				if (msg.vkcode == 'T') editor.setMode(0);
				if (msg.vkcode == '1') editor.setMode(1);
				if (msg.vkcode == '2') editor.setMode(2);
				if (msg.vkcode == VK_RETURN) {
					path = solver.solveAnimated(maze, renderer, SOLVE_ANIM_DELAY_MS);
					solver.buildPathMask(maze, path, pathMask);
				}
				if (msg.vkcode == 'G') {
					generator.generate(maze);
					path.clear();
					solver.buildPathMask(maze, path, pathMask);
					manual.stop();
				}
				if (msg.vkcode == 'M') {
					manual.toggle(maze);
				}
				if (msg.vkcode == 'R') {
					resizing = true;
					resizeInput.clear();
				}
				if (msg.vkcode == 'O') {
					char pathBuf[MAX_PATH] = "";
					if (fileIO.openFileDialog(pathBuf, MAX_PATH)) {
						if (fileIO.loadMaze(maze, pathBuf)) {
							path.clear();
							solver.buildPathMask(maze, path, pathMask);
							manual.stop();
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
			if (msg.message == WM_LBUTTONDOWN && !manual.isActive()) {
				if (editor.handleClick(maze, renderer, msg.x, msg.y)) {
					path.clear();
					solver.buildPathMask(maze, path, pathMask);
				}
			}
			if (msg.message == WM_KEYDOWN && manual.isActive()) {
				manual.handleKey(msg.vkcode, maze);
			}
		}

		renderer.drawMaze(maze, pathMask);
		int pathLen = path.empty() ? -1 : (int)path.size() - 1;
		renderer.drawPathLength(pathLen);
		if (manual.isActive()) {
			renderer.drawPlayer(maze, manual.getPlayerX(), manual.getPlayerY());
			renderer.drawManualStats(manual.getSteps(), manual.getElapsedMs(), manual.isFinished());
		}
		if (resizing) {
			renderer.drawResizePrompt(resizeInput);
		}
		FlushBatchDraw();
		Sleep(10);
	}
	EndBatchDraw();
	closegraph();
	return 0;
}