#pragma once

#include <vector>
#include <string>

struct Coord {
	int x;
	int y;
	Coord() : x(0), y(0) {}
	Coord(int x, int y) : x(x), y(y) {}
};

using Rock = std::vector<Coord>;

int day17P1(const std::vector<std::string>& input);

void rockFall(std::vector<std::vector<short>>&, const std::vector<Rock>&, const std::vector<std::string>&, int&, char, size_t&);

void displayRocks(std::vector<std::vector<short>>& chamber, int& maxHeight);