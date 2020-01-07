#include "taskcreator.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
TaskCreator* TaskCreator::_instance = nullptr;
std::string TaskCreator::_taskNumber = "";
std::string TaskCreator::_fileName = "";
std::map<std::string, TaskCreator*> TaskCreator::_taskMap;

// -----------------------------------------------------------------
// Member functions
// -----------------------------------------------------------------
TaskCreator& TaskCreator::createTask(std::string taskNumber)
{
	std::map<std::string, TaskCreator*>::iterator it;
	it = _taskMap.find(taskNumber);

	if (it == _taskMap.end()) {
		std::cout << "Unable to create task, task " << taskNumber
			  << " not found in map" << std::endl;
		exit(1);
	}
	return *(it->second);
}

std::shared_ptr<TaskCreator> TaskCreator::getInstance(std::string taskNumber)
{
	if (_taskNumber == "") {
		_taskNumber = taskNumber;
	}
	if (_instance == nullptr) {
		_instance = &createTask(taskNumber);
	}

	if (taskNumber == _taskNumber)
		return std::shared_ptr<TaskCreator>(_instance);
	return nullptr;
}

std::string TaskCreator::getTaskNumber()
{
	return _taskNumber;
}

bool TaskCreator::registerTask(std::string taskName, TaskCreator* createFunc)
{
	std::map<std::string, TaskCreator*>::iterator it;
	it = _taskMap.find(taskName);

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
