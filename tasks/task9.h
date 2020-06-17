#ifndef TASK9_H
#define TASK9_H

#include "taskcreator.h"
#include "taskexecutor.h"

class Task9 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

public:
	Task9() {}
	~Task9() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK9_H
