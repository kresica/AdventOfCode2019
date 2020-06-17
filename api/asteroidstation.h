#ifndef ASTEROIDSTATION_H
#define ASTEROIDSTATION_H

#include <fstream>
#include <list>
#include <cmath>
#include <algorithm>

#include "taskexecutor.h"

using asteroidList_t = std::list<std::pair<int,int>>;

class AsteroidStation
{
	static asteroidList_t _asteroidList;
public:
	AsteroidStation() {}
	~AsteroidStation() {}
	static void makeAsteroidList(const std::string &fName);
	static void detectBestLocation(std::pair<int, int>& location,
					  unsigned int& numOfDetectableAsteroids);
	static void turnOnAsteroidLaser(const std::pair<int, int> location);
	static const asteroidList_t& getAsteroidList() { return _asteroidList; }
};

#endif // ASTEROIDSTATION_H
