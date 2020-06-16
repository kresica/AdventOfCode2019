#ifndef TASK41_H
#define TASK41_H

#include "taskexecutor.h"
#include "passwordcracker.h"

class Task41 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task41() {}
	~Task41() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK41_H
