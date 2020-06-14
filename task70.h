#ifndef TASK70_H
#define TASK70_H

#include <algorithm>

#include "taskcreator.h"
#include "taskexecutor.h"
#include "mooncomputer.h"

class Task70 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

public:
	Task70() {}
	~Task70() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK70_H
