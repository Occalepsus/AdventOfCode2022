#include "Day16.h"

#include <iostream>
#include <regex>

int day16P1(std::vector<std::string> const& input) {
	auto network{ getNetwork(input) };

	auto valvesStates{ initValvesStates(network) };

	std::cout << "Network created.\nBeginning calculations.\n";

	return findMaxStream(0, network, valvesStates, 0);
}

network_t getNetwork(std::vector<std::string> const& input) {
	// Construct a new network, with the same size as the input
	auto network{ network_t() };
	auto rawNeighbours{ std::map<short, std::string>() };

	// First getting all valves and their neighbours as raw string
	std::regex regexLine{ std::regex("Valve ([A-Z]{2}) has flow rate=([0-9]+); tunnel(?:s?) lead(?:s?) to valve(?:s?) ((?:(?:[A-Z]{2})(?:, )?)+)") };
	for (auto& line : input) {
		std::smatch matchLine;
		std::regex_match(line, matchLine, regexLine);

		short valveId{ hashValveName(matchLine[1]) };
		char stream{ static_cast<char>(std::stoi(matchLine[2].str())) };
		
		// Adding the valve at the valveId, with the stream as the flow rate
		network.try_emplace(valveId, stream);
		rawNeighbours.try_emplace(valveId, matchLine[3].str());
	}

	// Then getting all neighbours for each valve from raw string
	std::regex regexTo{ std::regex("([A-Z]{2})") };
	for (auto& [valveId, list] : rawNeighbours) {
		std::smatch matchTo;
		do {
			std::regex_search(list, matchTo, regexTo);
			network.at(valveId).neighbours.push_back(hashValveName(matchTo[1].str()));
			list = matchTo.suffix();
		} while (list.length() > 0);
	}

	return network;
}

int findMaxStream(short start, network_t const& network, valvesStates_t& valvesStates, char time) {
	int maxStream{};

	valve const& startValve{ network.at(start) };

	// First by opening the valve
	if (startValve.stream > 0 && valvesStates[start][time]) {
		if (time == 29) {
			return startValve.stream;
		}
		else {
			openValve(start, valvesStates, time, false);
			if (int stream{ findMaxStream(start, network, valvesStates, time + 1) + startValve.stream }; stream > maxStream) {
				maxStream = stream;
			}
			// Reset the valve state
			openValve(start, valvesStates, time, true);
		}
		if (time < 5) {
			std::cout << "Opened valve " << start << " at time " << static_cast<int>(time) << "\n";
			std::cout << "Actual score " << maxStream << "\n";
		}
	}

	// Second by opening the neighbours
	if (time < 29) {
		for (auto& neighbour : startValve.neighbours) {
			if (int stream{ findMaxStream(neighbour, network, valvesStates, time + 1) }; stream > maxStream) {
				maxStream = stream;
			}
		}
	}

	return maxStream;
}


short hashValveName(std::string const& name) {
	return static_cast<short>(name[0] - 'A') * 26 + name[1] - 'A';
}
valvesStates_t initValvesStates(network_t const& network) {
	valvesStates_t valvesStates;
	for (auto& [valveId, _] : network) {
		valvesStates.try_emplace(valveId /* emplacing a default constructed object */);
		for (int i{}; i < 20; i++) {
			valvesStates[valveId][i] = true;
		}
	}
	return valvesStates;
}
void openValve(short valveId, valvesStates_t& valvesStates, char time, bool open) {
	auto& states{ valvesStates[valveId] };
	for (int i{ time }; i < 20; i++) {
		states[i] = open;
	}
}

//void resetValvesStates(valvesStates_t& valvesStates, int time) {
//	for (auto& [_, states] : valvesStates) {
//		// Resetting it to the previous state (or true if time == 0)
//		states[time] = time == 0 ? true : states[static_cast<size_t>(time) - 1];
//	}
//}