#include "Day7.h"

#include <iostream>
#include <sstream>

int day7P1(std::vector<std::string> input) {
	Folder* root = createTree(input);

	displayTree(root);

	std::list<Folder*> lightFolders{ getLightFolders(root, 100000) };

	int score{ 0 };
	
	for (Folder* folder : lightFolders) {
		std::cout << folder->getName() << "\n";
		score += folder->getSize();
	}

	return score;
}

int day7P2(std::vector<std::string> input) {
	Folder* root = createTree(input);

	displayTree(root);

	std::list<Folder*> lightFolders{ getHeavyFolders(root, root->getSize() - 40000000) };

	int minSize{ 70000000 };

	for (Folder* folder : lightFolders) {
		std::cout << folder->getName() << "\n";
		if (folder->getSize() < minSize) {
			minSize = folder->getSize();
		}
	}

	return minSize;
}

Folder* createTree(std::vector<std::string> input) {
	Folder* root{ new Folder("/") };
	Folder* currentDir{ root };
		
	for (std::string line : input) {
		std::stringstream ss(line);
		std::string word;
		
		if (ss >> word) {
			// Cas 1 : entrée utilisateur
			if (word == "$") {
				if (ss >> word) {
					// Cas 1.1 : cd
					if (word == "cd") {
						if (ss >> word) {
							// Cas 1.1.1 : cd ..
							if (word == "..") {
								currentDir = (currentDir->getParent());
							}
							// Cas 1.1.2 : cd /
							else if (word == "/") {
								currentDir = root;
							}
							// Cas 1.1.3 : cd nom
							else {
								Folder* newDir{ new Folder(word) };
								currentDir->addChild(newDir);
								currentDir = newDir;
							}
						}
					}
					// Cas 1.2 : ls
					else {
						continue;
					}
				}
			}
			// Cas 2 : affichage console
			else {
				// Cas 2.1 : Fichier
				try {
					int size = std::stoi(word);
					if (ss >> word) {
						currentDir->addChild(new File(word, size));
					}
				}
				// Cas 2.2 : Dossier
				catch (std::invalid_argument e) {
					continue;
				}
			}
		}
	}
	return root;
}

void displayTree(Folder* root, int depth) {
	std::cout << std::string(depth, '\t') << "- " << root->getName() << " (dir)\n";
	for (Item* child : root->getChildren()) {
		Folder* cast_child{ dynamic_cast<Folder*>(child) };
		if (cast_child != nullptr) {
			displayTree(cast_child, depth + 1);
		}
		else {
			std::cout << std::string(depth + 1, '\t') << "- " << child->getName() << " (file, size=" << child->getSize() << ")\n";
		}
	}
}

std::list<Folder*> getLightFolders(Folder* root, int maxWeight) {
	std::list<Folder*> lightFolders;

	for (Item* child : root->getChildren()) {
		Folder* cast_child{ dynamic_cast<Folder*>(child) };
		if (cast_child != nullptr) {
			lightFolders.splice(lightFolders.end(), getLightFolders(cast_child, maxWeight));
		}
	}

	if (root->getSize() < maxWeight) {
		lightFolders.push_back(root);
	}

	return lightFolders;
}

std::list<Folder*> getHeavyFolders(Folder* root, int minWeight) {
	std::list<Folder*> heavyFolders;

	for (Item* child : root->getChildren()) {
		Folder* cast_child{ dynamic_cast<Folder*>(child) };
		if (cast_child != nullptr) {
			heavyFolders.splice(heavyFolders.end(), getHeavyFolders(cast_child, minWeight));
		}
	}

	if (root->getSize() >= minWeight) {
		heavyFolders.push_back(root);
	}

	return heavyFolders;
}