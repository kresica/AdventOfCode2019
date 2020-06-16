#ifndef TASK80_H
#define TASK80_H

#include <sstream>

#include "taskcreator.h"
#include "taskexecutor.h"

#define IMAGE_WIDTH 25
#define IMAGE_HEIGHT 6

typedef std::array<std::array<int,IMAGE_WIDTH>,IMAGE_HEIGHT> imageLayer_t;

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
