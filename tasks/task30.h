#ifndef TASK30_H
#define TASK30_H

#include <algorithm>

#include "taskexecutor.h"
#include "wireboard.h"

class Task30 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task30() {}
	~Task30() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK30_H
