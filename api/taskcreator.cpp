#include "taskcreator.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
std::shared_ptr<TaskCreator> TaskCreator::_instance = nullptr;
std::string TaskCreator::_taskNumber = "";
std::string TaskCreator::_fileName = "";
std::map<std::string, std::shared_ptr<TaskCreator>> TaskCreator::_taskMap;
std::string TaskCreator::_entryValue = "";

// -----------------------------------------------------------------
// Member functions
// -----------------------------------------------------------------
std::shared_ptr<TaskCreator> TaskCreator::createTask(std::string taskNumber)
{
	auto it = _taskMap.find(taskNumber);

	if (it == _taskMap.end()) {
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
	auto it = _taskMap.find(taskName);

	if (it == _taskMap.end()) {
		_taskMap[taskName] = createFunc;
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
