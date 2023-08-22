#pragma once

#include <string>
#include <vector>
#include <map>
#include <array>

struct valve {
	const char stream;
	std::vector<short> neighbours;

	explicit valve(char stream) : stream{ stream } {};
};
using network_t = std::map<short, valve>;

using valvesStates_t = std::map<short, std::array<bool, 30>>;

int day16P1(std::vector<std::string> const& input);

network_t getNetwork(std::vector<std::string> const& input);

int findMaxStream(short start, network_t const& network, valvesStates_t& valvesStates, char time);

short hashValveName(std::string const& name);

valvesStates_t initValvesStates(network_t const& network);
void openValve(short valveId, valvesStates_t& valvesStates, char time, bool open);
