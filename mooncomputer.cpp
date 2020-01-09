#include "mooncomputer.h"

std::vector<int> MoonComputer::_program;

void MoonComputer::printProgramSnapshot()
{
	std::cout << "1. ";
	for (std::vector<int>::iterator it = _program.begin();
	     it != _program.end(); ++it)
	{
		std::cout << *it;
		if (std::distance(_program.begin(), it) % 4 == 3) {
			std::cout << std::endl;
			std::cout << (std::distance(_program.begin(), it+1)) / 4 + 1 << ". ";
		}
		else if (it + 1 != _program.end()) {
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
		std::cout << "Final program:" << std::endl;
		MoonComputer::printProgramSnapshot();
		return 1;
	}
	else {
		std::cout << "Non-existent operation, crashing" << std::endl;
		std::cout << std::endl;
		std::cout << "Saving program snapshot" << std::endl;
		MoonComputer::printProgramSnapshot();
		return -1;
	}
}

void MoonComputer::mangleTheCode(const mangler_t &mangler)
{
	for (mangler_t::const_iterator it = mangler.begin(); it != mangler.end(); ++it) {
		_program[it->first] = it->second;
	}
}

int MoonComputer::runMoonProgram()
{
	int operation;
	int firstOperand;
	int secondOperand;
	int result;
	int ret;

	for (std::vector<int>::iterator i = _program.begin(); i != _program.end(); ++i) {
		if ((i - _program.begin()) % 4 == 0) {
			operation = _program.at(i - _program.begin());
		}
		else if ((i - _program.begin()) % 4 == 1) {
			firstOperand = _program.at(i - _program.begin());
		}
		else if ((i - _program.begin()) % 4 == 2) {
			secondOperand = _program.at(i - _program.begin());
		}
		else if ((i - _program.begin()) % 4 == 3) {
			result = _program.at(i - _program.begin());
			ret = MoonComputer::doOperation(operation, firstOperand,
					  secondOperand, result);
			if (ret == -1) {
				int index = std::distance(_program.begin(), i+1);
				std::cout << "Program crashed at " << index / 4 <<
					     ". instruction" << std::endl;
				return -1;
			}
			else if (ret == 1) {
				int index = std::distance(_program.begin(), i+1);
				std::cout << "Program ended at " << index / 4 <<
					     ". instruction" << std::endl;
				return 0;
			}
		}
	}
	std::cout << "No halt operation reached" << std::endl;
	return -1;
}

void MoonComputer::uploadProgramToComputer(const std::vector<int> &program)
{
	_program = std::move(program);
}
