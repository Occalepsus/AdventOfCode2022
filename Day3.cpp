#include "Day3.h"

#include <iostream>
#include <iomanip>
#include <cstddef>

int day3P1(std::vector<std::string> input) {
	int score{ static_cast<int>(input.size()) };

	for (std::string line : input) {
		size_t mid{ line.size() / 2 };

		int freq1[26 * 2]{ 0 };
		int freq2[26 * 2]{ 0 };

		std::string firstHalf{ line.substr(0, mid) };
		std::string secondHalf{ line.substr(mid) };

		std::cout << firstHalf << '|' << secondHalf << std::setw(60 - line.size()) << "-> ";

		for (int i = 0; i < mid; i++) {
			int c1 = line[i] >= 'a' ? line[i] - 'a' : line[i] - 'A' + 26;
			freq1[c1]++;

			int c2 = line[mid + i] >= 'a' ? line[mid + i] - 'a' : line[mid + i] - 'A' + 26;
			freq2[c2]++;
		}

		for (int i{ 0 }; i < 26 * 2; i++) {
			if (freq1[i] * freq2[i] > 0) {
				score += i;
				
				std::cout << (char)(i < 26 ? i + 'a' : i + 'A' - 26) << " found in common.\n";
				break;
			}
		}
	}

	return score;
}

int day3P2(std::vector<std::string> input) {
	int score{ 0 };

	int count{ 0 };
	char freq[26 * 2]{ 0 };
	
	for (std::string line : input) {
		for (char ch : line) {
			int c = ch >= 'a' ? ch - 'a' : ch - 'A' + 26;
			if (c > 51) throw std::domain_error("Unsupported character in input.");
			freq[c] |= (1 << count);
		}
		if (count++ == 2) {
			count = 0;
			for (int c{ 0 }; c < 26 * 2; c++) {
				if (freq[c] == 7) {
					score += c + 1;
					std::cout << "Group, " << (char)(c < 26 ? c + 'a' : c + 'A' - 26) << " found in common.\n";
				}
				freq[c] = 0;
			}
		}
	}
	
	return score;
}