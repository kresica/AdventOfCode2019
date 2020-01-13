#include "task50.h"
#include "mooncomputer.h"

REGISTER_TASK_TO_CREATOR(Task50, 5.0)
REGISTER_TASK_TO_EXECUTOR(Task50, 5.0)

std::shared_ptr<TaskCreator> Task50::create()
{
	return std::shared_ptr<TaskCreator>(new Task50());
}

void Task50::execute()
{
	std::ifstream iFile;
	std::stringbuf sb;

	program_t program;

	openFile(iFile);
	while (!iFile.eof()) {
		iFile.get(sb, ',');
		iFile.get();
		const int intCode = std::stoi(sb.str());
		program.push_back(intCode);

		sb.str("");
		sb.str().clear();
	}

	//MoonComputer::setVerbose(false);
	MoonComputer::uploadProgramToComputer(program);

	int programResult;
	if (!MoonComputer::runMoonProgram(programResult)) {
		return;
	}
	exit(1);
}
