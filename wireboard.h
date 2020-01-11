#ifndef WIREBOARD_H
#define WIREBOARD_H

#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

typedef struct coordinate_t {
	int xPos;
	int yPos;

	coordinate_t(int x = 0, int y = 0) : xPos(x), yPos(y) {}
	~coordinate_t() {}
	bool operator==(const coordinate_t& coordinate) const
	{
		return (coordinate.xPos == xPos && coordinate.yPos == yPos);
	}
	friend std::ostream& operator<<(std::ostream& os, const coordinate_t& coor)
	{
		os << coor.xPos << "," << coor.yPos;
		return os;
	}
} coordinate_t;
typedef std::vector<std::string> wire_t;
typedef std::list<coordinate_t> path_t;

class WireBoard
{
	std::shared_ptr<path_t> _wirePath = std::shared_ptr<path_t>(new path_t);
	coordinate_t _currentPos;

	void updatePosition(const char position);
public:
	WireBoard() {}
	~WireBoard() {}
	int populateBoard(wire_t& wire);
	std::shared_ptr<path_t> getWirePath() const;
	void makeWireVector(const std::string& wireString, wire_t& wireVector);
	void checkForCollisions(const WireBoard& otherBoard, std::list<coordinate_t>& collisions);
	long long findNearestCrossing(const path_t& otherWirePath, const std::list<coordinate_t>& collisions);
};

#endif // WIREBOARD_H
