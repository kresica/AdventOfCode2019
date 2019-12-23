#include "taskcreator.h"
#include "spacemodule.h"

// -----------------------------------------------------------------
// Static members definitions
// -----------------------------------------------------------------
TaskCreator* TaskCreator::instance = 0;
std::string TaskCreator::_fileName = "";
void (* TaskCreator::_execFunction)() = nullptr;

// -----------------------------------------------------------------
// Member functions
// -----------------------------------------------------------------
std::shared_ptr<TaskCreator> TaskCreator::getInstance(int taskNumber)
{
	if (instance == 0) {
		instance = new TaskCreator(taskNumber);
	}
	return std::shared_ptr<TaskCreator>(instance);
}

TaskCreator::TaskCreator(int taskNumber)
{
	_taskNumber = taskNumber;
	switch (taskNumber) {
	case 10:
		_execFunction = &execFunction10;
	case 11:
		_execFunction = &execFunction11;
	}
}

void TaskCreator::openFile(std::ifstream &fileHandle)
{
	std::cout << "File to open: " << _fileName << std::endl;
	fileHandle.open(_fileName);
	if (!fileHandle) {
		std::cout << "Unable to open file" << std::endl;
		exit(1);
	}
}

void TaskCreator::setFilename(std::string fileName)
{
	_fileName = fileName;
}

void TaskCreator::execute()
{
	_execFunction();
}

// -----------------------------------------------------------------
// Task member functions
// -----------------------------------------------------------------
void TaskCreator::execFunction10()
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

static int calculateFuelMassRecursive(int mass)
{
	int fuelMass = mass / 3 - 2;
	if (fuelMass > 0)
		fuelMass += calculateFuelMassRecursive(fuelMass);
	return (fuelMass < 0) ? 0 : fuelMass;
}

void TaskCreator::execFunction11()
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
