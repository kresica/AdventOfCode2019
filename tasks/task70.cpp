#include "task70.h"

REGISTER_TASK_TO_CREATOR(Task70, 7.0)
REGISTER_TASK_TO_EXECUTOR(Task70, 7.0)

std::shared_ptr<TaskCreator> Task70::create()
{
	return std::shared_ptr<TaskCreator>(new Task70());
}

void Task70::execute()
{
	const int numOfAmps = 5;
	program_t program;
	MoonComputer::classPtr_t amp[numOfAmps];
	bool verbose = false;

	for (int i = 0; i < numOfAmps; ++i) {
		amp[i] = MoonComputer::classPtr_t(new MoonComputer());
		DO_ONCE(amp[i]->openProgramFile(program));
		amp[i]->uploadProgramToComputer(program);
		amp[i]->setVerbose(false);
		amp[i]->showOutput(false);
	}

	std::array<int, numOfAmps> phaseSettings = { 0,1,2,3,4 };
	std::array<int, numOfAmps> highestPhaseSettings = phaseSettings;
	int highestResult = INT_MIN;

	do {
		progResult_t result;
		int firstInput, secondInput, intRes;
		for (int i = 0; i < numOfAmps; ++i) {
			firstInput = phaseSettings[i];
			(i == 0) ? secondInput = 0 : secondInput = result[1];
			std::vector<int> autoInsertData;
			autoInsertData.push_back(firstInput);
			autoInsertData.push_back(secondInput);
			amp[i]->setAutoInsert(true, &autoInsertData);
			amp[i]->runMoonProgram(result);
			intRes = result[1];
			if (verbose)
				std::cout << i << ". amp result: " << intRes << std::endl;
			result.clear();
		}
		if (verbose) {
			for (int i = 0; i < numOfAmps; ++i)
				std::cout << phaseSettings[i];
			std::cout << " final result: " << intRes << std::endl;
		}

		if (highestResult < intRes) {
			highestResult = intRes;
			highestPhaseSettings = phaseSettings;
		}
	} while (std::next_permutation(phaseSettings.begin(), phaseSettings.end()));

	std::cout << "Highest result: " << highestResult << std::endl;
	std::cout << "Permutation: ";
	for (int i = 0; i < numOfAmps; ++i)
		std::cout << highestPhaseSettings[i];
	std::cout << std::endl;
}
