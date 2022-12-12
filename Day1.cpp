#include "Day1.h"
#include <iostream>
#include <algorithm>

int day1P1(std::vector<std::string> input) {
	std::cout << "Starting process\n";
	double maxPos{ 0 };
	std::vector<int> values{ getValues(input, &maxPos) };

	std::cout << "Processing done\n";

	return *std::max_element(values.begin(), values.end());
}

int day1P2(std::vector<std::string> input) {
	std::cout << "Starting process\n";
	double maxPos{ 0 };
	std::vector<int> values{ getValues(input, &maxPos) };

	std::cout << "Processing done\n";

	return findSum3Higher(values);
}

std::vector<int> getValues(std::vector<std::string> input, double* maxPosPtr) {
	std::vector<int> values{ {} };

	int line{ 0 };
	do {
		std::cout << "Elf n°" << values.size() << " .";

		int val{ 0 };
		while (line < input.size() && input[line] != "") {
			std::cout << "|";
			val += std::stoi(input[line]);
			line++;
		}
		values.push_back(val);
		if (val >= values[*maxPosPtr]) {
			*maxPosPtr = values.size();
		}
		line++;
		std::cout << ". has " << val << "\n";
	} while (line < input.size());

	return values;
}

int findSum3Higher(std::vector<int> values) {
	int fst{ 0 };
	int scd{ 0 };
	int trd{ 0 };

	for (int value: values) {
		if (value > fst) {
			trd = scd;
			scd = fst;
			fst = value;
		}
		else if (value > scd) {
			trd = scd;
			scd = value;
		}
		else if (value > trd) {
			trd = value;
		}
	}
	return fst + scd + trd;
}