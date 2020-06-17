#ifndef TASK90_H
#define TASK90_H

#include "taskcreator.h"
#include "taskexecutor.h"

class Task90 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

public:
	Task90() {}
	~Task90() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK90_H
