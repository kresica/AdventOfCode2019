#ifndef TASK81_H
#define TASK81_H

#include "taskcreator.h"
#include "taskexecutor.h"
#include "sifdecoder.h"

class Task81 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

public:
	Task81() {}
	~Task81() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK81_H
