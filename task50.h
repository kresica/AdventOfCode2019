#ifndef TASK50_H
#define TASK50_H

#include <sstream>

#include "taskcreator.h"
#include "taskexecutor.h"

class Task50 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task50() {}
	~Task50() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK50_H
