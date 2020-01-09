#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>

#include "taskcreator.h"
#include "taskexecutor.h"

void parseInputArguments(int argc, char *argv[], std::string &taskNumber)
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
			std::stringstream ss;
			ss << argv[i+1];
			ss >> taskNumber;
			taskCreator = TaskCreator::getInstance(taskNumber);
			if (taskCreator == nullptr) {
				std::cout << "No task created" << std::endl;
				exit(1);
			}
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
}

int main(int argc, char *argv[])
{
	std::string taskNumber;
	parseInputArguments(argc, argv, taskNumber);
	static std::unique_ptr<TaskExecutor> exec = TaskExecutor::getInstance();
	exec->execute(taskNumber);
	exit(0);
}
