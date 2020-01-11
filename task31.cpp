#include "task31.h"

REGISTER_TASK_TO_CREATOR(Task31, 3.1)
REGISTER_TASK_TO_EXECUTOR(Task31, 3.1)

TaskCreator* Task31::create()
{
	return new Task31();
}

void Task31::execute()
{
	std::ifstream iFile;
	std::string firstWireInput;
	std::string secondWireInput;
	wire_t firstWireVector;
	wire_t secondWireVector;
	int ret;

	openFile(iFile);
	iFile >> firstWireInput;
	iFile >> secondWireInput;

	std::unique_ptr<WireBoard> firstBoard_o = std::unique_ptr<WireBoard>(new WireBoard());
	firstBoard_o->makeWireVector(firstWireInput, firstWireVector);
	ret = firstBoard_o->populateBoard(firstWireVector);
	if (ret == -1) {
		std::cout << "Error, exiting program" << std::endl;
		exit(1);
	}

	std::unique_ptr<WireBoard> secondBoard_o = std::unique_ptr<WireBoard>(new WireBoard());
	secondBoard_o->makeWireVector(secondWireInput, secondWireVector);
	ret = secondBoard_o->populateBoard(secondWireVector);
	if (ret == -1) {
		std::cout << "Error, exiting program" << std::endl;
		exit(1);
	}

	std::list<coordinate_t> collisions;
	firstBoard_o->checkForCollisions(*secondBoard_o, collisions);
	path_t wir = *secondBoard_o->getWirePath();
	std::cout << "Nearest crossing is "
		  << firstBoard_o->findNearestCrossing(wir, collisions)
		  << " points away" << std::endl;
	return;
}

