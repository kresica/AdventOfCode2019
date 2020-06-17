#include "task9.h"
#include "mooncomputer.h"

REGISTER_TASK_TO_CREATOR(Task9, 9)
REGISTER_TASK_TO_EXECUTOR(Task9, 9)

std::shared_ptr<TaskCreator> Task9::create()
{
	return std::shared_ptr<TaskCreator>(new Task9());
}

void Task9::execute()
{
	program_t program;
	MoonComputer::classPtr_t moonCpu = MoonComputer::classPtr_t(new MoonComputer());

	moonCpu->openProgramFile(program);
	moonCpu->setVerbose(false);
	moonCpu->setTestMode(true);
	moonCpu->uploadProgramToComputer(program);

	progResult_t programResult;
	if (!moonCpu->runMoonProgram(programResult)) {
		return;
	}
	exit(1);
}
