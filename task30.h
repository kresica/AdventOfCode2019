#ifndef TASK30_H
#define TASK30_H

#include "taskcreator.h"
#include "taskexecutor.h"

typedef std::vector<std::string> wire_t;

class Task30 : public TaskExecutor
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task30() {}
	~Task30() {}
	static TaskCreator* create();
	static void execute();
};

#endif // TASK30_H
