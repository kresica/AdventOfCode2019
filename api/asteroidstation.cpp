#include "asteroidstation.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
asteroidList_t AsteroidStation::_asteroidList;

// -----------------------------------------------------------------
// Public
// -----------------------------------------------------------------
void AsteroidStation::makeAsteroidList(const std::string& fName)
{
	std::ifstream iFile;
	char c;
	int row = 0;
	int col = 0;
	std::list<std::pair<int,int>>::iterator it = _asteroidList.begin();

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
			_asteroidList.insert(it, std::make_pair(col, row));
			std::advance(it, 1);
			++col;
		}
		else {
			std::cout << "Invalid character read, exiting" << std::endl;
			exit(1);
		}
	}

	_asteroidList.sort();
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
			double angle = atan2(it1->first - it2->first, it1->second - it2->second);
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
}

void AsteroidStation::turnOnAsteroidLaser(const std::pair<int, int> location)
{

}
