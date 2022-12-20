#include "inputReader.h"
#include <iostream>
#include <string>

#include "Day16.h"

int main() {
	auto res{ day16P1(readInputFile("input.txt")) };
	std::cout << "\nResult: " << res << "\n";
}