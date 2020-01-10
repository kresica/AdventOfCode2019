#include "taskexecutor.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
std::map<std::string, void (*)()> TaskExecutor::_taskMap;

// -----------------------------------------------------------------
// Member functions
// -----------------------------------------------------------------
bool TaskExecutor::registerTask(std::string taskName, void executeFunc())
{
	std::map<std::string, void (*)()>::iterator it;
	it = _taskMap.find(taskName);

	if (it == _taskMap.end()) {
		_taskMap[taskName] = executeFunc;
		return true;
	}
	return false;
}

std::unique_ptr<TaskExecutor> TaskExecutor::getInstance()
{
	return std::unique_ptr<TaskExecutor>(new TaskExecutor);
}

void TaskExecutor::openFile(std::ifstream& fileHandle)
{
	std::string fileName = TaskCreator::getFilename();
	fileHandle.open(fileName);
	if (!fileHandle) {
		std::cout << "Unable to open file" << fileName << std::endl;
		exit(1);
	}
}

void TaskExecutor::execute(std::string taskNumber)
{
	std::map<std::string, void (*)()>::iterator it;
	it = _taskMap.find(taskNumber);

	if (it == _taskMap.end()) {
		std::cout << "Unable to execute task, task " << taskNumber
			  << " not found in map" << std::endl;
		exit(1);
	}
	(it->second)();
}
