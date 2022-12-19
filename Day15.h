#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <thread>
#include <mutex>

struct sensor {
	__int64 x;
	__int64 y;
	__int64 bx;
	__int64 by;

	size_t radius() { return std::abs(x - bx) + std::abs(y - by); }

	sensor(__int64 x, __int64 y, __int64 bx, __int64 by) : x(x), y(y), bx(bx), by(by) {}
};
struct interval {
	__int64 start;
	__int64 end;
	
	interval() : start{ 0 }, end{ 0 } {};
	interval(__int64 s, __int64 e) {
		if (s < e) {
			start = s;
			end = e;
		}
		else {
			start = e;
			end = s;
		}
	};

	size_t size() { return static_cast<size_t>(end - start); }

	interval split(__int64 splitter) {
		if (splitter > end || splitter < start) throw std::out_of_range("Splitter out of range");
		else if (splitter == end) {
			end--;
			return interval();
		}
		else if (splitter == start) {
			start++;
			return interval();
		}
		else {
			auto oldEnd{ end };
			end = splitter - 1;
			return interval(splitter + 1, oldEnd);
		}
	}

	/**
	* Merge this with other, if possible, change this to fit the merge and return its new size, else it returns 0
	*
	* @param other: the interval to merge with this
	* @return the new size of the merged interval, or 0 if the merge failed
	*/
	size_t merge(interval& other) {
		size_t space{ static_cast<size_t>(std::max(end, other.end) - std::min(start, other.start)) };

		// Case 1: the intervals are separated
		if (space > size() + other.size()) {
			return 0;	
		}
		// Case 2.1: other is contained in this
		else if (space == size()) {
			return size();
		}
		// Case 2.2: this is contained in other
		else if (space == other.size()) {
			start = other.start;
			end = other.end;
			return size();
		}
		// Case 3: the intervals are overlapping
		else {
			start = std::min(start, other.start);
			end = std::max(end, other.end);
			return size();
		}
	}

	bool operator<(interval& other) {
		return start < other.start;
	}
};

size_t day15P1(std::vector<std::string> input);
int day15P2(std::vector<std::string> input);

void lookForTheInterval(std::vector<sensor>& sensors, long line, std::vector<std::vector<interval>>& keptIntervals, std::mutex& m);

interval intervalFromSensor(sensor& s, int line);

void insertInterval(std::vector<interval>& intervals, interval& itv);