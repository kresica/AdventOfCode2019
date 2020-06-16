#ifndef TASK11_H
#define TASK11_H

#include <fstream>

#include "taskcreator.h"
#include "taskexecutor.h"

class Task11 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task11() {}
	~Task11() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK11_H
