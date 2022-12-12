#include "Day5.h"

#include <iostream>
#include <deque>
#include <array>

#define slots 9

std::string day5P1(std::vector<std::string> input) {
	std::array<std::deque<char>, slots> stacks;

	std::cout << "Begin lines process :\n";

	bool createStack{ true };
	for (std::string line : input) {
		std::cout << "Line : " << line << "\n\t";
		if (createStack) {
			if (line[1] == '1') {
				std::cout << "is the separator\n";
				createStack = false;
				continue;
			}
			else {
				std::cout << "is a stack, of ";
				for (int i{ 0 }; i < slots; i++) {
					char c = line[i * 4 + 1];
					if (c != ' ') {
						stacks[i].push_back(c);
					}
					std::cout << c;
				}
				std::cout << "\n";
			}
		}
		else if (line.length() < 2) {
			std::cout << "is empty\n";
			continue;
		}
		else {
			int nb, from, to;

			const int ret{ sscanf_s(line.c_str(), "move %d from %d to %d", &nb, &from, &to) };			
			if (ret != 3) {
				std::cout << "is not valid\n";
				throw std::exception("Input scan error.");
			}
			std::cout << "is a move, from " << from << " to " << to << " of " << nb << " box.\n";
			from--, to--;
			
			for (int i{ 0 }; i < nb; i++) {
				if (!stacks[from].empty()) {
					std::cout << "moving " << stacks[from].front() << "\n";
					stacks[to].push_front(stacks[from].front());
					stacks[from].pop_front();
				}
			}
		}
	}

	std::string res;
	for (auto& stack : stacks) {
		res += stack.front();
	}
	return res;
}

std::string day5P2(std::vector<std::string> input) {
	std::array<std::deque<char>, slots> stacks;

	std::cout << "Begin lines process :\n";

	bool createStack{ true };
	for (std::string line : input) {
		std::cout << "Line : " << line << "\n\t";
		if (createStack) {
			if (line[1] == '1') {
				std::cout << "is the separator\n";
				createStack = false;
				continue;
			}
			else {
				std::cout << "is a stack, of ";
				for (int i{ 0 }; i < slots; i++) {
					char c = line[i * 4 + 1];
					if (c != ' ') {
						stacks[i].push_back(c);
					}
					std::cout << c;
				}
				std::cout << "\n";
			}
		}
		else if (line.length() < 2) {
			std::cout << "is empty\n";
			continue;
		}
		else {
			int nb, from, to;

			const int ret{ sscanf_s(line.c_str(), "move %d from %d to %d", &nb, &from, &to) };
			if (ret != 3) {
				std::cout << "is not valid\n";
				throw std::exception("Input scan error.");
			}
			std::cout << "is a move, from " << from << " to " << to << " of " << nb << " box.\n";
			from--, to--;

			std::deque<char> tmp;
			for (int i{ 0 }; i < nb; i++) {
				if (!stacks[from].empty()) {
					std::cout << "moving " << stacks[from].front() << "\n";
					tmp.push_front(stacks[from].front());
					stacks[from].pop_front();
				}
			}
			for (int i{ 0 }; i < nb; i++) {
				if (!tmp.empty()) {
					//std::cout << "moving " << tmp.front() << "\n";
					stacks[to].push_front(tmp.front());
					tmp.pop_front();
				}
			}
		}
	}

	std::string res;
	for (auto& stack : stacks) {
		res += stack.front();
	}
	return res;
}