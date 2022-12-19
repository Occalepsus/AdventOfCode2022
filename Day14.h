#pragma once

#include <vector>
#include <string>
#include <queue>

enum Tile {
	Empty,
	Rock,
	Sand
};

using caveMap = std::vector<std::vector<Tile>>;
using rockLine = std::vector<unsigned short>;

int day14P1(std::vector<std::string> input);
int day14P2(std::vector<std::string> input);

static size_t def = 0;
caveMap createMap(std::vector<std::string>& input, size_t& maxDepth = def);

unsigned short getValue(std::queue<char>& stack);