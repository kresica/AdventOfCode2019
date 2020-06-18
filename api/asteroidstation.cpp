#include "asteroidstation.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
asteroidList_t AsteroidStation::_asteroidList;
std::pair<int, int> AsteroidStation::_bestLocation;
asteroidList_t AsteroidStation::_asteroidListSorted;

static double calculateAmplitude(const std::pair<int,int>& first, const std::pair<int,int>& second)
{
	return sqrt(pow(first.first - second.first, 2) + pow(first.second - second.second, 2));
}

static double calculateAngle(const std::pair<int,int>& first, const std::pair<int,int>& second)
{
	double angle = atan2(first.second - second.second, first.first - second.first) - M_PI_2;
	if (angle < 0) {
		return (angle += 2 * M_PI);
	}
	else {
		return angle;
	}
}

// -----------------------------------------------------------------
// Private
// -----------------------------------------------------------------

bool AsteroidStation::sortFunc(std::pair<int,int>& first, std::pair<int,int>& second)
{
	const std::pair<int,int> bestLocation = AsteroidStation::getBestLocation();

	double distanceFirst = calculateAmplitude(first, bestLocation);
	double distanceSecond = calculateAmplitude(second, bestLocation);

	double angleFirst = calculateAngle(bestLocation, first);
	double angleSecond = calculateAngle(bestLocation, second);

	if (fabs(angleFirst - angleSecond) < std::numeric_limits<double>::epsilon()) {
		if (distanceFirst < distanceSecond) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (angleFirst < angleSecond) {
		return true;
	}
	else {
		return false;
	}
}

// -----------------------------------------------------------------
// Public
// -----------------------------------------------------------------
void AsteroidStation::makeAsteroidList(const std::string& fName)
{
	std::ifstream iFile;
	char c;
	int row = 0;
	int col = 0;

	TaskExecutor::openFile(iFile, fName);

	while (!iFile.eof()) {
		if (!iFile.get(c))
			break;
		if (c == '\n') {
			++row;
			col = 0;
		}
		else if (c == '.') {
			++col;
			continue;
		}
		else if (c == '#') {
			_asteroidList.push_back(std::make_pair(col, row));
			++col;
		}
		else {
			std::cout << "Invalid character read, exiting" << std::endl;
			exit(1);
		}
	}

	std::sort(_asteroidList.begin(), _asteroidList.end());
}

void AsteroidStation::detectBestLocation(std::pair<int, int> &location,
					    unsigned int &numOfDetectableAsteroids)
{
	for (auto it1 = _asteroidList.begin(); it1 != _asteroidList.end(); ++it1) {
		std::list<double> detectedAngles;
		std::list<double>::iterator anglesIt = detectedAngles.begin();
		for (auto it2 = _asteroidList.begin(); it2 != _asteroidList.end(); ++it2) {
			if (it1 == it2)
				continue;
			double angle = atan2(it1->second - it2->second, it1->first - it2->first);
			if (std::find(detectedAngles.begin(), detectedAngles.end(), angle) == detectedAngles.end()) {
				detectedAngles.insert(anglesIt, angle);
				std::advance(anglesIt, 1);
			}
		}
		if (detectedAngles.size() > numOfDetectableAsteroids) {
			numOfDetectableAsteroids = detectedAngles.size();
			location = *it1;
		}
	}
	_bestLocation = location;
}

void AsteroidStation::turnOnAsteroidLaser()
{
	_asteroidListSorted = _asteroidList;
	getBestLocation();
	_asteroidListSorted.erase(std::find(_asteroidListSorted.begin(), _asteroidListSorted.end(), _bestLocation));
	std::sort(_asteroidListSorted.begin(), _asteroidListSorted.end(), sortFunc);

	asteroidList_t nextStageSorted;
	auto it1 = _asteroidListSorted.begin();
	auto it2 = it1 + 1;
	while (it2 != _asteroidListSorted.end()) {
		bool anglesEqual = fabs(calculateAngle(_bestLocation, *it1) - calculateAngle(_bestLocation, *it2)) < std::numeric_limits<double>::epsilon();
		if (anglesEqual && it2 != _asteroidListSorted.end()) {
			nextStageSorted.push_back(*it2);
			_asteroidListSorted.erase(it2);
		}
		else {
			++it1;
			++it2;
		}
		if (it2 == _asteroidListSorted.end() && !nextStageSorted.empty()) {
			_asteroidListSorted.insert(_asteroidListSorted.end(), nextStageSorted.begin(), nextStageSorted.end());
			nextStageSorted.clear();
			++it1;
			++it2;
		}
	}
}

const std::pair<int, int>& AsteroidStation::getBestLocation()
{
	unsigned int numOfDetectableAsteroids;
	DO_ONCE(detectBestLocation(_bestLocation, numOfDetectableAsteroids));
	return _bestLocation;
}
