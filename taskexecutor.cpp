#include "taskexecutor.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
std::shared_ptr<TaskExecutor> TaskExecutor::_instance = nullptr;
std::map<std::string, void (*)()> TaskExecutor::_taskMap;

// -----------------------------------------------------------------
// Member functions
// -----------------------------------------------------------------
bool TaskExecutor::registerTask(std::string taskName, void executeFunc())
{
	auto it = _taskMap.find(taskName);

	if (it == _taskMap.end()) {
		_taskMap[taskName] = executeFunc;
		return true;
	}
	return false;
}

std::shared_ptr<TaskExecutor> TaskExecutor::getInstance()
{
	if (_instance == nullptr) {
		_instance = static_cast<std::shared_ptr<TaskExecutor>>(new TaskExecutor());
	}
	return _instance;
}

void TaskExecutor::openFile(std::ifstream& fileHandle)
{
	std::string fileName = TaskCreator::getFilename();
	fileHandle.open(fileName);
	if (!fileHandle) {
		std::cout << "Unable to open file " << fileName << std::endl;
		exit(1);
	}
}

void TaskExecutor::execute(std::string taskNumber)
{
	auto it = _taskMap.find(taskNumber);

	if (it == _taskMap.end()) {
		std::cout << "Unable to execute task, task " << taskNumber
			  << " not found in map" << std::endl;
		exit(1);
	}
	(it->second)();
}
