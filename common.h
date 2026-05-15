#pragma once

#include <graphics.h>
#include <vector>

const int MAX_SIZE = 35;
const int DEFAULT_SIZE = 10;
const int MIN_SIZE = 5;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int DEFAULT_MAZE_WIDTH = 15;
const int DEFAULT_MAZE_HEIGHT = 15;
const int GRID_LINE_WIDTH = 1;
const int SIDE_PADDING = 40;
const int TOP_UI_HEIGHT = 80;

const COLORREF COLOR_BG = RGB(20, 20, 20);
const COLORREF COLOR_WALL = RGB(127, 127, 127);
const COLORREF COLOR_EMPTY = RGB(230, 230, 230);
const COLORREF COLOR_GRID = RGB(120, 120, 120);
const COLORREF COLOR_START = RGB(0, 200, 80);
const COLORREF COLOR_END = RGB(220, 60, 60);
const COLORREF COLOR_PATH = RGB(255, 127, 39);

const COLORREF COLOR_VISITED = RGB(140, 190, 230);
const COLORREF COLOR_PLAYER = RGB(0, 18, 154);
const COLORREF COLOR_TEXT = RGB(240, 240, 240);

const int SOLVE_ANIM_DELAY_MS = 15;

inline int GetCellSize(int w, int h) {
	int sizeX = (WINDOW_WIDTH - SIDE_PADDING * 2) / w;
	int sizeY = (WINDOW_HEIGHT - TOP_UI_HEIGHT - SIDE_PADDING) / h;
	int size = (sizeX < sizeY) ? sizeX : sizeY;
	if (size < 8) size = 8;
	return size;
}

inline std::vector<int> DefaultMazeData() {
	const char* rows[DEFAULT_MAZE_HEIGHT] = {
		"###############",
		"#..#.....#....#",
		"#..#.#.#.#.##.#",
		"#....#.#...#..#",
		"###.#.#.###.#.#",
		"#...#...#...#.#",
		"#.#####.#.###.#",
		"#.....#.#.....#",
		"#.###.#.###.###",
		"#...#.#.....#.#",
		"#.###.#####.#.#",
		"#.#.....#...#.#",
		"#.#.###.#.###.#",
		"#...#...#.....#",
		"###############"
	};
	std::vector<int> data(DEFAULT_MAZE_WIDTH * DEFAULT_MAZE_HEIGHT, 0);
	for (int y = 0; y < DEFAULT_MAZE_HEIGHT; ++y) {
		for (int x = 0; x < DEFAULT_MAZE_WIDTH; ++x) {
			data[y * DEFAULT_MAZE_WIDTH + x] = (rows[y][x] == '#') ? 1 : 0;
		}
	}
	return data;
}
