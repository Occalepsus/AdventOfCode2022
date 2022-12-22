#include "Day18.h"

#include <iostream>

size_t day18P1(const std::vector<std::string>& input) {
	std::vector<Cube> cubes{};
	Grid grid{ getGrid(input, cubes) };

	size_t score{ 0 };
	for (auto& c : cubes) {
		auto a{ score };
		if (grid[c.x][c.y + 1][c.z + 1] == NULL) score++;
		if (grid[c.x + 2][c.y + 1][c.z + 1] == NULL) score++;
		
		if (grid[c.x + 1][c.y][c.z + 1] == NULL) score++;
		if (grid[c.x + 1][c.y + 2][c.z + 1] == NULL) score++;
		
		if (grid[c.x + 1][c.y + 1][c.z] == NULL) score++;
		if (grid[c.x + 1][c.y + 1][c.z + 2] == NULL) score++;
		//std::cout << "cube at " << (int)c.x << ", " << (int)c.y << ", " << (int)c.z << " has " << score - a << " faces\n";
	}
	
	return score;
}

size_t day18P2(const std::vector<std::string>& input) {
	std::vector<Cube> cubes{};
	Grid grid{ getGrid(input, cubes) };
	
	short connex{ 1 };
	for (auto& cube : cubes) {
		if (cube.connex == 0) {
			assignConnex(cube, grid, connex);
			connex++;
		}
	}

	size_t score{ 0 };
	for (short w{ 0 }; w < GRID_SIZE; w++) {
		for (short h{ 0 }; h < GRID_SIZE; h++) {
			// x+
			for (short d{ 0 }; d < GRID_SIZE; d++) {
				if (grid[w][h][d] != NULL) {
					score++;
					break;
				}
			}
			// x-
			for (short d{ 0 }; d < GRID_SIZE; d++) {
				if (grid[w][h][GRID_SIZE - 1 - d] != NULL) {
					score++;
					break;
				}
			}
			// y+
			for (short d{ 0 }; d < GRID_SIZE; d++) {
				if (grid[d][w][h] != NULL) {
					score++;
					break;
				}
			}
			// y-
			for (short d{ 0 }; d < GRID_SIZE; d++) {
				if (grid[GRID_SIZE - 1 - d][w][h] != NULL) {
					score++;
					break;
				}
			}
			// z+
			for (short d{ 0 }; d < GRID_SIZE; d++) {
				if (grid[h][d][w] != NULL) {
					score++;
					break;
				}
			}
			// z-
			for (short d{ 0 }; d < GRID_SIZE; d++) {
				if (grid[h][GRID_SIZE - 1 - d][w] != NULL) {
					score++;
					break;
				}
			}
		}
	}

	return score;
}

Grid getGrid(const std::vector<std::string>& input, std::vector<Cube>& cubes) {
	Grid grid{ Grid(GRID_SIZE, std::vector<std::vector<Cube*>>(GRID_SIZE, std::vector<Cube*>(GRID_SIZE))) };
	
	for (auto& line : input) {
		Cube* c{ new Cube(line) };
		cubes.push_back(*c);
		grid[c->x + 1][c->y + 1][c->z + 1] = c;
	}
	return grid;
}

void assignConnex(Cube& cube, Grid& grid, short connex) {
	if (cube.connex == 0) {
		cube.connex = connex;
		Cube* c;
		c = grid[cube.x][cube.y + 1][cube.z + 1];
		if (c != NULL && c->connex == 0) assignConnex(*c, grid, connex);

		c = grid[cube.x + 2][cube.y + 1][cube.z + 1];
		if (c != NULL && c->connex == 0) assignConnex(*c, grid, connex);

		c = grid[cube.x + 1][cube.y][cube.z + 1];
		if (c != NULL && c->connex == 0) assignConnex(*c, grid, connex);

		c = grid[cube.x + 1][cube.y + 2][cube.z + 1];
		if (c != NULL && c->connex == 0) assignConnex(*c, grid, connex);

		c = grid[cube.x + 1][cube.y + 1][cube.z];
		if (c != NULL && c->connex == 0) assignConnex(*c, grid, connex);

		c = grid[cube.x + 1][cube.y + 1][cube.z + 2];
		if (c != NULL && c->connex == 0) assignConnex(*c, grid, connex);
	}
}