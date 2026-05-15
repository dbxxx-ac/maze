#include "editor.h"

Editor::Editor() : editMode(0) {}

void Editor::setMode(int mode) { editMode = mode; }
int Editor::getMode() const { return editMode; }

bool Editor::handleClick(Maze& maze, const Renderer& renderer, int px, int py) {
	int ox, oy;
	renderer.getMazeOffset(maze, ox, oy);
	int cellSize = GetCellSize(maze.getWidth(), maze.getHeight());
	int mx = px - ox;
	int my = py - oy;
	if (mx < 0 || my < 0) return false;
	int cx = mx / cellSize;
	int cy = my / cellSize;
	if (cx >= maze.getWidth() || cy >= maze.getHeight()) return false;
	if (editMode == 0) maze.toggleCell(cx, cy);
	if (editMode == 1) maze.setStart(cx, cy);
	if (editMode == 2) maze.setEnd(cx, cy);
	return true;
}
