#include "inputReader.h"
#include <iostream>
#include <string>

#include "Day13.h"

int main() {
	auto res{ day13P2(readInputFile("input.txt")) };
	std::cout << "\nResult: " << res << "\n";
}