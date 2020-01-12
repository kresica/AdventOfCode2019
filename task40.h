#ifndef TASK40_H
#define TASK40_H

#include "taskexecutor.h"
#include "passwordcracker.h"

class Task40 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task40() {}
	~Task40() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK40_H
