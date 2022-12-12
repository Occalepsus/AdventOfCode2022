#include "Day8.h"

#include <iostream>

//int day8P1(std::vector<std::string> input) {
//	forest forest{ getForest(input) };
//
//	int score{ 0 };
//	std::array<int, forest_size> rd{}, ru{}, cl{}, cr{};
//
//	for (int row{ 0 }; row < forest_size; row++) {
//		for (int col{ 0 }; col < forest_size; col++) {
//			if (forest[row][col].size > cl[row]) {
//				cl[row] = forest[row][col].size;
//				forest[row][col].visible[0] = true;
//			}
//			if (forest[row][col].size > ru[col]) {
//				ru[col] = forest[row][col].size;
//				forest[row][col].visible[1] = true;
//			}
//			if (forest[forest_size - row - 1][forest_size - col - 1].size > cr[row]) {
//				cr[row] = forest[forest_size - row - 1][forest_size - col - 1].size;
//				forest[forest_size - row - 1][forest_size - col - 1].visible[2] = true;
//			}
//			if (forest[forest_size - row - 1][forest_size - col - 1].size > rd[col]) {
//				rd[col] = forest[forest_size - row - 1][forest_size - col - 1].size;
//				forest[forest_size - row - 1][forest_size - col - 1].visible[3] = true;
//			}
//		}
//	}
//	for (int row{ 0 }; row < forest_size; row++) {
//		for (int col{ 0 }; col < forest_size; col++) {
//			if (forest[row][col].hidden()) {
//				score++;
//				std::cout << "o";
//			}
//			else std::cout << "x";
//		}
//		std::cout << '\n';
//	}
//	
//	return score;
//}

int day8P2(std::vector<std::string> input) {
	auto forest{ getForest(input) };

	int score{ 0 };

	for (int row{ 0 }; row < forest_size; row++) {
		for (int col{ 0 }; col < forest_size; col++) {
			int off{ 0 };
			while (off++ < col) {
				if ((*forest)[row][col]->size <=
					(*forest)[row][col - off]->size) {
					(*forest)[row][col]->visible[0] = off;
					break;
				}
			}
			if (off > col) (*forest)[row][col]->visible[0] = col;

			off = 0;
			while (off++ < col) {
				if ((*forest)[col][forest_size - row - 1]->size <=
					(*forest)[col - off][forest_size - row - 1]->size) {
					(*forest)[col][forest_size - row - 1]->visible[1] = off;
					break;
				}
			}
			if (off > col) (*forest)[col][forest_size - row - 1]->visible[1] = col;

			off = 0;
			while (off++ < col) {
				if ((*forest)[forest_size - row - 1][forest_size - col - 1]->size <=
					(*forest)[forest_size - row - 1][forest_size - col - 1 + off]->size) {
					(*forest)[forest_size - row - 1][forest_size - col - 1]->visible[2] = off;
					break;
				}
			}
			if (off > col) (*forest)[forest_size - row - 1][forest_size - col - 1]->visible[2] = col;

			off = 0;
			while (off++ < col) {
				if ((*forest)[forest_size - col - 1][row]->size <=
					(*forest)[forest_size - col - 1 + off][row]->size) {
					(*forest)[forest_size - col - 1][row]->visible[3] = off;
					break;
				}
			}
			if (off > col) (*forest)[forest_size - col - 1][row]->visible[3] = col;
		}
	}
	for (int row{ 0 }; row < forest_size; row++) {
		for (int col{ 0 }; col < forest_size; col++) {
			if ((*forest)[row][col]->score() > score)
				score = (*forest)[row][col]->score();
		}
	}

	return score;
}

std::unique_ptr<forest> getForest(std::vector<std::string> input) {
	auto forest = std::make_unique<std::array<std::array<tree*, forest_size>, forest_size>>();

	for (int row{ 0 }; row < forest_size; row++) {
		for (int col{ 0 }; col < forest_size; col++) {
			(*forest)[row][col] = new tree{row, col, input[row][col] - '0' + 1};
		}
	}

	return forest;
}