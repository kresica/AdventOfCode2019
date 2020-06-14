#include "task70.h"

REGISTER_TASK_TO_CREATOR(Task70, 7.0)
REGISTER_TASK_TO_EXECUTOR(Task70, 7.0)

std::shared_ptr<TaskCreator> Task70::create()
{
	return std::shared_ptr<TaskCreator>(new Task70());
}

void Task70::execute()
{
	program_t program;
	MoonComputer::openProgramFile(program);

	int numOfAmps = 5;
	MoonComputer amp[numOfAmps];

	for (int i = 0; i < numOfAmps; ++i)
		amp[i].uploadProgramToComputer(program);

	int phaseSettings[] = { 0,1,2,3,4 };

	do {

	} while (std::next_permutation(phaseSettings, phaseSettings + numOfAmps));
}
