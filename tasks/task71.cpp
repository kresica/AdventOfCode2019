#include "task71.h"

REGISTER_TASK_TO_CREATOR(Task71, 7.1)
REGISTER_TASK_TO_EXECUTOR(Task71, 7.1)

std::shared_ptr<TaskCreator> Task71::create()
{
	return std::shared_ptr<TaskCreator>(new Task71());
}

void Task71::execute()
{
	const int numOfAmps = 5;
	program_t program;
	MoonComputer::classPtr_t amp[numOfAmps];
	bool verbose = true;

	for (int i = 0; i < numOfAmps; ++i) {
		amp[i] = MoonComputer::classPtr_t(new MoonComputer());
		DO_ONCE(amp[i]->openProgramFile(program));
		amp[i]->uploadProgramToComputer(program);
		amp[i]->setVerbose(false);
		amp[i]->showOutput(true);
	}

	std::array<int, numOfAmps> phaseSettings = { 5,6,7,8,9 };
	std::array<int, numOfAmps> highestPhaseSettings = phaseSettings;
	std::array<bool, numOfAmps> programDone = { false };
	int highestResult = INT_MIN;
	bool allDone = false;

	do {
		std::array<progResult_t, numOfAmps> result;
		int intRes;
		static bool start = true;
		do {
			for (int i = 0; i < numOfAmps; ++i) {
				if (programDone[i])
					continue;
				progResult_t parentAmpResult = result.at((i + numOfAmps - 1) % numOfAmps);
				std::vector<int> autoInsertData;

				if (start) {
					autoInsertData.push_back(phaseSettings[i]);
					if (i == 0) {
						autoInsertData.push_back(0);
					} else {
						while (parentAmpResult.size() >= 2) {
							autoInsertData.push_back(parentAmpResult[1]);
							if (!programDone[(i + numOfAmps - 1) % numOfAmps]) {
								parentAmpResult.erase(parentAmpResult.begin());
								parentAmpResult.erase(parentAmpResult.begin());
							}
						}
					}
					start = false;
				} else {
					while (parentAmpResult.size() >= 2) {
						autoInsertData.push_back(parentAmpResult[1]);
						if (!programDone[(i + numOfAmps - 1) % numOfAmps]) {
							parentAmpResult.erase(parentAmpResult.begin());
							parentAmpResult.erase(parentAmpResult.begin());
						}
					}
				}

				if (autoInsertData.empty())
					continue;
				amp[i]->setAutoInsert(true, &autoInsertData);
				amp[i]->runMoonProgram(result.at(i));
				if (result.at(i)[0] == 1)
					programDone[i] = true;
				intRes = result.at(i)[1];
				if (verbose)
					std::cout << i << ". amp result: " << intRes << std::endl;
			}

			for (int i = 0; i < numOfAmps; ++i) {
				if (!programDone[i])
					break;
			}
			allDone = true;
		} while (!allDone);
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
