#include "wireboard.h"

void WireBoard::updatePosition(const char direction)
{
	if (direction == 'U') {
		++_currentPos.yPos;
	}
	else if (direction == 'R') {
		++_currentPos.xPos;
	}
	else if (direction == 'D') {
		--_currentPos.yPos;
	}
	else if (direction == 'L') {
		--_currentPos.xPos;
	}
}

int WireBoard::populateBoard(wire_t& wire)
{
	for (wire_t::iterator it = wire.begin(); it < wire.end(); ++it) {
		int distance = std::stoi((*it).substr(1, (*it).size()-1));
		if (distance < 0) {
			std::cout << "Wrong distance given, can't be negative" << std::endl;
			return -1;
		}
		for (; distance != 0; --distance) {
			WireBoard::updatePosition((*it)[0]);
			_wirePath->push_back(_currentPos);
		}
	}
	return 0;
}

std::shared_ptr<path_t> WireBoard::getWirePath() const
{
	return _wirePath;
}
