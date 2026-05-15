#ifndef GENERATOR_H
#define GENERATOR_H

#include "maze.h"

class Generator {
public:
	Generator();
	void generate(Maze& maze) const;
};

#endif
