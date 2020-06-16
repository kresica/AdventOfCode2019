#include "task11.h"

REGISTER_TASK_TO_CREATOR(Task11, 1.1)
REGISTER_TASK_TO_EXECUTOR(Task11, 1.1)

std::shared_ptr<TaskCreator> Task11::create()
{
	return std::shared_ptr<TaskCreator>(new Task11());
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
	std::vector<unsigned int> moduleVec;
	std::ifstream iFile;

	openFile(iFile);
	while (iFile >> mass) {
		moduleVec.push_back(mass);
	}

	for (unsigned int i = 0; i < moduleVec.size(); ++i) {
		fuelMassSum += calculateFuelMassRecursive(moduleVec[i]);
	}

	std::cout << "Mass of all modules is: " << fuelMassSum << std::endl;
}
