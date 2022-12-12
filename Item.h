#pragma once

#include <string>
#include <vector>

class Folder;

class Item {
protected:
	std::string name;
	Folder* parent {};

public:
	virtual ~Item() = 0 {};

	std::string getName() {
		return name;
	}
	
	virtual int getSize() {
		return 0;
	};

	Folder* getParent() {
		return parent;
	};
	void setParent(Folder* parent) {
		this->parent = parent;
	}
};

class File : public Item {
private:
	int size;

public:
	File(std::string name, int size) {
		this->name = name;
		this->size = size;
	}

	int getSize() {
		return size;
	}
};

class Folder : public Item {
private:
	std::vector<Item*> children;

public:	
	Folder() {};
	Folder(std::string name) {
		this->name = name;
	}

	void addChild(Item* child) {
		children.push_back(child);
		child->setParent(this);
	}
	
	std::vector<Item*> getChildren() {
		return children;
	}

	int getSize() {
		int res{ 0 };
		for (Item* item : children) {
			res += item->getSize();
		}
		return res;
	}
};