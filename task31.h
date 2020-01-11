#ifndef TASK31_H
#define TASK31_H

#include "taskexecutor.h"
#include "wireboard.h"

class Task31 : public TaskExecutor
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task31() {}
	~Task31() {}
	static TaskCreator* create();
	static void execute();
};

#endif // TASK31_H
