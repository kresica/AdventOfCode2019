#include "taskcreator.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
std::shared_ptr<TaskCreator> TaskCreator::_instance = nullptr;
std::string TaskCreator::_taskNumber = "";
std::string TaskCreator::_fileName = "";
std::string TaskCreator::_entryValue = "";

static std::map<std::string, std::shared_ptr<TaskCreator>>& getTaskMap()
{
	static std::map<std::string, std::shared_ptr<TaskCreator>> _taskMap;
	return _taskMap;
}

// -----------------------------------------------------------------
// Member functions
// -----------------------------------------------------------------
std::shared_ptr<TaskCreator> TaskCreator::createTask(std::string taskNumber)
{
	auto it = getTaskMap().find(taskNumber);

	if (it == getTaskMap().end()) {
		std::cout << "Unable to create task, task " << taskNumber
			  << " not found in map" << std::endl;
		exit(1);
	}
	return it->second;
}

std::shared_ptr<TaskCreator> TaskCreator::getInstance(std::string taskNumber)
{
	if (_taskNumber == "") {
		_taskNumber = taskNumber;
	}
	if (_instance == nullptr) {
		_instance = createTask(taskNumber);
	}

	if (taskNumber == _taskNumber)
		return std::shared_ptr<TaskCreator>(_instance);
	return nullptr;
}

std::string TaskCreator::getTaskNumber()
{
	return _taskNumber;
}

bool TaskCreator::registerTask(std::string taskName, std::shared_ptr<TaskCreator> createFunc)
{
	auto it = getTaskMap().find(taskName);

	if (it == getTaskMap().end()) {
		getTaskMap()[taskName] = createFunc;
		return true;
	}
	return false;
}

void TaskCreator::setFilename(std::string fileName)
{
	_fileName = fileName;
}

std::string TaskCreator::getFilename()
{
	return _fileName;
}

void TaskCreator::setEntryValue(std::string entryValue)
{
	_entryValue = entryValue;
}

std::string TaskCreator::getEntryValue()
{
	return _entryValue;
}
