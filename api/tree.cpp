#include "tree.h"

bool Tree::findNode(std::shared_ptr<orbitnode_t>& root, std::string name,
		    std::shared_ptr<orbitnode_t>& match)
{
	for (std::shared_ptr<orbitnode_t> child : root->children) {
		if (findNode(child, name, match)) {
			return true;
		}
	}
	if (root->name == name) {
		match = root;
		return true;
	}
	return false;
}

void Tree::connectFreeRadicals(std::shared_ptr<orbitnode_t> root,
			       std::list<std::shared_ptr<orbitnode_t>>& freeRadicals)
{
	auto previousSize = freeRadicals.size();
	for (auto it = freeRadicals.begin(); it != freeRadicals.end(); ) {
		if ((*it)->name == "COM") {
			++it;
			continue;
		}
		std::shared_ptr<orbitnode_t> node;
		findNode(root, (*it)->name, node);
		if (node) {
			for (std::shared_ptr<orbitnode_t> child : (*it)->children) {
				child->parent = node;
				node->children.push_back(std::move(child));
			}
			freeRadicals.erase(it++);
			continue;
		}
		++it;
	}
	if (freeRadicals.size() != 1) {
		if (previousSize <= freeRadicals.size()) {
			std::cout << "Not all free radicals can be traced to root tree, exiting" << std::endl;
			return;
		}
		connectFreeRadicals(root, freeRadicals);
	}
	return;
}

std::shared_ptr<orbitnode_t> Tree::createOrbitTree(std::ifstream& iFile)
{
	std::string orbit;
	std::shared_ptr<orbitnode_t> root = std::shared_ptr<orbitnode_t>(new orbitnode_t());
	std::list<std::shared_ptr<orbitnode_t>> freeRadicals{root};

	while (iFile >> orbit) {
		std::shared_ptr<orbitnode_t> node;
		int delimiterPos = orbit.find(')');
		std::string parent = orbit.substr(0, delimiterPos);
		std::string child = orbit.substr(delimiterPos + 1);
		int ret = false;
		for (std::shared_ptr<orbitnode_t> radical : freeRadicals) {
			ret = findNode(radical, parent, node);
			if (ret) {
				std::shared_ptr<orbitnode_t> childNode =
						std::shared_ptr<orbitnode_t>(new orbitnode_t(child));
				childNode->parent = node;
				node->children.push_back(childNode);
				break;
			}
		}
		if (!ret) {
			std::shared_ptr<orbitnode_t> parentNode =
					std::shared_ptr<orbitnode_t>(new orbitnode_t(parent));
			std::shared_ptr<orbitnode_t> childNode =
					std::shared_ptr<orbitnode_t>(new orbitnode_t(child));
			childNode->parent = parentNode;
			parentNode->children.push_back(childNode);
			freeRadicals.push_back(std::move(parentNode));
		}
	}
	connectFreeRadicals(root, freeRadicals);

	return std::move(root);
}

void Tree::findPath(std::shared_ptr<orbitnode_t> node,
		    std::list<std::shared_ptr<orbitnode_t>>& pathList)
{
	if (node->parent) {
		findPath(node->parent, pathList);
	}
	pathList.push_back(node);
}
