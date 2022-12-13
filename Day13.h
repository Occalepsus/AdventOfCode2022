#pragma once

#include <vector>
#include <string>

enum CompVal {
	HIGHER,
	LOWER,
	TIE,
};

enum type {
	LIST,
	INT,
};
struct nestedList {
	type type{ LIST };
	std::vector<nestedList> list{};
	int value{ 0 };

	nestedList() {}
	nestedList(int val) : type(INT), value(val) {}
	~nestedList() {
		list.~vector();
	}

	void set(int val) {
		type = INT;
		value = val;
	}
	void add(nestedList nList) {
		if (type != LIST)
			throw std::exception("Trying to add element to a non-list");
		else {
			list.push_back(nList);
		}
	}
	size_t size() {
		if (type == INT)
			return 1;
		else
			return list.size();
	}
	void operator+(nestedList nList) {
		add(nList);
	}
	void setToList() {
		type = LIST;
		list.push_back(value);
	}
	
	CompVal comp(nestedList& other) {
		if (type == INT && other.type == INT) {
			if (value > other.value) return HIGHER;
			else if (value < other.value) return LOWER;
			else return TIE;
		}
		else if (type == INT) {
			setToList();
		}
		else if (other.type == INT) {
			other.setToList();
		}

		int i{ 0 };
		while (i < size() && i < other.size()) {
			CompVal res{ list[i].comp(other.list[i]) };
			if (res == TIE) i++;
			else return res;
		}
		if (i >= size() && i < other.size()) return LOWER;
		else if (i >= other.size() && i < size()) return HIGHER;
		else return TIE;
	}

	bool operator< (nestedList& other) {
		return comp(other) == LOWER;
	}

	std::string toString() {
		if (type == INT) {
			return std::to_string(value);
		}
		else {
			std::string res{ "[" };
			for (auto& nList : list) {
				res += nList.toString() + ",";
			}
			res.pop_back();
			res += "]";
			return res;
		}
	}
};

int day13P1(std::vector<std::string> input);
int day13P2(std::vector<std::string> input);

nestedList parseToNList(std::string input);