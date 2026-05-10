#include <graphics.h>
#include "maze.h"

int main() {
	initgraph(800, 600);
	Maze maze(21, 21);
	maze.setStart(0, 0);
	maze.setEnd(20, 20);

	while (true) {
		
	}

	closegraph();
	return 0;
}