#include "Monkey.h"

#include <iostream>

Monkey::Monkey(std::queue<unsigned long long>* items, std::vector<Monkey>* monkeys, int sT, int sF, testFunction* test) : 
	items{ items }, monkeys { monkeys }, sendTrue{ sT }, sendFalse{ sF }, testSend{ test } {}

Monkey::~Monkey() {}

void Monkey::makeTurn() {
	inspect += items->size();

	// For each item in the queue items
	while (!items->empty()) {
		unsigned long long item{ items->front() };
		items->pop();

		// Test to who the monkey will throw the item.
		if (testSend->operator()(&item)) {
			std::cout << "Item " << item << " was sent to " << sendTrue << " because " << div << " " << op << '\n';
			monkeys->at(sendTrue).sendItem(item);
		}
		else {
			std::cout << "Item " << item << " was sent to " << sendFalse << " because " << div << " " << op << '\n';
			monkeys->at(sendFalse).sendItem(item);
		}
	}
}

void Monkey::sendItem(unsigned long long item) {
	items->push(item);
}