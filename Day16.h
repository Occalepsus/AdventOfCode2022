#pragma once

#include <string>
#include <vector>

struct valveNetwork {
	char stream;
	std::vector<short> reachable;

	valveNetwork() : stream(0) {};
	valveNetwork(char value) : stream(value) {};
};

int day16P1(const std::vector<std::string>& input);

std::vector<valveNetwork> getNetwork(const std::vector<std::string>& input);

int findMaxStream(short start, std::vector<valveNetwork>& network, std::vector<bool> openValves, char time);