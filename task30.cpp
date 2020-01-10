#include "task30.h"

REGISTER_TASK_TO_CREATOR(Task30, 3.0)
REGISTER_TASK_TO_EXECUTOR(Task30, 3.0)

TaskCreator* Task30::create()
{
	return new Task30();
}

static void makeWireVector(std::string& wireString, wire_t& wireVector)
{
	int nextCharacterPosition = 0;
	int currentDelimiterPosition = 0;
	for (std::string::iterator it = wireString.begin(); it != wireString.end();) {
		currentDelimiterPosition = wireString.find(',', nextCharacterPosition);
		std::string heading = wireString.substr(nextCharacterPosition, currentDelimiterPosition - nextCharacterPosition);
		wireVector.push_back(heading);
		it = wireString.begin() + currentDelimiterPosition;
		if (!(nextCharacterPosition = currentDelimiterPosition + 1)) {
			break;
		}
	}
}

static void checkForCollisions(const WireBoard& firstBoard,
			       const WireBoard& secondBoard,
			       std::list<coordinate_t>& collisions)
{
	std::unique_ptr<path_t> firstWirePath;
	std::unique_ptr<path_t> secondWirePath;

	firstWirePath = firstBoard.getWirePath();
	secondWirePath = secondBoard.getWirePath();

	for (path_t::iterator it = firstWirePath->begin(); it != firstWirePath->end(); ++it) {
		path_t::iterator it2;
		it2 = std::find(secondWirePath->begin(), secondWirePath->end(), *it);
		if (it2 != secondWirePath->end()) {
			collisions.push_back(*it2);
		}
	}
	std::cout << "";
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

	std::cout << firstWireInput << std::endl;
	std::cout << secondWireInput << std::endl;

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
}
