#include "task20.h"
#include "mooncomputer.h"

REGISTER_TASK_TO_CREATOR(Task20, 2.0)
REGISTER_TASK_TO_EXECUTOR(Task20, 2.0)

std::shared_ptr<TaskCreator> Task20::create()
{
	return std::shared_ptr<TaskCreator>(new Task20());
}

void Task20::execute()
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

	MoonComputer::setVerbose(false);
	MoonComputer::uploadProgramToComputer(program);

	mangler_t mangler;
	mangler.insert(std::pair<int, int>(1, 12));
	mangler.insert(std::pair<int, int>(2, 2));
	MoonComputer::mangleTheCode(mangler);

	int programResult;
	if (!MoonComputer::runMoonProgram(programResult)) {
		std::cout << "First program entry: " << programResult << std::endl;
		return;
	}
	exit(1);
}
