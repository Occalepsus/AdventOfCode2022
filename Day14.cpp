#include "Day14.h"

#include <iostream>

int day14P1(std::vector<std::string> input) {
	caveMap map{ createMap(input) };
	
	int iterations{ 0 };
	while (true) {
		size_t cursorH{ 0 };
		size_t cursorW{ 100 };
		
		while (cursorH < 199) {
			if (map[cursorH + 1][cursorW] == Empty) {
				cursorH++;
				continue;
			}
			
			if (cursorW > 0 && map[cursorH + 1][cursorW - 1] == Empty) {
				cursorH++;
				cursorW--;
			}
			else if (cursorW < 200 && map[cursorH + 1][cursorW + 1] == Empty) {
				cursorH++;
				cursorW++;
			}
			else break;
		}
		if (cursorH == 199) break;
		map[cursorH][cursorW] = Sand;
		iterations++;
	}

	for (int i{ 0 }; i < 200; i++) {
		for (int j{ 0 }; j < 200; j++) {
			char c{};
			switch (map[i][j]) {
			case Empty:
				c = '.';
				break;
			case Rock:
				c = '#';
				break;
			case Sand:
				c = 'o';
				break;
			}
			std::cout << c;
		}
		std::cout << '\n';
	}

	return iterations;
}

int day14P2(std::vector<std::string> input) {
	size_t maxDepth{ 0 };
	caveMap map{ createMap(input, maxDepth) };

	for (int i{ 0 }; i < 200; i++) map[maxDepth + 2][i] = Rock;

	int iterations{ 0 };
	while (map[0][100] != Sand) {
		size_t cursorH{ 0 };
		size_t cursorW{ 100 };

		while (cursorH < 199) {
			if (cursorW == 199 || cursorW == 0) {
				iterations += maxDepth - cursorH + 1;
				break;
			}
			if (map[cursorH + 1][cursorW] == Empty) {
				cursorH++;
			}
			else if (cursorW > 0 && map[cursorH + 1][cursorW - 1] == Empty) {
				cursorH++;
				cursorW--;
			}
			else if (cursorW < 200 && map[cursorH + 1][cursorW + 1] == Empty) {
				cursorH++;
				cursorW++;
			}
			else break;
		}
		if (cursorH == 199) break;
		map[cursorH][cursorW] = Sand;
		iterations++;
	}

	for (int i{ 0 }; i < 200; i++) {
		for (int j{ 0 }; j < 200; j++) {
			char c{};
			switch (map[i][j]) {
			case Empty:
				c = '.';
				break;
			case Rock:
				c = '#';
				break;
			case Sand:
				c = 'o';
				break;
			}
			std::cout << c;
		}
		std::cout << '\n';
	}
	return iterations;
}

caveMap createMap(std::vector<std::string>& input, size_t& maxDepth) {
	caveMap map{ caveMap(200, std::vector<Tile>(200, Empty)) };

	for (auto& line : input) {
		rockLine rockH{};
		rockLine rockW{};
		
		std::queue<char> tempStack{};
		for (int pos{ 0 }; pos < line.size(); pos++) {
			if (line[pos] == '>') {
				rockH.push_back(getValue(tempStack));
				tempStack = std::queue<char>{};
			}
			else if (line[pos] == ',') {
				rockW.push_back(getValue(tempStack) - 400);
				tempStack = std::queue<char>{};
			}
			else if (line[pos] >= '0' && line[pos] <= '9') {
				tempStack.push(line[pos]);
			}
		}
		rockH.push_back(getValue(tempStack));

		for (size_t i{ 0 }; i < rockH.size() - 1; i++) {
			if (maxDepth < rockH[i]) maxDepth = rockH[i];

			if (rockH[i] == rockH[i + 1]) {
				for (size_t l{ std::min(rockW[i], rockW[i + 1]) }; l <= std::max(rockW[i], rockW[i + 1]); l++) {
					map[rockH[i]][l] = Rock;
				}
			}
			else if (rockW[i] == rockW[i + 1]) {
				for (size_t l{ std::min(rockH[i], rockH[i + 1]) }; l <= std::max(rockH[i], rockH[i + 1]); l++) {
					map[l][rockW[i]] = Rock;
				}
			}
			else throw std::exception("Erreur de lignes");
		}
	}
	return map;
}

unsigned short getValue(std::queue<char>& queue) {
	unsigned short value{ 0 };
	while (!queue.empty()) {
		value *= 10;
		value += queue.front() - '0';
		queue.pop();
	}
	return value;
}