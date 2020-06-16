#ifndef TASK71_H
#define TASK71_H

#include <algorithm>

#include "taskcreator.h"
#include "taskexecutor.h"
#include "mooncomputer.h"

class Task71 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

public:
	Task71() {}
	~Task71() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK71_H
