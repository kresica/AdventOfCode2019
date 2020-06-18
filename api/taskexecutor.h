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
		static std::list<std::string> done; \
		if (std::find(done.begin(), done.end(), #expr) == done.end()) { \
			done.insert(done.end(), #expr); \
			expr; \
		} \
	}

class TaskExecutor
{
	static std::shared_ptr<TaskExecutor> _instance;

public:
	TaskExecutor() {}
	~TaskExecutor() {}
	static bool registerTask(std::string taskName, void executeFunc());
	static std::shared_ptr<TaskExecutor> getInstance();
	static void openFile(std::ifstream& fileHandle);
	static void openFile(std::ifstream& fileHandle, const std::string fName);
	static void execute(std::string taskNumber);
};

#endif // TASKEXECUTOR_H
