#ifndef TASK10_H
#define TASK10_H

#include "taskcreator.h"
#include "taskexecutor.h"
#include "spacemodule.h"

class Task10 : public TaskExecutor
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task10() {}
	~Task10() {}
	static TaskCreator* create();
	static void execute();
};

#endif // TASK10_H
