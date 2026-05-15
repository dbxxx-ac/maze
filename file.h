#ifndef FILE_H
#define FILE_H

#include "maze.h"

class FileIO {
public:
	FileIO();
	bool saveMaze(const Maze& maze, const char* path) const;
	bool loadMaze(Maze& maze, const char* path) const;
	bool openFileDialog(char* outPath, int outSize) const;
	bool saveFileDialog(char* outPath, int outSize) const;
};

#endif
