#ifndef TASK20_H
#define TASK20_H

#include <sstream>

#include "taskcreator.h"
#include "taskexecutor.h"

class Task20 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task20() {}
	~Task20() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK20_H
