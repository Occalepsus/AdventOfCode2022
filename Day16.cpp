#include "Day16.h"

#include <iostream>
#include <regex>

int day16P1(const std::vector<std::string>& input) {
	std::vector<valveNetwork> network{ getNetwork(input) };

	return findMaxStream(0, network, std::vector<bool>(network.size(), false), 20);
}

std::vector<valveNetwork> getNetwork(const std::vector<std::string>& input) {
	std::vector<valveNetwork> network(std::vector<valveNetwork>(26 * 26));

	std::regex regexLine{ std::regex("Valve ([A-Z]{2}) has flow rate=([0-9]+); tunnel(?:s?) lead(?:s?) to valve(?:s?) ((?:(?:[A-Z]{2})(?:, )?)+)") };
	std::regex regexTo{ std::regex("([A-Z]{2})") };
	for (auto& line : input) {
		std::smatch matchLine;
		std::smatch matchTo;
		std::regex_match(line, matchLine, regexLine);

		short valveId{ (matchLine[1].str()[0] - 'A') * 26 + matchLine[1].str()[1] - 'A' };
		char stream{ static_cast<char>(std::stoi(matchLine[2].str())) };
		network[valveId].stream = stream;

		std::string list{ matchLine[3].str() };
		do {
			std::regex_search(list, matchTo, regexTo);
			network[valveId].reachable.push_back(static_cast<short>(matchTo[1].str()[0] - 'A') * 26 + matchTo[1].str()[1] - 'A');
			list = matchTo.suffix();
		} while (list.length() > 0);
	}

	return network;
}

int findMaxStream(short start, std::vector<valveNetwork>& network, std::vector<bool> openValves, char time) {
	if (time == 1) {
		if (!openValves[start]) {
			openValves.push_back(start);
			return network[start].stream;
		}
		else return 0;
	}
	else if (time > 1) {
		int max{};
		std::vector<bool> newOpenValves{};
		for (auto& valve : network[start].reachable) {
			std::vector<bool> openValvesWith{ openValves }, openValvesWithout{ openValves };
			int streamWith{ findMaxStream(valve, network, openValvesWith, time - 1) };
			int streamWithout{ openValves[valve] && network[valve].stream > 0 ? findMaxStream(valve, network, openValvesWithout, time - 2) + network[valve].stream : 0};
			
			if (streamWith > max) {
				max = streamWith;
				newOpenValves = openValvesWith;
			}
			if (streamWithout > max) {
				max = streamWithout;
				newOpenValves = openValvesWithout;
			}
		}
		openValves = newOpenValves;
		return max;
	}
	else {
		throw std::out_of_range("time parameter is null or negative, which is not possible");
	}
}