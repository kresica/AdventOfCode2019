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
	}
	if (root->name == name || root->name == "COM") {
		match = root;
		return true;
	}
	return false;
}

std::shared_ptr<orbitnode_t> Task60::createOrbitTree()
{
	std::ifstream iFile;
	std::string orbit;
	std::shared_ptr<orbitnode_t> root = std::shared_ptr<orbitnode_t>(new orbitnode_t());

	openFile(iFile);
	while (iFile >> orbit) {
		int level = 1;
		std::shared_ptr<orbitnode_t> node;
		int delimiterPos = orbit.find(')');
		std::string parent = orbit.substr(0, delimiterPos);
		std::string child = orbit.substr(delimiterPos + 1);
		if (!findNode(root, parent, node, level)) {
			return nullptr;
		}
		std::shared_ptr<orbitnode_t> childNode = std::shared_ptr<orbitnode_t>(new orbitnode_t(child, level));
		childNode->parent = node;
		childNode->level = level;
		node->children.push_back(childNode);
	}
	return std::move(root);
}

int Task60::findOrbits(std::shared_ptr<orbitnode_t> root)
{
	int level = 0;
	for (std::shared_ptr<orbitnode_t> child : root->children) {
		level += findOrbits(child);
	}
	return (root->level + level);
}

void Task60::execute()
{
	std::shared_ptr<orbitnode_t> root = createOrbitTree();
	if (!root) {
		std::cout << "Non-existent node, undefined behavior" << std::endl;
		return;
	}
	std::cout << "Total number of orbits: " << findOrbits(root) << std::endl;
}
