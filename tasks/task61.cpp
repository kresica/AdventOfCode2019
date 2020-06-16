#include "task61.h"

REGISTER_TASK_TO_CREATOR(Task61, 6.1)
REGISTER_TASK_TO_EXECUTOR(Task61, 6.1)

std::shared_ptr<TaskCreator> Task61::create()
{
	return std::shared_ptr<TaskCreator>(new Task61());
}

void Task61::execute()
{
	Tree tree;
	std::ifstream iFile;
	openFile(iFile);
	std::shared_ptr<orbitnode_t> root = tree.createOrbitTree(iFile);
	if (!root) {
		std::cout << "Non-existent node, undefined behavior" << std::endl;
		return;
	}
	std::shared_ptr<orbitnode_t> you;
	tree.findNode(root, "YOU", you);
	std::list<std::shared_ptr<orbitnode_t>> yourPath;
	tree.findPath(you, yourPath);

	std::shared_ptr<orbitnode_t> santa;
	tree.findNode(root, "SAN", santa);
	std::list<std::shared_ptr<orbitnode_t>> santasPath;
	tree.findPath(santa, santasPath);

	auto it1 = yourPath.begin();
	auto it2 = santasPath.begin();
	while (it1 != yourPath.end() && it2 != santasPath.end()) {
		if ((*it1) != (*it2)) {
			break;
		}
		++it1;
		++it2;
		yourPath.pop_front();
		santasPath.pop_front();
	}

	std::cout << "Distance between Santa and you is " <<
		     yourPath.size() + santasPath.size() - 2 <<
		     " orbits" << std::endl;
}
