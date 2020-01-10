#include "task30.h"

REGISTER_TASK_TO_CREATOR(Task30, 3.0)
REGISTER_TASK_TO_EXECUTOR(Task30, 3.0)

TaskCreator* Task30::create()
{
	return new Task30();
}

static void makeWireVector(std::string& wireString, wire_t& wireVector)
{
	size_t nextCharacterPosition = 0;
	size_t currentDelimiterPosition = 0;
	for (std::string::iterator it = wireString.begin(); it != wireString.end();) {
		currentDelimiterPosition = wireString.find(',', nextCharacterPosition);
		std::string heading = wireString.substr(nextCharacterPosition, currentDelimiterPosition - nextCharacterPosition);
		wireVector.push_back(heading);
		it = wireString.begin() + static_cast<long long>(currentDelimiterPosition);
		if (!(nextCharacterPosition = currentDelimiterPosition + 1)) {
			break;
		}
	}
}

static bool sortWirePath(const coordinate_t& next, const coordinate_t& prev)
{
	if (prev.xPos == next.xPos) {
		if (prev.yPos <= next.yPos) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (prev.xPos < next.xPos) {
		return true;
	}
	else {
		return false;
	}
}

static void checkForCollisions(const WireBoard& firstBoard,
			       const WireBoard& secondBoard,
			       std::list<coordinate_t>& collisions)
{
	// @todo function execution time could be faster
	std::shared_ptr<path_t> firstWirePath;
	std::shared_ptr<path_t> secondWirePath;

	firstWirePath = firstBoard.getWirePath();
	secondWirePath = secondBoard.getWirePath();
	firstWirePath->sort(sortWirePath);
	secondWirePath->sort(sortWirePath);

	for (path_t::iterator it1 = firstWirePath->begin(); it1 != firstWirePath->end(); ++it1) {
		for (path_t::iterator it2 = secondWirePath->begin(); it2 != secondWirePath->end(); ++it2) {
			if ((*it1).xPos > (*it2).xPos) {
				break;
			}
			else if ((*it1).xPos == (*it2).xPos) {
				if ((*it1).yPos == (*it2).yPos) {
					collisions.push_back(*it1);
				}
			}
		}
	}
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

	makeWireVector(firstWireInput, firstWireVector);
	makeWireVector(secondWireInput, secondWireVector);

	std::unique_ptr<WireBoard> firstBoard_o = std::unique_ptr<WireBoard>(new WireBoard());
	ret = firstBoard_o->populateBoard(firstWireVector);
	if (ret == -1) {
		std::cout << "Error, exiting program" << std::endl;
		exit(1);
	}

	std::unique_ptr<WireBoard> secondBoard_o = std::unique_ptr<WireBoard>(new WireBoard());
	ret = secondBoard_o->populateBoard(secondWireVector);
	if (ret == -1) {
		std::cout << "Error, exiting program" << std::endl;
		exit(1);
	}

	std::list<coordinate_t> collisions;
	checkForCollisions(*firstBoard_o, *secondBoard_o, collisions);

	int shortestDistanceFromOrigin = 0;
	for (std::list<coordinate_t>::iterator it = collisions.begin(); it != collisions.end(); ++it) {
		int distanceFromOrigin = abs((*it).xPos) + abs((*it).yPos);
		if (!shortestDistanceFromOrigin || distanceFromOrigin < shortestDistanceFromOrigin) {
			shortestDistanceFromOrigin = distanceFromOrigin;
		}
	}
	std::cout << "Shortest cross-point distance: " << shortestDistanceFromOrigin << std::endl;
}
