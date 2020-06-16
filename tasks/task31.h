#ifndef TASK31_H
#define TASK31_H

#include "taskexecutor.h"
#include "wireboard.h"

class Task31 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task31() {}
	~Task31() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK31_H
