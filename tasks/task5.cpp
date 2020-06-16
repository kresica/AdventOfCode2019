#include "task5.h"
#include "mooncomputer.h"

REGISTER_TASK_TO_CREATOR(Task5, 5)
REGISTER_TASK_TO_EXECUTOR(Task5, 5)

std::shared_ptr<TaskCreator> Task5::create()
{
	return std::shared_ptr<TaskCreator>(new Task5());
}

void Task5::execute()
{
	program_t program;
	MoonComputer::classPtr_t moonCpu = MoonComputer::classPtr_t(new MoonComputer());

	moonCpu->openProgramFile(program);
	moonCpu->setVerbose(false);
	moonCpu->uploadProgramToComputer(program);

	progResult_t programResult;
	if (!moonCpu->runMoonProgram(programResult)) {
		return;
	}
	exit(1);
}
