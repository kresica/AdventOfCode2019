#include "task100.h"

REGISTER_TASK_TO_CREATOR(Task100, 10.0)
REGISTER_TASK_TO_EXECUTOR(Task100, 10.0)

std::shared_ptr<TaskCreator> Task100::create()
{
	return std::shared_ptr<TaskCreator>(new Task100());
}

void Task100::execute()
{
	AsteroidStation::makeAsteroidList(getFilename());

	std::pair<int,int> location;
	unsigned int numOfDetectableAsteroids = 0;
	AsteroidStation::detectBestLocation(location, numOfDetectableAsteroids);

	std::cout << "Most asteroids visible from location (" << location.first;
	std::cout << "," << location.second << "): " << numOfDetectableAsteroids << std::endl;
}
