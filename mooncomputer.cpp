#include "mooncomputer.h"

program_t MoonComputer::_program;
bool MoonComputer::_verbose = true;

void MoonComputer::printProgramSnapshot()
{
	if (!_verbose) {
		return;
	}
	std::cout << "1. ";
	for (program_t::iterator pc = _program.begin(); pc != _program.end(); ++pc)
	{
		std::cout << *pc;
		if (std::distance(_program.begin(), pc) % 4 == 3) {
			std::cout << std::endl;
			std::cout << (std::distance(_program.begin(), pc+1)) / 4 + 1 << ". ";
		}
		else if (pc+1 != _program.end()) {
			std::cout << ",";
		}
	}
	std::cout << std::endl << std::endl;
}

int MoonComputer::doOperation(const int op, const int first,
			      const int second, const int result)
{
	if (op == 1) {
		_program[result] = _program[first] + _program[second];
		return 0;
	}
	else if (op == 2) {
		_program[result] = _program[first] * _program[second];
		return 0;
	}
	else if (op == 99) {
		if (_verbose) {
			std::cout << "Final program:" << std::endl;
			MoonComputer::printProgramSnapshot();
		}
		return 1;
	}
	else {
		if (_verbose) {
			std::cout << "Non-existent operation, crashing" << std::endl;
			std::cout << std::endl;
			std::cout << "Saving program snapshot" << std::endl;
			MoonComputer::printProgramSnapshot();
		}
		return -1;
	}
}

void MoonComputer::mangleTheCode(const mangler_t& mangler)
{
	for (mangler_t::const_iterator it = mangler.begin(); it != mangler.end(); ++it) {
		_program[it->first] = it->second;
	}
}

int MoonComputer::runMoonProgram()
{
	int result;
	return MoonComputer::runMoonProgram(result);
}

int MoonComputer::runMoonProgram(int& programResult)
{
	int operation;
	int firstOperand;
	int secondOperand;
	int result;
	int ret;

	for (program_t::iterator pc = _program.begin(); pc != _program.end(); ++pc) {
		if ((pc - _program.begin()) % 4 == 0) {
			operation = _program.at(pc - _program.begin());
		}
		else if ((pc - _program.begin()) % 4 == 1) {
			firstOperand = _program.at(pc - _program.begin());
		}
		else if ((pc - _program.begin()) % 4 == 2) {
			secondOperand = _program.at(pc - _program.begin());
		}
		else if ((pc - _program.begin()) % 4 == 3) {
			result = _program.at(pc - _program.begin());
			ret = MoonComputer::doOperation(operation, firstOperand,
					  secondOperand, result);
			programResult = _program[0];
			if (ret == -1) {
				int index = std::distance(_program.begin(), pc+1);
				if (_verbose) {
					std::cout << "Program crashed at " << index / 4 <<
						     ". instruction" << std::endl;
				}
				return -1;
			}
			else if (ret == 1) {
				int index = std::distance(_program.begin(), pc+1);
				if (_verbose) {
					std::cout << "Program ended at " << index / 4 <<
						     ". instruction" << std::endl;
				}
				return 0;
			}
		}
	}
	std::cout << "No halt operation reached" << std::endl;
	return -1;
}
