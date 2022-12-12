#pragma once

#include <vector>
#include <string>
#include <queue>
#include <functional>

typedef std::function<bool(unsigned long long*)> testFunction;

class Monkey
{
public:
	std::vector<Monkey>* monkeys{};

	std::queue<unsigned long long>* items{};

	testFunction* testSend{};
	int sendTrue;
	int sendFalse;

	std::string op;
	int div;

	unsigned long long inspect{ 0 };

	Monkey() : sendTrue{}, sendFalse{} {};
	
	Monkey(std::queue<unsigned long long>*, std::vector<Monkey>*, int, int, testFunction*);
	~Monkey();

	void makeTurn();

	void sendItem(unsigned long long);
};

