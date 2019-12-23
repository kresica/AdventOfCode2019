#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>

#include "taskcreator.h"

static std::shared_ptr<TaskCreator> parseInputArguments(int argc, char *argv[])
{
	std::shared_ptr<TaskCreator> taskCreator;

	// First we got to create task
	for (int i = 0;; ++i) {
		if (i == argc) {
			std::cout << "No task number provided, exiting" << std::endl;
			exit(0);
		}
		std::string inArg(argv[i]);
		if (!inArg.compare("-t")) {
			float taskNumberFloat = std::atof(argv[i+1]);
			int taskNumber = (int)(taskNumberFloat * 10);
			taskCreator = TaskCreator::getInstance(taskNumber);
			break;
		}
	}

	for (int i = 0; i < argc; ++i) {
		std::string inArg(argv[i]);
		if (!inArg.compare("-f")) {
			std::string fileName;
			std::stringstream ss;
			ss << argv[i+1];
			ss >> fileName;
			taskCreator->setFilename(fileName);
		}
	}

	return taskCreator;
}

int main(int argc, char *argv[])
{
	static std::shared_ptr<TaskCreator> task = parseInputArguments(argc, argv);
	task->execute();
	exit(0);
}
