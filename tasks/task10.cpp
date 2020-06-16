#include "task10.h"

REGISTER_TASK_TO_CREATOR(Task10, 1.0)
REGISTER_TASK_TO_EXECUTOR(Task10, 1.0)

std::shared_ptr<TaskCreator> Task10::create()
{
	return std::shared_ptr<TaskCreator>(new Task10());
}

void Task10::execute()
{
	unsigned int mass;
	unsigned int fuelMassSum = 0;
	std::vector<unsigned int> moduleVec;
	std::ifstream iFile;

	openFile(iFile);
	while (iFile >> mass) {
		moduleVec.push_back(mass);
	}

	for (unsigned int i = 0; i < moduleVec.size(); ++i) {
		fuelMassSum += moduleVec[i] / 3 - 2;
	}

	std::cout << "Mass of all modules is: " << fuelMassSum << std::endl;
}
