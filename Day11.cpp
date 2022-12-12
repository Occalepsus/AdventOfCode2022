#include "Day11.h"

#include <iostream>
#include <regex>

//int day11P1(std::vector<std::string> input) {
//	auto monkeys{ new std::vector<Monkey> };
//	getMonkeys(input, monkeys);
//	monkeys->shrink_to_fit();
//
//	for (int i{ 0 }; i < 20; i++)
//		for (auto& m : *monkeys)
//			m.makeTurn();
//	
//	int fst{ 0 }, scd{ 0 };
//	for (auto& m : *monkeys) {
//		if (m.inspect > fst) {
//			scd = fst;
//			fst = m.inspect;
//		}
//		else if (m.inspect > scd)
//			scd = m.inspect;
//	}
//
//	return fst * scd;
//}

unsigned long long day11P2(std::vector<std::string> input) {
	auto monkeys{ new std::vector<Monkey> };
	getMonkeys2(input, monkeys);
	monkeys->shrink_to_fit();

	for (int i{ 0 }; i < 10000; i++)
		for (auto& m : *monkeys)
			m.makeTurn();

	int fst{ 0 }, scd{ 0 };
	for (auto& m : *monkeys) {
		if (m.inspect > fst) {
			scd = fst;
			fst = m.inspect;
		}
		else if (m.inspect > scd)
			scd = m.inspect;
	}

	std::cout << fst << ", " << scd << '\n';
	return fst * scd;
}

//void getMonkeys(std::vector<std::string> input, std::vector<Monkey>* monkeys) {
//	std::regex rgxMonkey("^Monkey ([0-9]+):");
//	std::regex rgxStart(R"(^  Starting items: ((?:(?:[0-9]+)(?:, )?)*))");
//	std::regex rgxOperation(R"(^  Operation: new = old (\*|\+) ([0-9]+|old))");
//	std::regex rgxTest(R"(^  Test: divisible by ([0-9]+))");
//	std::regex rgxTrue(R"(^    If true: throw to monkey ([0-9]+))");
//	std::regex rgxFalse(R"(^    If false: throw to monkey ([0-9]+))");
//
//	Monkey monkey;
//	std::queue<int>* items{};
//	int* ifTrue{ new int(0) }, * ifFalse{ new int(0) };
//	std::string op;
//	std::string opValue;
//	testFunction* testFunc{};
//
//	for (std::string line : input) {
//		std::smatch match;
//
//		if (std::regex_match(line, match, rgxMonkey)) {
//			items = new std::queue<int>();
//		}
//		else if (std::regex_match(line, match, rgxStart)) {
//			size_t pos = 0;
//			std::string s{ match[1].str() };
//			while ((pos = s.find(", ")) != std::string::npos) {
//				items->push(std::stoi(s.substr(0, pos)));
//				s.erase(0, pos + 2);
//			}
//			items->push(std::stoi(s));
//		}
//		else if (std::regex_match(line, match, rgxOperation)) {
//			op = match[1].str();
//			opValue = match[2].str();
//		}
//		else if (std::regex_match(line, match, rgxTest)) {
//			int div{ std::stoi(match[1].str()) };
//			if (op == "*") {
//				if (opValue == "old") {
//					testFunc = new testFunction([div](int* item) {
//						*item = * item * *item / 3;
//						return *item % div == 0;
//						});
//				}
//				else {
//					int value{ std::stoi(opValue) };
//					testFunc = new testFunction([div, value](int* item) {
//						*item = * item * value / 3;
//						return *item % div == 0;
//						});
//				}
//			}
//			else {
//				int value{ std::stoi(opValue) };
//				testFunc = new testFunction([div, value](int* item) {
//					*item = (*item + value) / 3;
//					return *item % div == 0;
//					});
//			}
//		}
//		else if (std::regex_match(line, match, rgxTrue)) {
//			ifTrue = new int(std::stoi(match[1].str()));
//		}
//		else if (std::regex_match(line, match, rgxFalse)) {
//			ifFalse = new int(std::stoi(match[1].str()));
//
//			monkey = Monkey(items, monkeys, *ifTrue, *ifFalse, testFunc);
//			monkeys->push_back(monkey);
//		}
//	}
//}

void getMonkeys2(std::vector<std::string> input, std::vector<Monkey>* monkeys) {
	std::regex rgxMonkey("^Monkey ([0-9]+):");
	std::regex rgxStart(R"(^  Starting items: ((?:(?:[0-9]+)(?:, )?)*))");
	std::regex rgxOperation(R"(^  Operation: new = old (\*|\+) ([0-9]+|old))");
	std::regex rgxTest(R"(^  Test: divisible by ([0-9]+))");
	std::regex rgxTrue(R"(^    If true: throw to monkey ([0-9]+))");
	std::regex rgxFalse(R"(^    If false: throw to monkey ([0-9]+))");

	Monkey monkey;
	std::queue<unsigned long long>* items{};
	int* ifTrue{ new int(0) }, * ifFalse{ new int(0) };
	std::string op;
	std::string opValue;
	testFunction* testFunc{};

	for (std::string line : input) {
		std::smatch match;

		if (std::regex_match(line, match, rgxMonkey)) {
			items = new std::queue<unsigned long long>();
		}
		else if (std::regex_match(line, match, rgxStart)) {
			size_t pos = 0;
			std::string s{ match[1].str() };
			while ((pos = s.find(", ")) != std::string::npos) {
				items->push(std::stoi(s.substr(0, pos)));
				s.erase(0, pos + 2);
			}
			items->push(std::stoi(s));
		}
		else if (std::regex_match(line, match, rgxOperation)) {
			op = match[1].str();
			opValue = match[2].str();
		}
		else if (std::regex_match(line, match, rgxTest)) {
			int div{ std::stoi(match[1].str()) };
			if (op == "*") {
				if (opValue == "old") {
					testFunc = new testFunction([div](unsigned long long* item) {
						*item = *item * *item;
						return *item % div == 0;
						});
				}
				else {
					int value{ std::stoi(opValue) };
					testFunc = new testFunction([div, value](unsigned long long* item) {
						*item = *item * value;
						return *item % div == 0;
						});
				}
			}
			else {
				int value{ std::stoi(opValue) };
				testFunc = new testFunction([div, value](unsigned long long* item) {
					*item = (*item + value) / 3;
					return *item % div == 0;
					});
			}
		}
		else if (std::regex_match(line, match, rgxTrue)) {
			ifTrue = new int(std::stoi(match[1].str()));
		}
		else if (std::regex_match(line, match, rgxFalse)) {
			ifFalse = new int(std::stoi(match[1].str()));

			monkey = Monkey(items, monkeys, *ifTrue, *ifFalse, testFunc);
			monkeys->push_back(monkey);
		}
	}
}