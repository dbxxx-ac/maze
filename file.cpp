#include "file.h"
#include "common.h"

#include <windows.h>
#include <commdlg.h>

#include <cstring>
#include <fstream>
#include <vector>

FileIO::FileIO() {}

bool FileIO::saveMaze(const Maze& maze, const char* path) const {
	std::ofstream out(path);
	if (!out.is_open()) return false;
	out << maze.getWidth() << " " << maze.getHeight() << "\n";
	out << maze.getStartX() << " " << maze.getStartY() << " " << maze.getEndX() << " " << maze.getEndY() << "\n";
	for (int y = 0; y < maze.getHeight(); ++y) {
		for (int x = 0; x < maze.getWidth(); ++x) {
			out << maze.getCell(x, y);
			if (x + 1 < maze.getWidth()) out << " ";
		}
		out << "\n";
	}
	return true;
}

bool FileIO::loadMaze(Maze& maze, const char* path) const {
	std::ifstream in(path);
	if (!in.is_open()) return false;
	int w = 0, h = 0;
	int sx = -1, sy = -1, ex = -1, ey = -1;
	if (!(in >> w >> h)) return false;
	if (w <= 0 || h <= 0 || w > MAX_SIZE || h > MAX_SIZE) return false;
	if (!(in >> sx >> sy >> ex >> ey)) return false;
	std::vector<int> data(w * h, 0);
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int v = 0;
			if (!(in >> v)) return false;
			data[y * w + x] = v ? 1 : 0;
		}
	}
	maze.resize(w, h);
	maze.loadFromVector(data);
	if (sx >= 0 && sy >= 0) maze.setStart(sx, sy);
	if (ex >= 0 && ey >= 0) maze.setEnd(ex, ey);
	return true;
}

bool FileIO::openFileDialog(char* outPath, int outSize) const {
	OPENFILENAMEA ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetHWnd();
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Maze files (*.txt)\0*.txt\0All files (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = "txt";
	if (GetOpenFileNameA(&ofn) == TRUE) {
		strncpy_s(outPath, outSize, fileName, _TRUNCATE);
		return true;
	}
	return false;
}

bool FileIO::saveFileDialog(char* outPath, int outSize) const {
	OPENFILENAMEA ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetHWnd();
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "Maze files (*.txt)\0*.txt\0All files (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = "txt";
	if (GetSaveFileNameA(&ofn) == TRUE) {
		strncpy_s(outPath, outSize, fileName, _TRUNCATE);
		return true;
	}
	return false;
}
