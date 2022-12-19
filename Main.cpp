#include "inputReader.h"
#include <iostream>
#include <string>

#include "Day15.h"

int main() {
	auto res{ day15P2(readInputFile("input.txt")) };
	std::cout << "\nResult: " << res << "\n";
}