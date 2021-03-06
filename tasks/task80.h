#ifndef TASK80_H
#define TASK80_H

#include "taskcreator.h"
#include "taskexecutor.h"
#include "sifdecoder.h"

class Task80 : public TaskExecutor, public TaskCreator
{
	static bool _creatorRegistered;
	static bool _executorRegistered;

public:
	Task80() {}
	~Task80() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
};

#endif // TASK80_H
