#ifndef TASK60_H
#define TASK60_H

#include <iostream>
#include <string>
#include <list>

#include "taskcreator.h"
#include "taskexecutor.h"

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

class Task60 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

	static bool findNode(std::shared_ptr<orbitnode_t> root, std::string& name,
			     std::shared_ptr<orbitnode_t>& match, int& level);
	static void connectFreeRadicals(std::shared_ptr<orbitnode_t> root,
					std::list<std::shared_ptr<orbitnode_t>> freeRadicals);
	static std::shared_ptr<orbitnode_t> createOrbitTree();
	static int findOrbits(std::shared_ptr<orbitnode_t> root, int &level);
public:
	Task60() {}
	~Task60() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK60_H
