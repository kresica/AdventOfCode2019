#ifndef TASKCREATOR_H
#define TASKCREATOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <map>

#define REGISTER_TASK_TO_CREATOR(className, taskName) \
	bool className::_creatorRegistered = \
	TaskCreator::registerTask(#taskName, className::create());

class TaskCreator
{
private:
	static TaskCreator* _instance;
	static std::string _taskNumber;
	static std::string _fileName;
	static std::map<std::string, TaskCreator*> _taskMap;

	static TaskCreator& createTask(std::string taskNumber);

public:
	static std::shared_ptr<TaskCreator> getInstance(std::string taskNumber);
	static std::string getTaskNumber();
	static bool registerTask(std::string taskName, TaskCreator *createFunc);
	static void setFilename(std::string fileName);
	static std::string getFilename();
};

#endif // TASKCREATOR_H
