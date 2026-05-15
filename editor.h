#ifndef EDITOR_H
#define EDITOR_H

#include "maze.h"
#include "renderer.h"

class Editor {
private:
	int editMode;
public:
	Editor();
	void setMode(int mode);
	int getMode() const;
	bool handleClick(Maze& maze, const Renderer& renderer, int px, int py);
};

#endif
