#include "task41.h"

REGISTER_TASK_TO_CREATOR(Task41, 4.1)
REGISTER_TASK_TO_EXECUTOR(Task41, 4.1)

std::shared_ptr<TaskCreator> Task41::create()
{
	return std::shared_ptr<TaskCreator>(new Task41());
}

void Task41::execute()
{
	std::array<int, 6> lowRange;
	std::array<int, 6> highRange;
	std::string passwordRange = TaskCreator::getEntryValue();
	PasswordCracker passCrack;

	std::string stringToPass = passwordRange.substr(0, passwordRange.find("-"));
	passCrack.populateRange(lowRange, stringToPass);
	stringToPass = passwordRange.substr(passwordRange.find("-")+1);
	passCrack.populateRange(highRange, stringToPass);

	int validCombinationCounter = 0;
	while (true) {
		if (!passCrack.getNextValidNumber(lowRange, highRange)) {
			break;
		}
		validCombinationCounter += passCrack.checkForAdjacentNumbers(lowRange, 2, 2);
		passCrack.incrementNumber(lowRange);
	}
	std::cout << "Number of potential password combinations: " << validCombinationCounter <<
		     std::endl;
}
