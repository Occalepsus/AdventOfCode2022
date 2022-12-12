#pragma once

#include "Monkey.h"
#include <vector>
#include <string>

int day11P1(std::vector<std::string> input);
size_t day11P2(std::vector<std::string> input);

void getMonkeys(std::vector<std::string>, std::vector<Monkey>*);
void getMonkeys2(std::vector<std::string>, std::vector<Monkey>&);