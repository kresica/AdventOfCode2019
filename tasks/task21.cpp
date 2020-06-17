#include "task21.h"
#include "mooncomputer.h"

REGISTER_TASK_TO_CREATOR(Task21, 2.1)
REGISTER_TASK_TO_EXECUTOR(Task21, 2.1)

std::shared_ptr<TaskCreator> Task21::create()
{
	return std::shared_ptr<TaskCreator>(new Task21());
}


void Task21::execute()
{
	std::ifstream iFile;
	std::stringbuf sb;

	program_t program;
	progResult_t programResult;
	long long i = 0;

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

	std::unique_ptr<MoonComputer> moonComp_o;
	moonComp_o = std::unique_ptr<MoonComputer>(new MoonComputer);
	moonComp_o->setVerbose(false);

	for (int i = 0; i < 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			moonComp_o->uploadProgramToComputer(program);

			mangler_t mangler;
			mangler.insert(std::pair<int, int>(1, i));
			mangler.insert(std::pair<int, int>(2, j));
			moonComp_o->mangleTheCode(mangler);

			moonComp_o->runMoonProgram(programResult);
			if (programResult[0] == 19690720) {
				std::cout << "Got correct parameters:" << std::endl;
				std::cout << "100 * noun + verb = " << 100 * i + j << std::endl;
				return;
			}
		}
	}
}
