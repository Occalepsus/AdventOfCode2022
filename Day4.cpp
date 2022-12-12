#include "Day4.h"

#include <iostream>

int day4P2(std::vector<std::string> input) {
	int score{ 0 };
	
	for (std::string line : input) {
		int min1, max1;
		int min2, max2;

		const int ret{ sscanf_s(line.c_str(), "%d-%d,%d-%d", &min1, &max1, &min2, &max2) };

		if (ret != 4) {
			throw std::exception("Input scan error.");
		}
		
		std::cout << "Fst ";
		for (int i{ 0 }; i < 100; i++) {
			if (min1 <= i && i <= max1) {
				std::cout << '-';
			}
			else {
				std::cout << '.';
			}
		}
		std::cout << "\nScd ";
		for (int i{ 0 }; i < 100; i++) {
			if (min2 <= i && i <= max2) {
				std::cout << '-';
			}
			else {
				std::cout << '.';
			}
		}
		if (std::max(max1, max2) - std::min(min1, min2) <= max1 - min1 + max2 - min2 ) {
			score++;
			std::cout << "\n\t==> True\n";
		}
		else {
			std::cout << "\n\t==> False\n";
		}
	}

	return score;
}