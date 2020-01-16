#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <fstream>

typedef struct orbitnode_t
{
	std::string name;
	std::weak_ptr<orbitnode_t> parent;
	std::list<std::shared_ptr<orbitnode_t>> children;
	orbitnode_t(const std::string name = "COM") {
		this->name = name;
		this->parent.reset();
	}
} orbitnode_t;

class Tree
{
	void connectFreeRadicals(std::shared_ptr<orbitnode_t> root,
				 std::list<std::shared_ptr<orbitnode_t>>& freeRadicals);
public:
	Tree() {}
	~Tree() {}
	std::shared_ptr<orbitnode_t> createOrbitTree(std::ifstream &iFile);
	bool findNode(std::shared_ptr<orbitnode_t> root, std::string& name,
		      std::shared_ptr<orbitnode_t>& match);
	void findPath(std::shared_ptr<orbitnode_t>& node,
		      std::list<std::shared_ptr<orbitnode_t>>& pathList);
};

#endif // TREE_H
