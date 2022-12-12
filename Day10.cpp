#include "Day10.h"

#include <iostream>

int day10P1(std::vector<std::string> input) {
	int cycle{ 1 };
	int regX{ 1 };
	int score{ 0 };

	for (std::string line : input) {
		testCycle(&score, ++cycle, regX);

		if (line[0] == 'a') {
			regX += std::stoi(line.substr(5, line.size() - 5));
			testCycle(&score, ++cycle, regX);
		}
	}
	return score;
}

void testCycle(int* score, int cycle, int reg) {
	if ((cycle + 20) % 40 == 0) {
		*score += cycle * reg;
		std::cout << "On cycle " << cycle << ", reg is at " << reg << '\n';
	}
}

int day10P2(std::vector<std::string> input) {
	int cycle{ 1 };
	int regX{ 1 };
	bool newOp{ true };

	auto it = input.begin();

	do {
		// CRT draw
		int crt = cycle % 40 - 1;
		if (crt == 0) std::cout << "\n";
		if (std::abs(crt - regX) < 2) std::cout << "#";
		else std::cout << ".";

		// Instruction read
		if (it->at(0) == 'a') {
			if (!newOp) {
				regX += std::stoi(it->substr(5, it->size() - 5));
				newOp = true;
			}
			else newOp = false;
		}
		if (newOp) it++;
		
		cycle++;
	} while (it != input.end());

	std::cout << "\n\n";
	return 0;
}