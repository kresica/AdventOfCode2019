#ifndef WIREBOARD_H
#define WIREBOARD_H

#include <iostream>
#include <memory>
#include <vector>
#include <list>

struct coordinate_t {
	int xPos;
	int yPos;

	coordinate_t(int x = 0, int y = 0) : xPos(x), yPos(y) {}
	~coordinate_t() {}
	bool operator==(const coordinate_t& coordinate) const
	{
		return (coordinate.xPos == xPos && coordinate.yPos == yPos);
	}
};

typedef struct coordinate_t coordinate_t;
typedef std::vector<std::string> wire_t;
typedef std::list<coordinate_t> path_t;

class WireBoard
{
	static path_t _wirePath;
	static coordinate_t _currentPos;

	static void updatePosition(const char position);
public:
	WireBoard() {}
	~WireBoard() {}
	static int populateBoard(wire_t& wire);
	static std::unique_ptr<path_t> getWirePath();
};

#endif // WIREBOARD_H
