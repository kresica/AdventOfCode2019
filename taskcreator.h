#ifndef TASKCREATOR_H
#define TASKCREATOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <vector>

class TaskCreator
{
private:
	TaskCreator(int taskNumber);
	static TaskCreator* instance;

	float _taskNumber;
	static std::string _fileName;
	static void openFile(std::ifstream &fileHandle);
	static void (*_execFunction)();

	// Task member functions
	static void execFunction10();
	static void execFunction11();
public:
	static std::shared_ptr<TaskCreator> getInstance(int taskNumber);
	void setFilename(std::string fileName);
	void execute();
};

#endif // TASKCREATOR_H
