#pragma once

#include "Item.h"

#include <vector>
#include <string>
#include <list>

int day7P1(std::vector<std::string> input);
int day7P2(std::vector<std::string> input);

Folder* createTree(std::vector<std::string> input);

void displayTree(Folder* root, int depth = 0);

std::list<Folder*> getLightFolders(Folder* root, int maxWeight);
std::list<Folder*> getHeavyFolders(Folder* root, int minWeight);