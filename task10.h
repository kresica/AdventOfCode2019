#ifndef TASK10_H
#define TASK10_H

#include <fstream>

#include "taskcreator.h"
#include "taskexecutor.h"

class Task10 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task10() {}
	~Task10() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK10_H
