#include "task60.h"

REGISTER_TASK_TO_CREATOR(Task60, 6.0)
REGISTER_TASK_TO_EXECUTOR(Task60, 6.0)

std::shared_ptr<TaskCreator> Task60::create()
{
	return std::shared_ptr<TaskCreator>(new Task60());
}

bool Task60::findNode(std::shared_ptr<orbitnode_t> root, std::string& name,
		      std::shared_ptr<orbitnode_t>& match, int& level)
{
	for (std::shared_ptr<orbitnode_t> child : root->children) {
		++level;
		if (findNode(child, name, match, level)) {
			return true;
		}
		--level;
	}
	if (root->name == name) {
		match = root;
		return true;
	}
	return false;
}

void Task60::connectFreeRadicals(std::shared_ptr<orbitnode_t> root,
				 std::list<std::shared_ptr<orbitnode_t>> freeRadicals)
{
	int previousSize = freeRadicals.size();
	for (auto it = freeRadicals.begin(); it != freeRadicals.end(); ) {
		if ((*it)->name == "COM") {
			++it;
			continue;
		}
		std::shared_ptr<orbitnode_t> node;
		int level = 1;
		findNode(root, (*it)->name, node, level);
		if (node) {
			for (std::shared_ptr<orbitnode_t> child : (*it)->children) {
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

std::shared_ptr<orbitnode_t> Task60::createOrbitTree()
{
	std::ifstream iFile;
	std::string orbit;
	std::shared_ptr<orbitnode_t> root = std::shared_ptr<orbitnode_t>(new orbitnode_t());
	std::list<std::shared_ptr<orbitnode_t>> freeRadicals{root};

	openFile(iFile);
	while (iFile >> orbit) {
		int level = 1;
		std::shared_ptr<orbitnode_t> node;
		int delimiterPos = orbit.find(')');
		std::string parent = orbit.substr(0, delimiterPos);
		std::string child = orbit.substr(delimiterPos + 1);
		int ret = false;
		for (std::shared_ptr<orbitnode_t> radical : freeRadicals) {
			ret = findNode(radical, parent, node, level);
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
			parentNode->children.push_back(std::move(childNode));
			freeRadicals.push_back(std::move(parentNode));
		}
	}
	connectFreeRadicals(root, freeRadicals);

	return std::move(root);
}

int Task60::findOrbits(std::shared_ptr<orbitnode_t> root, int& levelSum)
{
	static int level = 0;
	for (std::shared_ptr<orbitnode_t> child : root->children) {
		++level;
		levelSum += findOrbits(child, levelSum);
		--level;
	}
	return level;
}

void Task60::execute()
{
	std::shared_ptr<orbitnode_t> root = createOrbitTree();
	if (!root) {
		std::cout << "Non-existent node, undefined behavior" << std::endl;
		return;
	}
	int level = 0;
	findOrbits(root, level);
	std::cout << "Total number of orbits: " << level << std::endl;
}
