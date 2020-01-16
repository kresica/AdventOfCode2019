#ifndef TASK60_H
#define TASK60_H

#include <iostream>
#include <string>
#include <list>

#include "taskcreator.h"
#include "taskexecutor.h"
#include "tree.h"

class Task60 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

	static int findOrbits(std::shared_ptr<orbitnode_t> root, int& levelSum);
public:
	Task60() {}
	~Task60() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK60_H
