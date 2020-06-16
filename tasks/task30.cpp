#include "task30.h"

REGISTER_TASK_TO_CREATOR(Task30, 3.0)
REGISTER_TASK_TO_EXECUTOR(Task30, 3.0)

std::shared_ptr<TaskCreator> Task30::create()
{
	return std::shared_ptr<TaskCreator>(new Task30());
}

void Task30::execute()
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

	int shortestDistanceFromOrigin = 0;
	for (auto it = collisions.begin(); it != collisions.end(); ++it) {
		int distanceFromOrigin = abs((*it).xPos) + abs((*it).yPos);
		if (!shortestDistanceFromOrigin || distanceFromOrigin < shortestDistanceFromOrigin) {
			shortestDistanceFromOrigin = distanceFromOrigin;
		}
	}
	std::cout << "Shortest cross-point distance: " << shortestDistanceFromOrigin << std::endl;
}
