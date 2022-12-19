#include "Day15.h"

#include <iostream>
#include <algorithm>

const __int64 line = 2000000;

size_t day15P1(std::vector<std::string> input) {
	std::vector<sensor> sensors{};

	for (auto& line : input) {
		int x, y, bx, by;
		if (sscanf_s(line.c_str(), "Sensor at x=%i, y=%i: closest beacon is at x=%i, y=%i", &x, &y, &bx, &by) != 4) {
			std::cout << "Error parsing line: " << line << std::endl;
			return -1;
		}
		sensors.push_back(sensor(x, y, bx, by));
	}

	std::vector<interval> intervals{};

	for (auto& sensor : sensors) {
		std::cout << std::abs(line - sensor.y) << ", " << sensor.radius() << ": " << (std::abs(line - sensor.y) < sensor.radius()) << ". ";
		std::cout << sensor.y - sensor.radius() << ", " << sensor.y + sensor.radius() << ". ";
		interval i{ intervalFromSensor(sensor, line) };
		std::cout << "[" << i.start << ", " << i.end << "]" << "\n";
		if (i.size() > 0) {
			insertInterval(intervals, i);
		}
	}
	for (auto& sensor : sensors) {
		if (/*sensor.y == line || */sensor.by == line) {
			for (auto& itv : intervals) {
				//if (sensor.y == line && sensor.x >= itv.start && sensor.x <= itv.end) {
				//	interval splitItv{ itv.split(sensor.x) };
				//	if (splitItv.size() > 0) {
				//		intervals.push_back(splitItv);
				//	}
				//}
				if (sensor.by == line && sensor.bx >= itv.start && sensor.bx <= itv.end) {
					interval splitItv{ itv.split(sensor.bx) };
					if (splitItv.size() > 0) {
						intervals.push_back(splitItv);
					}
				}
			}
		}
	}
	size_t score{ 0 };
	for (auto& itv : intervals) {
		score += itv.size() + 1;
	}
	return score;
}

int day15P2(std::vector<std::string> input) {
	std::vector<sensor> sensors{};

	for (auto& line : input) {
		int x, y, bx, by;
		if (sscanf_s(line.c_str(), "Sensor at x=%i, y=%i: closest beacon is at x=%i, y=%i", &x, &y, &bx, &by) != 4) {
			std::cout << "Error parsing line: " << line << std::endl;
			return -1;
		}
		sensors.push_back(sensor(x, y, bx, by));
	}

	std::vector<std::vector<interval>> keptIntervals{};

	for (long line{ 0 }; line < 4000000; line++) {
		std::vector<interval> intervals{};
		for (auto& sensor : sensors) {
			//std::cout << std::abs(line - sensor.y) << ", " << sensor.radius() << ": " << (std::abs(line - sensor.y) < sensor.radius()) << ". ";
			//std::cout << sensor.y - sensor.radius() << ", " << sensor.y + sensor.radius() << ". ";
			interval i{ intervalFromSensor(sensor, line) };
			//std::cout << "[" << i.start << ", " << i.end << "]" << "\n";
			if (i.size() > 0) {
				insertInterval(intervals, i);
			}
		}
		if (intervals.size() == 1) {
			if (!(intervals[0].start <= 0 && intervals[0].end >= 4000000)) {
				keptIntervals.push_back(intervals);
			}
			continue;
		}
		else if (intervals.size() > 1) {
			keptIntervals.push_back(intervals);
			continue;
		}
	}

	for (auto& vec : keptIntervals) {
		for (auto& i : vec) {
			std::cout << "[" << i.start << ", " << i.end << "] ";
		}
		std::cout << "\n";
	}
	return 0;
}


interval intervalFromSensor(sensor& s, int line) {
	if (std::abs(line - s.y) < s.radius()) {
		size_t a{ s.radius() - std::abs(line - s.y) };
		return interval(s.x - a, s.x + a);
	}
	else {
		return interval();
	}
}

void insertInterval(std::vector<interval>& intervals, interval& itv) {
	bool insert{ true };
	for (std::vector<interval>::iterator it{ intervals.begin() }; it != intervals.end();) {
		if (it->merge(itv) > 0) {
			interval nInterval{ *it };
			it = intervals.erase(it);
			insertInterval(intervals, nInterval);

			insert = false;
			break;
		}
		else if (intervals.size() == 0) break;
		else {
			++it;
		}
	}
	if (insert && itv.size() > 0) intervals.push_back(itv);
}