#include "task71.h"

REGISTER_TASK_TO_CREATOR(Task71, 7.1)
REGISTER_TASK_TO_EXECUTOR(Task71, 7.1)

std::shared_ptr<TaskCreator> Task71::create()
{
	return std::shared_ptr<TaskCreator>(new Task71());
}

void Task71::execute()
{
	program_t program;
	bool verbose = false;

	intAmpArr_t phaseSettings = { 5,6,7,8,9 };
	intAmpArr_t highestPhaseSettings = phaseSettings;
	int highestResult = INT_MIN;

	do {
		bool allDone = false;
		std::array<bool, NUM_OF_AMPS> programDone = { false };
		progResAmpArr_t result;
		int intRes, progRes;
		bool start = true;
		progResAmpArr_t parentAmpResult;

		MoonComputer::classPtr_t amp[NUM_OF_AMPS];
		for (int i = 0; i < NUM_OF_AMPS; ++i) {
			amp[i] = MoonComputer::classPtr_t(new MoonComputer());
			DO_ONCE(amp[i]->openProgramFile(program));
			amp[i]->uploadProgramToComputer(program);
			amp[i]->setVerbose(false);
			amp[i]->showOutput(false);
		}

		do {
			for (int i = 0; i < NUM_OF_AMPS; ++i) {
				int prevAmpIdx = (i + NUM_OF_AMPS - 1) % NUM_OF_AMPS;
				if (programDone[i])
					continue;
				std::vector<long long> autoInsertData;
				if (!result.at(prevAmpIdx).empty()) {
					parentAmpResult.at(i) = result.at(prevAmpIdx);
					result.at(prevAmpIdx).clear();
				}

				if (start) {
					autoInsertData.push_back(phaseSettings[i]);
					if (i == 0) {
						autoInsertData.push_back(0);
					} else {
						while (parentAmpResult.at(i).size() > 0) {
							if (parentAmpResult.at(i).size() == 1) {
								autoInsertData.push_back(parentAmpResult.at(i)[0]);
								break;
							}
							autoInsertData.push_back(parentAmpResult.at(i)[0]);
							parentAmpResult.at(i).erase(parentAmpResult.at(i).begin());
						}
					}
				} else {
					while (parentAmpResult.at(i).size() > 0) {
						if (parentAmpResult.at(i).size() == 1) {
							autoInsertData.push_back(parentAmpResult.at(i)[0]);
							break;
						}
						autoInsertData.push_back(parentAmpResult.at(i)[0]);
						parentAmpResult.at(i).erase(parentAmpResult.at(i).begin());
					}
				}

				if (autoInsertData.empty())
					continue;
				amp[i]->setAutoInsert(true, &autoInsertData);
				progRes = amp[i]->runMoonProgram(result.at(i));
				if (progRes == 0) {
					programDone[i] = true;
					result.at(i).erase(result.at(i).begin());
				}
				intRes = result.at(i)[0];
				if (verbose)
					std::cout << i << ". amp result: " << intRes << std::endl;
			}
			start = false;

			for (int i = 0; i < NUM_OF_AMPS; ++i) {
				if (!programDone[i])
					break;
				if (programDone[i] && i == (NUM_OF_AMPS - 1)) {
					allDone = true;
				}
			}
		} while (!allDone);
		if (verbose) {
			for (int i = 0; i < NUM_OF_AMPS; ++i)
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
	for (int i = 0; i < NUM_OF_AMPS; ++i)
		std::cout << highestPhaseSettings[i];
	std::cout << std::endl;
}
