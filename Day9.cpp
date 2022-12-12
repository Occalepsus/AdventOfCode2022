#include "Day9.h"

#include <iostream>

int day9P1(std::vector<std::string> input) {
	Rope* rope{ new Rope() };

	for (std::string move : input) {
		int dist = move.length() == 4 ? 10 * move[2] + move[3] - 528 : move[2] - 48;
		rope->move(move[0], dist);
		std::cout << "Moved to " << rope->hx << ", " << rope->hy << "\n";
	}

	return rope->calcTrail();
}

constexpr int length = 10;

int day9P2(std::vector<std::string> input) {
	Rope2<length>* rope{ new Rope2<length>() };

	for (std::string move : input) {
		int dist = move.length() == 4 ? 10 * move[2] + move[3] - 528 : move[2] - 48;
		rope->move(move[0], dist);
		std::cout << move << '\n';
		std::cout << "Tale at " << rope->xPos->at(length - 1) << ", " << rope->yPos->at(length - 1) << "\n";
	}

	return rope->calcTrail();
}

int sign(int x) {
	return x > 0 ? 1 : x < 0 ? -1 : 0;
}

int Rope::length() {
	return std::max(std::abs(hx - tx), std::abs(hy - ty));
}

void Rope::move(char dir, int dist) {
	for (int i{ 0 }; i < dist; i++) {
		int ox{ hx }, oy{ hy };

		switch (dir)
		{
		case 'U':
			hy++;
			break;
		case 'R':
			hx++;
			break;
		case 'D':
			hy--;
			break;
		case 'L':
			hx--;
			break;
		default:
			break;
		}

		if (length() > 1) {
			tx = ox;
			ty = oy;
		}

		xTrail->push_back(tx);
		yTrail->push_back(ty);
	}
}

int Rope::calcTrail() {
	int score{ 0 };
	for (int elt{ 0 }; elt < xTrail->size(); elt++) {
		for (int comp{ 0 }; comp < elt; comp++) {
			if (xTrail->at(elt) == xTrail->at(comp) && yTrail->at(elt) == yTrail->at(comp)) goto exit;
		}
		score++;
	exit:
		continue;
	}

	return score;
}

template<size_t s>
void Rope2<s>::pull(size_t node) {
	int px{ xPos->at(node) - xPos->at(node + 1) };
	int py{ yPos->at(node) - yPos->at(node + 1) };

	int str = std::abs(px) + std::abs(py);

	if (str > 2) {
		px -= sign(px);
		py -= sign(py);
	}
	else if (std::abs(px) > 1) {
		px -= sign(px);
	}
	else if (std::abs(py) > 1) {
		py -= sign(py);
	}

	xPos->at(node + 1) = xPos->at(node) - px;
	yPos->at(node + 1) = yPos->at(node) - py;
}

template<size_t s>
void Rope2<s>::move(char dir, int dist) {
	for (int i{ 0 }; i < dist; i++) {
		switch (dir) {
		case 'U':
			yPos->at(0)++;
			break;
		case 'R':
			xPos->at(0)++;
			break;
		case 'D':
			yPos->at(0)--;
			break;
		case 'L':
			xPos->at(0)--;
			break;
		default:
			break;
		}

		for (int node{ 0 }; node < s - 1; node++) {
			pull(node);
		}

		xTrail->push_back(xPos->at(s - 1));
		yTrail->push_back(yPos->at(s - 1));
	}
}

template<size_t s>
int Rope2<s>::calcTrail() {
	int score{ 0 };
	for (int elt{ 0 }; elt < xTrail->size(); elt++) {
		for (int comp{ 0 }; comp < elt; comp++) {
			if (xTrail->at(elt) == xTrail->at(comp) && yTrail->at(elt) == yTrail->at(comp)) goto exit;
		}
		score++;
	exit:
		continue;
	}

	return score;
}