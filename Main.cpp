#include "inputReader.h"
#include <iostream>
#include <string>

#include "Day17.h"

int main() {
	auto res{ day17P1(readInputFile("input.txt")) };
	std::cout << "\nResult: " << res << "\n";
}