#include "Day6.h"

#include <iostream>
#include <deque>

int day6P1(std::vector<std::string> input) {
	std::string stream = input[0];

	int goodCharCount{ 0 };
	for (int cursor{ 0 }; cursor < stream.length() - 4; cursor++) {
		std::cout << "Cursor: " << cursor << " character " << stream[cursor] << "\ncomp char ";
		for (int testPos{ cursor + 1 }; testPos < cursor + 4; testPos++) {
			std::cout << stream[testPos];
			if (stream[cursor] == stream[testPos]) {
				std::cout << " XXX\n";
				goodCharCount = 0;
				goto notGood;
			}
		}
		std::cout << " VVV, goodCharCount is " << goodCharCount << "\n";
		if (goodCharCount++ == 4) {
			std::cout << "Found at pos " << cursor << " with sequence " << stream.substr(cursor - 4, 4) << "\n";
			return cursor;
		}		
	notGood:
		continue;
	}
	
	return 0;
}

int day6P2(std::vector<std::string> input, int qtt) {
	std::string stream = input[0];

	std::deque<char> seqBuffer;
	for (int cursor{ 0 }; cursor < stream.length(); cursor++) {
		std::cout << "Cursor: " << cursor << " character " << stream[cursor] << "\ncomp char ";

		std::deque<char> checkBuffer;
		while (!seqBuffer.empty()) {
			char c{ seqBuffer.back() };
			seqBuffer.pop_back();

			if (c != stream[cursor]) {
				checkBuffer.push_front(c);
			}
			else {
				checkBuffer.clear();
			}
		}

		std::cout << "Buffer is now [";
		while (!checkBuffer.empty()) {
			char c{ checkBuffer.front() };
			std::cout << c;

			seqBuffer.push_back(c);
			checkBuffer.pop_front();
		}
		char c{ stream[cursor] };
		seqBuffer.push_front(c);
		std::cout << c << "], at position " << cursor << " of size " << seqBuffer.size() << "\n";

		if (seqBuffer.size() >= qtt) {
			std::cout << "Sequence found !\n";
			return cursor + 1;
		}
	}

	return 0;
}