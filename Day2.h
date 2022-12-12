#pragma once

#include <vector>
#include <string>

enum RPS {
	Rock,
	Paper,
	Scissors
};

int day2P1(std::vector<std::string> input);
int day2P2(std::vector<std::string> input);

RPS decode(char c);
RPS adapt(char c, RPS pivot);