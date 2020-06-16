#include "task60.h"

REGISTER_TASK_TO_CREATOR(Task60, 6.0)
REGISTER_TASK_TO_EXECUTOR(Task60, 6.0)

std::shared_ptr<TaskCreator> Task60::create()
{
	return std::shared_ptr<TaskCreator>(new Task60());
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
	Tree tree;
	std::ifstream iFile;
	openFile(iFile);
	std::shared_ptr<orbitnode_t> root = tree.createOrbitTree(iFile);
	if (!root) {
		std::cout << "Non-existent node, undefined behavior" << std::endl;
		return;
	}
	int level = 0;
	findOrbits(root, level);
	std::cout << "Total number of orbits: " << level << std::endl;
}
