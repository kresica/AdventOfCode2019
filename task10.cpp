#include "task10.h"

REGISTER_TASK_TO_CREATOR(Task10, "1.0")
REGISTER_TASK_TO_EXECUTOR(Task10, "1.0")

//bool Task10::_creatorRegistered = TaskCreator::registerTask("1.0", Task10::create());
//bool Task10::_executorRegistered = TaskExecutor::registerTask("1.0", Task10::execute);

TaskCreator* Task10::create()
{
	return new Task10();
}

void Task10::execute()
{
	unsigned int mass;
	unsigned int fuelMassSum = 0;
	std::vector<std::unique_ptr<SpaceModule>> moduleVec;
	std::ifstream iFile;

	openFile(iFile);
	while (iFile >> mass) {
		std::unique_ptr<SpaceModule> mod(new SpaceModule(mass));
		moduleVec.push_back(std::move(mod));
	}

	for (unsigned int i = 0; i < moduleVec.size(); ++i) {
		fuelMassSum += moduleVec[i]->getMass() / 3 - 2;
	}

	std::cout << "Mass of all modules is: " << fuelMassSum << std::endl;
}
