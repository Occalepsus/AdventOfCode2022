#pragma once

#include <vector>
#include <string>
#include <deque>

struct Coord {
	int x;
	int y;
	Coord() : x(0), y(0) {}
	Coord(int x, int y) : x(x), y(y) {}
};
struct Coord2 {
	char x;
	char y;
	Coord2() : x(0), y(0) {}
	Coord2(char x, char y) : x(x), y(y) {}
};

using Rock = std::vector<Coord>;
using Rock2 = std::vector<Coord2>;

int day17P1(const std::vector<std::string>& input);

void rockFall(std::vector<std::vector<short>>&, const std::vector<Rock>&, const std::vector<std::string>&, int&, char, size_t&);

int day17P2(const std::vector<std::string>& input);

void rockFallP2(std::vector<std::deque<short >> &, const std::vector<Rock2>&, const std::vector<std::string>&, size_t&, size_t&, char, size_t&);

void displayRocks(std::vector<std::vector<short>>& chamber, int& maxHeight);