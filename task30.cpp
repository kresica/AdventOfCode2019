#include "task30.h"

REGISTER_TASK_TO_CREATOR(Task30, 3.0)
REGISTER_TASK_TO_EXECUTOR(Task30, 3.0)

TaskCreator* Task30::create()
{
	return new Task30();
}

static void populateMesh(std::vector<std::string> &wire)
{

}

void Task30::execute()
{
	std::ifstream iFile;
	std::string firstWireInput;
	std::string secondWireInput;
	wire_t firstWireVector;
	wire_t secondWireVector;

	openFile(iFile);
	iFile >> firstWireInput;
	iFile >> secondWireInput;
	int previousDelimiterPosition = 0;
	int currentDelimiterPosition = 0;

	for (std::string::iterator it = firstWireInput.begin(); it != firstWireInput.end();) {
		currentDelimiterPosition = firstWireInput.find(',', previousDelimiterPosition + 1);
		std::cout << currentDelimiterPosition << std::endl;
		std::string heading = firstWireInput.substr(previousDelimiterPosition + 1, currentDelimiterPosition - previousDelimiterPosition);
		std::cout << heading << std::endl;
		firstWireVector.push_back(heading);
		it = firstWireInput.begin() + currentDelimiterPosition;
		previousDelimiterPosition = currentDelimiterPosition;
	}

	for (wire_t::iterator it = firstWireVector.begin(); it != firstWireVector.end(); ++it) {
	//	std::cout << *it << std::endl;
	}

	populateMesh(firstWireVector);
	populateMesh(secondWireVector);
}
