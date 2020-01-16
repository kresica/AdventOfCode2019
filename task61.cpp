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
	std::shared_ptr<orbitnode_t> you = std::shared_ptr<orbitnode_t>(new orbitnode_t("YOU"));
	tree.findNode(root, you->name, you);
	std::list<std::shared_ptr<orbitnode_t>> yourPath;
	tree.findPath(you, yourPath);

	std::shared_ptr<orbitnode_t> santa = std::shared_ptr<orbitnode_t>(new orbitnode_t("SAN"));
	tree.findNode(root, santa->name, santa);
	std::list<std::shared_ptr<orbitnode_t>> santasPath;
	tree.findPath(santa, santasPath);


}
