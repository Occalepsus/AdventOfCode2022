#pragma once

#include <vector>
#include <array>
#include <string>

int day9P1(std::vector<std::string> input);
int day9P2(std::vector<std::string> input);

struct Rope {
	int hx, hy, tx, ty;
	std::vector<int>
		*xTrail{new std::vector<int>()},
		*yTrail{new std::vector<int>()};

	Rope(int hx, int hy, int tx, int ty) : hx(hx), hy(hy), tx(tx), ty(ty) {}
	Rope() : Rope(0, 0, 0, 0) {}

	int length();

	void move(char, int);

	int calcTrail();
};

template <size_t s>
struct Rope2 {
	std::array<int, s>
		* xPos{ new std::array<int, s>() },
		* yPos{ new std::array<int, s>() };
	std::vector<int>
		* xTrail{ new std::vector<int>() },
		* yTrail{ new std::vector<int>() };

	Rope2() {}

	void pull(size_t node);

	void move(char, int);

	int calcTrail();
};