#ifndef TASK101_H
#define TASK101_H

#include "taskcreator.h"
#include "taskexecutor.h"
#include "asteroidstation.h"

class Task101 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

public:
	Task101() {}
	~Task101() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK101_H
