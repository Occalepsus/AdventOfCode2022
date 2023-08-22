#include "Day20.h"

#include <list>
#include <algorithm>

#include <iostream>

template<typename T>
inline T positiveModulo(T i, int n) {
	return (i % n + n) % n;
}

int day20P1(std::vector<std::string> const& inputs) {
	int size{ static_cast<int>(inputs.size()) };

	std::list<int> values{};
	std::vector<std::list<int>::iterator> positions{};

	for (auto const& s: inputs) {
		values.emplace_back(std::stoi(s));
	}

	for (auto it{ values.begin() }; it != values.end(); it++) {
		positions.push_back(it);
	}

	for (auto const& it: positions) {
		int i{ *it };
		// Little calculations done to avoid overflow (calculating the distance between the iterator and the beginning of the list)
		i += std::distance(values.begin(), it) + 1;
		i += *it / size;
		if (*it < 0) {
			i--;
		}
		i = positiveModulo(i, size);

		auto adv{ values.begin() };
		std::ranges::advance(adv, i);
		values.splice(adv, values, it);
	}

	//std::cout << "Wanted: 1, 2, -3, 4, 0, 3, -2\n";
	//std::cout << "Result: ";
	//for (auto const& a: values) {
	//	std::cout << a << ", ";
	//}
	//std::cout << '\n';

	int zIdx{ 0 };
	for (auto v : values) {
		if (v == 0) {
			break;
		}
		zIdx++;
	}

	int res{};
	auto adv{ values.begin() };
	std::ranges::advance(adv, static_cast<ptrdiff_t>((1000 + zIdx) % size));
	res += *adv;

	adv = values.begin();
	std::ranges::advance(adv, static_cast<ptrdiff_t>((2000 + zIdx) % size));
	res += *adv;

	adv = values.begin();
	std::ranges::advance(adv, static_cast<ptrdiff_t>((3000 + zIdx) % size));
	res += *adv;

	return res;
}

long long getMoveIdx(long long v, long long i, int size) {
	return positiveModulo(v + i + (v >= 0 ? 1 : 0), size);
}

long long day20P2(std::vector<std::string> const& inputs) {
	constexpr long long key{ 811589153 };

	int size{ static_cast<int>(inputs.size()) };

	std::list<long long> values{};
	std::vector<std::list<long long>::iterator> positions{};

	for (auto const& s: inputs) {
		values.emplace_back(std::stoi(s) * key);
	}

	for (auto it{ values.begin() }; it != values.end(); it++) {
		positions.push_back(it);
	}

	for (int mix{ 0 }; mix < 10; mix++) {
		for (auto const& it : positions) {
			auto adv{ values.begin() };
			std::ranges::advance(adv, getMoveIdx(*it, std::ranges::distance(values.begin(), it), size));
			values.splice(adv, values, it);
		}
	}

	//std::cout << "Wanted: 1, 2, -3, 4, 0, 3, -2\n";
	//std::cout << "Result: ";
	//for (auto const& a: values) {
	//	std::cout << a << ", ";
	//}
	//std::cout << '\n';

	int zIdx{ 0 };
	for (auto v : values) {
		if (v == 0) {
			break;
		}
		zIdx++;
	}

	long long res{};
	auto adv{ values.begin() };
	std::ranges::advance(adv, static_cast<ptrdiff_t>((1000 + zIdx) % size));
	res += *adv;

	adv = values.begin();
	std::ranges::advance(adv, static_cast<ptrdiff_t>((2000 + zIdx) % size));
	res += *adv;

	adv = values.begin();
	std::ranges::advance(adv, static_cast<ptrdiff_t>((3000 + zIdx) % size));
	res += *adv;

	return res;
}
