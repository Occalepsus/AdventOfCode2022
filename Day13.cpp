#include "Day13.h"

#include <iostream>
#include <sstream>
#include <algorithm>

int day13P1(std::vector<std::string> input) {
	nestedList uList{}, dList{};
	bool isUp{ true };

	size_t score{ 0 };
	int pairId{ 1 };
	for (auto& line : input) {
		if (line.size() < 2) isUp = true;
		else if (isUp) {
			std::cout << "\nDealing pair " << pairId;
			isUp = false;
			uList = parseToNList(line);
		}
		else {
			dList = parseToNList(line); 

			if (uList < dList) {
				std::cout << "\t-> is good";
				score += pairId;
			}
			pairId++;
		}
	}

	return score;
}

int day13P2(std::vector<std::string> input) {
	std::vector<nestedList> packets{};
	nestedList corr1{ parseToNList("[[2]]") }, corr2{ parseToNList("[[6]]") };
	packets.push_back(corr1);
	packets.push_back(corr2);

	for (auto& line : input) {
		if (line.size() > 1) {
			packets.push_back(parseToNList(line));
		}
	}

	std::sort(packets.begin(), packets.end());

	int score{ 1 };
	for (int i{ 0 }; i < packets.size(); i++) {
		const std::string val{ packets[i].toString() };
		std::cout << val << '\n';
		
		if (val == "[[[[[2]]]]]" || val == "[[[[[6]]]]]") {
			score *= i + 1; 
			std::cout << "Line " << i + 1 << " ^^^^^^^^\n";
		}
	}

	return score;
}

nestedList parseToNList(std::string input) {
	nestedList nList{};
	size_t pos{ 0 };

	while (pos < input.size()) {
		if (input[pos] == '[') {
			size_t close{ pos };
			int nest{ 1 };
			while (++close < input.size()) {
				if (input[close] == '[') nest++;
				else if (input[close] == ']') nest--;
				if (nest == 0) break;
			}
			nList.add(parseToNList(input.substr(pos + 1, close - pos - 1)));
			pos = close + 1;
		}
		else if (input[pos] == ',') pos++;
		else {
			if ('0' <= input[pos + 1] && input[pos + 1] <= '9') {
				nList.add(nestedList(std::stoi(input.substr(pos, 2))));
				pos += 2;
			}
			else {
				nList.add(nestedList(input[pos] - '0'));
				pos++;
			}
		}
	}
	return nList;
}
