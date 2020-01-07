#ifndef TASK11_H
#define TASK11_H

#include "taskcreator.h"
#include "taskexecutor.h"
#include "spacemodule.h"

class Task11 : public TaskExecutor
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task11() {}
	~Task11() {}
	static TaskCreator* create();
	static void execute();
};

#endif // TASK11_H