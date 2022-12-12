#include "inputReader.h"
#include <iostream>
#include <string>

#include "Day11.h"

int main() {
	auto res{ day11P2(readInputFile("input.txt")) };
	std::cout << "\nResult: " << res << "\n";
}