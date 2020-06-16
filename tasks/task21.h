#ifndef TASK21_H
#define TASK21_H

#include <sstream>

#include "taskcreator.h"
#include "taskexecutor.h"

class Task21 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task21() {}
	~Task21() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK21_H
