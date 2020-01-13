#include "mooncomputer.h"

program_t MoonComputer::_program;
bool MoonComputer::_verbose = true;

int MoonComputer::getOpModes(bool& first, bool& second, const int op)
{
	if (!(op / 10000)) {
		first = false;
	}
	else if (op / 10000 == 1) {
		first = true;
	}
	else {
		goto exit;
	}

	if (!(op / 1000)) {
		second = false;
	}
	else if (op / 1000 == 1) {
		second = true;
	}
	else {
		goto exit;
	}

	if (!(op / 100)) {
		return 0;
	}
exit:
	std::cout << "Non-existent opcode, halting" << std::endl;
	return -1;
}

void MoonComputer::printProgramSnapshot()
{
	if (!_verbose) {
		return;
	}
	for (auto pc = _program.begin(); pc != _program.end(); ++pc) {
		std::cout << *pc;
		if (pc != _program.end()-1) {
			std::cout << ",";
		}
	}
	std::cout << std::endl << std::endl;
}

int MoonComputer::doOperation(const int op, const int first, const bool firstMode,
			      const int second, const bool secondMode, const int result,
			      std::vector<int>::iterator &pc, int &varPart)
{
	if (op == 1) {
		int firstParam = firstMode ? first : _program[first];
		int secondParam = secondMode ? second : _program[second];
		_program[result] = firstParam + secondParam;
		return 0;
	}
	else if (op == 2) {
		int firstParam = firstMode ? first : _program[first];
		int secondParam = secondMode ? second : _program[second];
		_program[result] = firstParam * secondParam;
		return 0;
	}
	else if (op == 3) {
		std::cout << "Enter input: ";
		std::cin >> _program[first];
		std::cout << std::endl;
		pc -= 2;
		varPart += 2;
		varPart %= 4;
		return 0;
	}
	else if (op == 4) {
		std::cout << (firstMode ? first : _program[first]);
		std::cout << std::endl;
		pc -= 2;
		varPart += 2;
		varPart %= 4;
		return 0;
	}
	else if (op == 5 || op == 6) {
		int firstParam = firstMode ? first : _program[first];
		int secondParam = secondMode ? second : _program[second];
		if ((op == 5) ? firstParam : !firstParam) {
			pc = _program.begin() + secondParam - 1;
			varPart = 4 - secondParam % 4;
		}
		return 0;
	}
	else if (op == 7 || op == 8) {
		int firstParam = firstMode ? first : _program[first];
		int secondParam = secondMode ? second : _program[second];
		if ((op == 7) ? (firstParam < secondParam) : (firstParam == secondParam)) {
			_program[result] = 1;
		}
		else {
			_program[result] = 0;
		}
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
	int firstMode;
	int secondOperand;
	int secondMode;
	int result;
	int ret;
	int varPart = 0;
	bool programLoaded = false;

	for (auto pc = _program.begin(); pc != _program.end(); ++pc) {
		if ((pc - _program.begin() + varPart) % 4 == 0) {
			operation = _program.at(pc - _program.begin());
			if (!(operation / 10000 % 10)) {
				firstMode = operation / 100 % 10;
				secondMode = operation / 1000 % 10;
				operation %= 100;
			}
			else {
				std::cout << "Non-supported 3rd parameter mode, halting"
					  << std::endl;
				return -1;
			}
		}
		else if ((pc - _program.begin() + varPart) % 4 == 1) {
			firstOperand = _program.at(pc - _program.begin());
		}
		else if ((pc - _program.begin() + varPart) % 4 == 2) {
			secondOperand = _program.at(pc - _program.begin());
		}
		else if ((pc - _program.begin() + varPart) % 4 == 3) {
			result = _program.at(pc - _program.begin());
			programLoaded = true;
		}
		if (!programLoaded) {
			continue;
		}

		ret = MoonComputer::doOperation(operation, firstOperand, firstMode, secondOperand,
						secondMode, result, pc, varPart);
		if (ret == -1) {
			int index = std::distance(_program.begin(), pc+1);
			if (_verbose) {
				std::cout << "Program crashed at " << index / 4 + 1 <<
					     ". instruction" << std::endl;
			}
			return -1;
		}
		else if (ret == 1) {
			programResult = _program[0];
			int index = std::distance(_program.begin(), pc+1);
			if (_verbose) {
				std::cout << "Program ended at " << index / 4 <<
					     ". instruction" << std::endl;
			}
			return 0;
		}
		programLoaded = false;
	}
	std::cout << "No halt operation reached" << std::endl;
	return -1;
}
