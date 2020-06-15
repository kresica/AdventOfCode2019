#ifndef TASKEXECUTOR_H
#define TASKEXECUTOR_H

#include <iostream>
#include <string>
#include <fstream>

#include "taskcreator.h"

#define REGISTER_TASK_TO_EXECUTOR(className, taskName) \
	bool className::_executorRegistered = \
	TaskExecutor::registerTask(#taskName, className::execute);

// Not thread safe!
#define DO_ONCE(expr) \
	{ \
		static bool done = false; \
		if (!done) { \
			expr; \
			done = true; \
		} \
	}

class TaskExecutor
{
	static std::shared_ptr<TaskExecutor> _instance;
	static std::map<std::string, void (*)()> _taskMap;

public:
	TaskExecutor() {}
	~TaskExecutor() {}
	static bool registerTask(std::string taskName, void executeFunc());
	static std::shared_ptr<TaskExecutor> getInstance();
	static void openFile(std::ifstream& fileHandle);
	static void execute(std::string taskNumber);
};

#endif // TASKEXECUTOR_H
