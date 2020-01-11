#include "wireboard.h"

static bool sortWirePath(const coordinate_t& prev, const coordinate_t& next)
{
	if (prev.xPos == next.xPos) {
		return (prev.yPos <= next.yPos);
	}
	return (prev.xPos < next.xPos);
}

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
			this->_wirePath->push_back(_currentPos);
		}
	}
	return 0;
}

std::shared_ptr<path_t> WireBoard::getWirePath() const
{
	return this->_wirePath;
}

void WireBoard::makeWireVector(const std::string& wireString, wire_t& wireVector)
{
	size_t nextCharacterPosition = 0;
	size_t currentDelimiterPosition = 0;
	for (std::string::const_iterator it = wireString.begin(); it != wireString.end();) {
		currentDelimiterPosition = wireString.find(',', nextCharacterPosition);
		std::string heading = wireString.substr(nextCharacterPosition, currentDelimiterPosition - nextCharacterPosition);
		wireVector.push_back(heading);
		it = wireString.begin() + static_cast<long long>(currentDelimiterPosition);
		if (!(nextCharacterPosition = currentDelimiterPosition + 1)) {
			break;
		}
	}
}

void WireBoard::checkForCollisions(const WireBoard& otherBoard, std::list<coordinate_t>& collisions)
{
	std::shared_ptr<path_t> firstWirePath = this->getWirePath();
	std::shared_ptr<path_t> secondWirePath = otherBoard.getWirePath();
	std::shared_ptr<path_t> firstWirePathSorted(new path_t);
	std::shared_ptr<path_t> secondWirePathSorted(new path_t);
	*firstWirePathSorted = *firstWirePath;
	*secondWirePathSorted = *secondWirePath;

	firstWirePathSorted->sort(sortWirePath);
	secondWirePathSorted->sort(sortWirePath);

	for (path_t::iterator it1 = firstWirePathSorted->begin(); it1 != firstWirePathSorted->end(); ++it1) {
		for (path_t::iterator it2 = secondWirePathSorted->begin(); it2 != secondWirePathSorted->end();) {
			if ((*it1).xPos > (*it2).xPos) {
				secondWirePathSorted->pop_front();
				it2 = secondWirePathSorted->begin();
				continue;
			}
			else if ((*it1).xPos == (*it2).xPos) {
				if ((*it1).yPos == (*it2).yPos) {
					collisions.push_back(*it1);
				}
				else if ((*it1).yPos < (*it2).yPos) {
					break;
				}
				++it2;
			}
			else {
				break;
			}
		}
	}
}

long long WireBoard::findNearestCrossing(const path_t& otherWirePath, const path_t& collisions)
{
	long long nearestDistance = 0;
	for (path_t::const_iterator it = collisions.begin(); it != collisions.end(); ++it) {
		path_t::const_iterator firstPathColIt = std::find(this->_wirePath->begin(),
								  this->_wirePath->end(),
								  *it);
		path_t::const_iterator secondPathColIt = std::find(otherWirePath.begin(),
								   otherWirePath.end(),
								   *it);
		auto crossingDistance = std::distance(static_cast<path_t::const_iterator>(this->_wirePath->begin()), firstPathColIt) +
					std::distance(otherWirePath.begin(), secondPathColIt) + 2;
		if (nearestDistance == 0 || crossingDistance < nearestDistance) {
			nearestDistance = crossingDistance;
		}
	}
	return nearestDistance;
}
