#include "mooncomputer.h"
#include "taskexecutor.h"

// -----------------------------------------------------------------
// Private
// -----------------------------------------------------------------
void MoonComputer::printProgramSnapshot()
{
	if (!_verbose) {
		return;
	}
	for (auto pc = _program.begin(); pc != _program.end(); ++pc) {
		std::cout << pc->second;
		if (pc->second != _program.end()->second-1) {
			std::cout << ",";
		}
	}
	std::cout << std::endl << std::endl;
}

int MoonComputer::assignOperands(long long &operand, const int mode, const long long value)
{
	if (mode == 0) {
		operand = _program[value];
	}
	else if (mode == 1) {
		operand = value;
	}
	else if (mode == 2) {
		operand = _program[_relBase + value];
	}
	else {
		return -1;
	}
	return 0;
}

int MoonComputer::doOperation(const int op, const long long first, const int firstMode,
			      const long long second, const int secondMode, const long long result,
			      const int resultMode, std::map<long long, long long>::iterator &pc,
			      progResult_t& pRes)
{
	if (op == 1) {
		long long firstParam, secondParam;
		if (assignOperands(firstParam, firstMode, first) != 0)
			return -1;
		if (assignOperands(secondParam, secondMode, second) != 0)
			return -1;

		if (resultMode == 0) {
			_program[result] = firstParam + secondParam;
		}
		else if (resultMode == 2) {
			_program[_relBase + result] = firstParam + secondParam;
		}
		else {
			return -1;
		}
		return 0;
	}
	else if (op == 2) {
		long long firstParam, secondParam;
		if (assignOperands(firstParam, firstMode, first) != 0)
			return -1;
		if (assignOperands(secondParam, secondMode, second) != 0)
			return -1;

		if (resultMode == 0) {
			_program[result] = firstParam * secondParam;
		}
		else if (resultMode == 2) {
			_program[_relBase + result] = firstParam * secondParam;
		}
		else {
			return -1;
		}
		return 0;
	}
	else if (op == 3) {
		if (!_autoInsert) {
			std::cout << "Enter input: ";
			long long input;
			std::cin >> input;
			if (firstMode == 0) {
				_program[first] = input;
			}
			else if (firstMode == 2) {
				_program[_relBase + first] = input;
			}
			else {
				return -1;
			}
		} else {
			if (_inputs.empty()) {
				return 2;
			}
			if (firstMode == 0) {
				_program[first] = _inputs[0];
			}
			else if (firstMode == 2) {
				_program[_relBase + first] = _inputs[0];
			}
			else {
				return -1;
			}
			_inputs.erase(_inputs.begin());
			return 0;
		}
		std::cout << std::endl;
		return 0;
	}
	else if (op == 4) {
		long long firstParam;
		assignOperands(firstParam, firstMode, first);
		if (_showOutput) {
			std::cout << firstParam;
			std::cout << std::endl;
		}
		pRes.push_back(firstParam);
		return 0;
	}
	else if (op == 5 || op == 6) {
		long long firstParam, secondParam;
		assignOperands(firstParam, firstMode, first);
		assignOperands(secondParam, secondMode, second);
		if ((op == 5) ? firstParam : !firstParam) {
			pc = _program.find(secondParam);
			_var = 4 - pc->first % 4;
			--pc;
		}
		return 0;
	}
	else if (op == 7 || op == 8) {
		long long firstParam, secondParam;
		assignOperands(firstParam, firstMode, first);
		assignOperands(secondParam, secondMode, second);
		if ((op == 7) ? (firstParam < secondParam) : (firstParam == secondParam)) {
			if (resultMode == 0) {
				_program[result] = 1;
			}
			else if (resultMode == 2) {
				_program[_relBase + result] = 1;
			}
			else {
				return -1;
			}
		}
		else {
			if (resultMode == 0) {
				_program[result] = 0;
			}
			else if (resultMode == 2) {
				_program[_relBase + result] = 0;
			}
			else {
				return -1;
			}
		}
		return 0;
	}
	else if (op == 9) {
		long long firstParam;
		assignOperands(firstParam, firstMode, first);
		_relBase += firstParam;
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

// -----------------------------------------------------------------
// Public
// -----------------------------------------------------------------
void MoonComputer::mangleTheCode(const mangler_t& mangler)
{
	for (mangler_t::const_iterator it = mangler.begin(); it != mangler.end(); ++it) {
		_program[it->first] = it->second;
	}
}

int MoonComputer::runMoonProgram()
{
	progResult_t result;
	return MoonComputer::runMoonProgram(result);
}

int MoonComputer::runMoonProgram(progResult_t &programResult)
{
	int operation;
	long long firstOperand;
	int firstMode;
	long long secondOperand;
	int secondMode;
	long long result;
	int resultMode;
	int ret;
	bool programLoaded = false;

	for (auto pc = _program.find(_haltPc); pc != _program.end(); ++pc) {
		if ((pc->first + _var) % 4 == 0) {
			operation = _program[pc->first];
			firstMode = operation / 100 % 10;
			secondMode = operation / 1000 % 10;
			resultMode = operation / 10000 % 10;
			operation %= 100;
			programLoaded = (operation == 99);
		}
		else if ((pc->first + _var) % 4 == 1) {
			firstOperand = _program[pc->first];
			programLoaded = (operation == 3 || operation == 4 || operation == 9);
			if (programLoaded) {
				_var += 2;
				_var %= 4;
			}
		}
		else if ((pc->first + _var) % 4 == 2) {
			secondOperand = _program[pc->first];
			programLoaded = (operation == 5 || operation == 6);
			if (programLoaded) {
				++_var;
				_var %= 4;
			}
		}
		else if ((pc->first + _var) % 4 == 3) {
			result = _program[pc->first];
			programLoaded = true;
		}
		if (!programLoaded) {
			continue;
		}

		ret = MoonComputer::doOperation(operation, firstOperand, firstMode, secondOperand,
						secondMode, result, resultMode, pc,
						programResult);
		if (ret == -1 && !_testMode) {
			long long index = pc->first + 1;
			if (_verbose) {
				std::cout << "Program crashed at " << index / 4 + 1 <<
					     ". instruction" << std::endl;
			}
			return -1;
		}
		else if (ret == 1) {
			programResult.insert(programResult.begin(), _program[0]);
			long long index = pc->first + 1;
			if (_verbose) {
				std::cout << "Program ended at " << index / 4 <<
					     ". instruction" << std::endl;
			}
			return 0;
		}
		else if (ret == 2) {
			if (_verbose) {
				std::cout << "Waiting for new input" << std::endl;
			}
			_haltPc = pc->first - 1;
			_var += 2;
			_var %= 4;
			return 1;
		}
		programLoaded = false;
	}
	std::cout << "No halt operation reached" << std::endl;
	return -1;
}

void MoonComputer::openProgramFile(program_t &program)
{
	std::ifstream iFile;
	std::stringbuf sb;
	long long i = 0;

	TaskExecutor::openFile(iFile);
	while (!iFile.eof()) {
		iFile.get(sb, ',');
		iFile.get();
		const long long intCode = std::stoll(sb.str());
		program.insert(std::make_pair(i, intCode));
		++i;

		sb.str("");
		sb.str().clear();
	}
}

void MoonComputer::setAutoInsert(bool flag, std::vector<long long>* inputs)
{
	_autoInsert = flag;
	if (!flag)
		return;
	if (inputs == nullptr) {
		std::cout << "WARNING! Auto insert selected but no inputs provided!" << std::endl;
		std::cout << "         Undefined behavior might occur!" << std::endl;
		return;
	}
	_inputs.insert(_inputs.end(), inputs->begin(), inputs->end());
}
