#include "Day17.h"

#include <iostream>

const short fallingRocks = 2022;
const size_t fallingRocks2 = 10;//1000000000000;

const short buffer = 1000;

int day17P1(const std::vector<std::string>& input) {
	/*
	 r1:	####
	 
			.#.
	 r2:	###
			.#.
	
			..#
	 r3:	..#
			###
	
			#
	 r4:	#
			#
			#
	
	 r5:	##
			##
	*/

	const std::vector<Rock> rocks{
		std::vector<Rock>({
			Rock({Coord(0, 0), Coord(1, 0), Coord(2, 0), Coord(3, 0)}),
			Rock({Coord(0, 1), Coord(1, 0), Coord(1, 1), Coord(1, 2), Coord(2, 1)}),
			Rock({Coord(0, 0), Coord(1, 0), Coord(2, 0), Coord(2, 2), Coord(2, 1)}),
			Rock({Coord(0, 0), Coord(0, 1), Coord(0, 3), Coord(0, 2)}),
			Rock({Coord(0, 0), Coord(1, 0), Coord(0, 1), Coord(1, 1)})
		}
	) };

	std::vector<std::vector<short>> chamber(7);
	int maxHeight{ 0 };
	size_t curSteam{ 0 };

	for (short i{ 0 }; i < fallingRocks; i++) {
		while (chamber[0].size() < maxHeight + 7) chamber[0].push_back(0);
		while (chamber[1].size() < maxHeight + 7) chamber[1].push_back(0);
		while (chamber[2].size() < maxHeight + 7) chamber[2].push_back(0);
		while (chamber[3].size() < maxHeight + 7) chamber[3].push_back(0);
		while (chamber[4].size() < maxHeight + 7) chamber[4].push_back(0);
		while (chamber[5].size() < maxHeight + 7) chamber[5].push_back(0);
		while (chamber[6].size() < maxHeight + 7) chamber[6].push_back(0);

		rockFall(chamber, rocks, input, maxHeight, i % 5, curSteam);
	}
	displayRocks(chamber, maxHeight);

	return maxHeight;
}

void rockFall(std::vector<std::vector<short>>& chamber, const std::vector<Rock>& rocks, const std::vector<std::string>& input, int& maxHeight, char sel, size_t& curSteam) {
	Coord pos{ 2, maxHeight + 4 };

	bool placed{ false };
	while (!placed) {
		// Tombe
		pos.y--;

		// Poussé par le vent
		bool stuck{ false };
		int dir{ input[0][curSteam] == '<' ? -1 : 1 };
		if (dir == -1 && pos.x == 0) stuck = true;
		else if (dir == 1 && pos.x + rocks[sel][rocks[sel].size() - 1].x == 6) stuck = true;

		if (!stuck) {
			for (auto& c : rocks[sel]) {
				if (chamber[pos.x + c.x + dir][pos.y + c.y] > 0) {
					stuck = true;
					break;
				}
			}
		}
		if (!stuck) pos.x += dir;

		for (auto& c : rocks[sel]) {
			if (pos.y == 0 || chamber[pos.x + c.x][pos.y + c.y - 1] > 0) {
				for (auto& c : rocks[sel]) chamber[pos.x + c.x][pos.y + c.y] = sel + 1;
				placed = true;
				break;
			}
		}

		// Steam change
		curSteam = (curSteam + 1) % input[0].size();
	}

	maxHeight = std::max(maxHeight, pos.y + rocks[sel][rocks[sel].size() - 2].y + 1);
}

int day17P2(const std::vector<std::string>& input) {
	const std::vector<Rock2> rocks{
		std::vector<Rock2>({
			Rock2({Coord2(0, 0), Coord2(1, 0), Coord2(2, 0), Coord2(3, 0)}),
			Rock2({Coord2(0, 1), Coord2(1, 0), Coord2(1, 1), Coord2(1, 2), Coord2(2, 1)}),
			Rock2({Coord2(0, 0), Coord2(1, 0), Coord2(2, 0), Coord2(2, 2), Coord2(2, 1)}),
			Rock2({Coord2(0, 0), Coord2(0, 1), Coord2(0, 3), Coord2(0, 2)}),
			Rock2({Coord2(0, 0), Coord2(1, 0), Coord2(0, 1), Coord2(1, 1)})
		}
	) };

	std::vector<std::deque<short>> chamber(7, std::deque<short>(buffer + 10, 0));
	size_t maxHeight{ 0 };
	size_t bottomHeight{ 0 };
	size_t curSteam{ 0 };

	for (size_t i{ 0 }; i < fallingRocks2; i++) {
		while (bottomHeight + buffer < maxHeight) {
			chamber[0].push_front(0);
			chamber[1].push_front(0);
			chamber[2].push_front(0);
			chamber[3].push_front(0);
			chamber[4].push_front(0);
			chamber[5].push_front(0);
			chamber[6].push_front(0);

			chamber[0].pop_back();
			chamber[1].pop_back();
			chamber[2].pop_back();
			chamber[3].pop_back();
			chamber[4].pop_back();
			chamber[5].pop_back();
			chamber[6].pop_back();

			bottomHeight++;
		}

		rockFallP2(chamber, rocks, input, maxHeight, bottomHeight, i % 5, curSteam);
	}
	//displayRocks(chamber, maxHeight);

	return maxHeight;
}

void rockFallP2(std::vector<std::deque<short>>& chamber, const std::vector<Rock2>& rocks, const std::vector<std::string>& input, size_t& maxHeight, size_t& bottomHeight, char sel, size_t& curSteam) {
	char posX{ 2 };
	size_t posY{ maxHeight + 4 };

	bool placed{ false };
	while (!placed) {
		// Falls
		posY--;

		// Pushed by steam
		bool stuck{ false };
		int dir{ input[0][curSteam] == '<' ? -1 : 1 };
		if (dir == -1 && posX == 0) stuck = true;
		else if (dir == 1 && posX + rocks[sel][rocks[sel].size() - 1].x == 6) stuck = true;

		if (!stuck) {
			for (auto& c : rocks[sel]) {
				if (chamber[posX + c.x + dir][posY - bottomHeight + c.y] > 0) {
					stuck = true;
					break;
				}
			}
		}
		if (!stuck) posX += dir;

		for (auto& c : rocks[sel]) {
			if (posY - bottomHeight == 0 || chamber[posX + c.x][posY - bottomHeight + c.y - 1] > 0) {
				// test if block is lost
				if (bottomHeight != 0 && posY - bottomHeight <= 0) {
					placed = true;
					break;
				}
				// place the block
				for (auto& c : rocks[sel]) chamber[posX + c.x][posY - bottomHeight + c.y] = sel + 1;
				placed = true;
				break;
			}
		}

		// Steam change
		curSteam = (curSteam + 1) % input[0].size();
	}

	maxHeight = std::max(maxHeight, posY + rocks[sel][rocks[sel].size() - 2].y + 1);
}

void displayRocks(std::vector<std::vector<short>>& chamber, int& maxHeight) {
	for (int l{ maxHeight + 2 }; l >= 0; l--) {
		std::cout << "|";
		for (short p{ 0 }; p < 7; p++) {
			char c{ chamber[p][l] == 0 ? '.' : (char)chamber[p][l] + '0' };
			std::cout << c;
		}
		std::cout << "|\n";
	}
	std::cout << "---------\n";
}