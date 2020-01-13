#ifndef TASK5_H
#define TASK5_H

#include <sstream>

#include "taskcreator.h"
#include "taskexecutor.h"

class Task5 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task5() {}
	~Task5() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK5_H
