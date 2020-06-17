#include "task90.h"
#include "mooncomputer.h"

REGISTER_TASK_TO_CREATOR(Task90, 9.0)
REGISTER_TASK_TO_EXECUTOR(Task90, 9.0)

std::shared_ptr<TaskCreator> Task90::create()
{
	return std::shared_ptr<TaskCreator>(new Task90());
}

void Task90::execute()
{
	program_t program;
	MoonComputer::classPtr_t moonCpu = MoonComputer::classPtr_t(new MoonComputer());

	moonCpu->openProgramFile(program);
	moonCpu->setVerbose(false);
	moonCpu->setTestMode(true);
	moonCpu->uploadProgramToComputer(program);
	std::vector<long long> autoInsert;
	autoInsert.push_back(1);
	moonCpu->setAutoInsert(true, &autoInsert);

	progResult_t programResult;
	if (!moonCpu->runMoonProgram(programResult)) {
		return;
	}
	exit(1);
}
