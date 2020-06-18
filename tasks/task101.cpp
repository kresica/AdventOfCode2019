#include "task101.h"

REGISTER_TASK_TO_CREATOR(Task101, 10.1)
REGISTER_TASK_TO_EXECUTOR(Task101, 10.1)

std::shared_ptr<TaskCreator> Task101::create()
{
	return std::shared_ptr<TaskCreator>(new Task101());
}

void Task101::execute()
{
	AsteroidStation::makeAsteroidList(getFilename());
	AsteroidStation::turnOnAsteroidLaser();
	asteroidList_t asteroidListSorted = AsteroidStation::getAsteroidListSorted();

	auto it = asteroidListSorted.begin() + 199;
	std::cout << "200th vaporized asteroid is: " << it->first * 100 + it->second << std::endl;
}
