#include "Day2.h"
#include <iostream>

int day2P1(std::vector<std::string> input) {
	const auto size{ input.size() };
	RPS* s1 = new RPS[size];
	RPS* s2 = new RPS[size];

	for (int i = 0; i < size; i++) {
		s1[i] = decode(input[i][0]);
		s2[i] = decode(input[i][2]);
	}

	int score{ 0 };
	for (int i = 0; i < size; i++) {
		int add{ s2[i] + 1 };
		switch ((s2[i] - s1[i] + 3) % 3) {
		case 0:
			add += 3;
			std::cout << s1[i] << " " << s2[i] << "\t -> Tie, score " << add << "\n";
			break;
		case 1:
			add +=6;
			std::cout << s1[i] << " " << s2[i] << "\t -> Win, score " << add << "\n";
			break;
		case 2:
			std::cout << s1[i] << " " << s2[i] << "\t -> Los, score " << add << "\n";
			break;
		default:
			std::cout << "Error : " << (s2[i] - s1[i] + 3) % 3 << "\n";
			break;
		}
		score += add;
	}

	return score;
}

int day2P2(std::vector<std::string> input) {
	const auto size{ input.size() };
	RPS* s1 = new RPS[size];
	RPS* s2 = new RPS[size];

	for (int i = 0; i < size; i++) {
		s1[i] = decode(input[i][0]);
		s2[i] = adapt(input[i][2], s1[i]);
	}

	int score{ 0 };
	for (int i = 0; i < size; i++) {
		int add{ s2[i] + 1 };
		switch ((s2[i] - s1[i] + 3) % 3) {
		case 0:
			add += 3;
			std::cout << s1[i] << " " << s2[i] << "\t -> Tie, score " << add << "\n";
			break;
		case 1:
			add += 6;
			std::cout << s1[i] << " " << s2[i] << "\t -> Win, score " << add << "\n";
			break;
		case 2:
			std::cout << s1[i] << " " << s2[i] << "\t -> Los, score " << add << "\n";
			break;
		default:
			std::cout << "Error : " << (s2[i] - s1[i] + 3) % 3 << "\n";
			break;
		}
		score += add;
	}

	return score;
}

RPS decode(char c) {
	switch (c) {
	case 'A':
	case 'X':
		return Rock;
	case 'B':
	case 'Y':
		return Paper;
	case 'C':
	case 'Z':
		return Scissors;
	default:
		throw std::invalid_argument("input is not valid. Must be 'A', 'B', 'C', 'X', 'Y' or 'Z'.");
	}
}

RPS adapt(char i, RPS pivot) {
	switch (i) {
	case 'X':
		return static_cast<RPS>((pivot + 2) % 3);
	case 'Y':
		return pivot;
	case 'Z':
		return static_cast<RPS>((pivot + 1) % 3);
	default:
		throw std::invalid_argument("input is not valid. Must be 'A', 'B', 'C', 'X', 'Y' or 'Z'.");
	}
}