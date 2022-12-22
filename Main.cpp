#include "inputReader.h"
#include <iostream>
#include <string>

#include "Day18.h"

int main() {
	auto res{ day18P1(readInputFile("input.txt")) };
	std::cout << "\nResult: " << res << "\n";
}