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

	MoonComputer::openProgramFile(program);
	MoonComputer::setVerbose(false);
	MoonComputer::uploadProgramToComputer(program);

	int programResult;
	if (!MoonComputer::runMoonProgram(programResult)) {
		return;
	}
	exit(1);
}
