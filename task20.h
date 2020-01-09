#ifndef TASK20_H
#define TASK20_H

#include <fstream>
#include <sstream>

#include "taskcreator.h"
#include "taskexecutor.h"

class Task20 : public TaskExecutor
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task20() {}
	~Task20() {}
	static TaskCreator* create();
	static void execute();
};

#endif // TASK20_H
