#include "wireboard.h"

std::list<coordinate_t> WireBoard::_wirePath;
coordinate_t WireBoard::_currentPos;

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
			_wirePath.push_back(_currentPos);
		}
	}
	return 0;
}

std::unique_ptr<path_t> WireBoard::getWirePath()
{
	return std::unique_ptr<path_t>(&_wirePath);
}
