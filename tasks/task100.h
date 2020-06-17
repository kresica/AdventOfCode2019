#ifndef TASK100_H
#define TASK100_H

#include "taskcreator.h"
#include "taskexecutor.h"
#include "asteroidstation.h"

class Task100 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

public:
	Task100() {}
	~Task100() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK100_H
