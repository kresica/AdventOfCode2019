#ifndef ASTEROIDSTATION_H
#define ASTEROIDSTATION_H

#include <fstream>
#include <list>
#include <cmath>
#include <algorithm>

#include "taskexecutor.h"

using asteroidList_t = std::vector<std::pair<int,int>>;

class AsteroidStation
{
	static asteroidList_t _asteroidList;
	static std::pair<int,int> _bestLocation;
	static asteroidList_t _asteroidListSorted;

	static bool sortFunc(std::pair<int, int> &first, std::pair<int, int> &second);
public:
	AsteroidStation() {}
	~AsteroidStation() {}
	static void makeAsteroidList(const std::string &fName);
	static void detectBestLocation(std::pair<int, int>& location,
					  unsigned int& numOfDetectableAsteroids);
	static void turnOnAsteroidLaser();
	static const asteroidList_t& getAsteroidList() { return _asteroidList; }
	static const std::pair<int, int>& getBestLocation();
	static const asteroidList_t& getAsteroidListSorted() { return _asteroidListSorted; }
};

#endif // ASTEROIDSTATION_H
