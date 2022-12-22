#pragma once

#include <vector>
#include <string>
#include <stdio.h>

const int GRID_SIZE{ 25 };

struct Cube {
	char x;
	char y;
	char z;
	uint16_t connex{ 0 };
	bool isAir{ true };

	Cube() : x(0), y(0), z(0) {};
	Cube(char x, char y, char z) : x(x), y(y), z(z), isAir(false) {};
	Cube(std::string s) : isAir(false) {
		unsigned int a, b, c;
		sscanf_s(s.c_str(), "%d,%d,%d", &a, &b, &c);
		x = a;
		y = b;
		z = c;
	}
};

using Grid = std::vector<std::vector<std::vector<Cube*>>>;

size_t day18P1(const std::vector<std::string>& input);
size_t day18P2(const std::vector<std::string>& input);

Grid getGrid(const std::vector<std::string>& input, std::vector<Cube>& cubes);

void assignConnex(Cube& cube, Grid& grid, short connex);