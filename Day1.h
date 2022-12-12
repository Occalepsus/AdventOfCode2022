#pragma once

#include <vector>
#include <string>

int day1P1(std::vector<std::string> input);
int day1P2(std::vector<std::string> input);

std::vector<int> getValues(std::vector<std::string> input, double* maxPosPtr);

int findSum3Higher(std::vector<int> values);