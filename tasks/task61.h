#ifndef TASK61_H
#define TASK61_H

#include "taskcreator.h"
#include "taskexecutor.h"
#include "tree.h"

class Task61 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task61() {}
	~Task61() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK61_H
