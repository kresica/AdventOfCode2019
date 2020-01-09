#include "task20.h"
#include "mooncomputer.h"

#include <ios>

REGISTER_TASK_TO_CREATOR(Task20, 2.0)
REGISTER_TASK_TO_EXECUTOR(Task20, 2.0)

TaskCreator* Task20::create()
{
	return new Task20();
}

void Task20::execute()
{
	std::ifstream iFile;
	std::stringbuf sb;

	std::vector<int> program;

	openFile(iFile);
	while (!iFile.eof()) {
		iFile.get(sb, ',');
		iFile.get();
		const int intCode = std::stoi(sb.str());
		program.push_back(intCode);

		sb.str("");
		sb.str().clear();
	}

	MoonComputer::uploadProgramToComputer(program);

	mangler_t mangler;
	mangler.insert(std::pair<int, int>(1, 12));
	mangler.insert(std::pair<int, int>(2, 2));
	MoonComputer::mangleTheCode(mangler);

	if (!MoonComputer::runMoonProgram()) {
		exit(0);
	}
	exit(1);
}
