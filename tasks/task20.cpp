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
	long long i = 0;

	program_t program;

	openFile(iFile);
	while (!iFile.eof()) {
		iFile.get(sb, ',');
		iFile.get();
		const long long intCode = std::stoll(sb.str());
		program.insert(std::make_pair(i, intCode));
		++i;

		sb.str("");
		sb.str().clear();
	}

	MoonComputer::classPtr_t moonCpu = MoonComputer::classPtr_t(new MoonComputer());

	moonCpu->setVerbose(false);
	moonCpu->uploadProgramToComputer(program);

	mangler_t mangler;
	mangler.insert(std::pair<int, int>(1, 12));
	mangler.insert(std::pair<int, int>(2, 2));
	moonCpu->mangleTheCode(mangler);

	progResult_t programResult;
	if (!moonCpu->runMoonProgram(programResult)) {
		std::cout << "First program entry: " << programResult[0] << std::endl;
		return;
	}
	exit(1);
}
