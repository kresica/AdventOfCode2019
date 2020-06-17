#include "taskexecutor.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
std::shared_ptr<TaskExecutor> TaskExecutor::_instance = nullptr;

static std::map<std::string, void (*)()>& getTaskMap()
{
	static std::map<std::string, void (*)()> _taskMap;
	return _taskMap;
}

// -----------------------------------------------------------------
// Member functions
// -----------------------------------------------------------------
bool TaskExecutor::registerTask(std::string taskName, void executeFunc())
{
	auto it = getTaskMap().find(taskName);

	if (it == getTaskMap().end()) {
		getTaskMap()[taskName] = executeFunc;
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
	std::string fName = TaskCreator::getFilename();
	openFile(fileHandle, fName);
}

void TaskExecutor::openFile(std::ifstream& fileHandle, const std::string fName)
{
	fileHandle.open(fName);
	if (!fileHandle) {
		std::cout << "Unable to open file " << fName << std::endl;
		exit(1);
	}
}

void TaskExecutor::execute(std::string taskNumber)
{
	auto it = getTaskMap().find(taskNumber);

	if (it == getTaskMap().end()) {
		std::cout << "Unable to execute task, task " << taskNumber
			  << " not found in map" << std::endl;
		exit(1);
	}
	(it->second)();
}
