#pragma once

#include "Item.h"

#include <vector>
#include <string>
#include <array>
#include <memory>

constexpr size_t forest_size = 99;

struct tree {
	int size{ 0 };
	int row{ 0 };
	int col{ 0 };

	int visible[4]{ 0, 0, 0, 0 };
	bool hidden() {
		return visible[0] || visible[1] || visible[2] || visible[3];
	}
	int score() {
		return visible[0] * visible[1] * visible[2] * visible[3];
	}

	tree() {}
	tree(int s) : size{ s } {}
	tree(int r, int c, int s) : row{ r }, col{ c }, size{ s } {}
};

using forest = std::array<std::array<tree*, forest_size>, forest_size>;

int day8P1(std::vector<std::string> input);
int day8P2(std::vector<std::string> input);

std::unique_ptr<forest> getForest(std::vector<std::string> input);