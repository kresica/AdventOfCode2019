#include "task11.h"

REGISTER_TASK_TO_CREATOR(Task11, "1.1")
REGISTER_TASK_TO_EXECUTOR(Task11, "1.1")

//bool Task11::_creatorRegistered = TaskCreator::registerTask("1.1", Task11::create());
//bool Task11::_executorRegistered = TaskExecutor::registerTask("1.1", Task11::execute);

TaskCreator* Task11::create()
{
	return new Task11();
}

static int calculateFuelMassRecursive(int mass)
{
	int fuelMass = mass / 3 - 2;
	if (fuelMass > 0)
		fuelMass += calculateFuelMassRecursive(fuelMass);
	return (fuelMass < 0) ? 0 : fuelMass;
}

void Task11::execute()
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
		fuelMassSum += calculateFuelMassRecursive(moduleVec[i]->getMass());
	}

	std::cout << "Mass of all modules is: " << fuelMassSum << std::endl;
}
