#ifndef MOONCOMPUTER_H
#define MOONCOMPUTER_H

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <memory>

// mangler_t entry -> std::pair<long long, long long>
//                 -> first = position
//                 -> second = value
using mangler_t = std::map<long long, long long>;
using program_t = std::map<long long, long long>;
// progResult_t -> [0] = return value of pc = 0
//              -> [1] = first program output (op code = 4)
//              -> [2] = second program output (op code = 4)
//              -> [n] = n-th program output (op code = 4)
using progResult_t = std::vector<long long>;

class MoonComputer
{
	program_t _program;
	bool _verbose = false;
	bool _autoInsert = false;
	std::vector<long long> _inputs;
	bool _showOutput = true;
	long long _haltPc = 0;
	long long _var = 0;
	long long _relBase = 0;
	bool _testMode = false;

	void printProgramSnapshot();
	int assignOperands(long long& operand, const int mode, const long long value);
	int doOperation(const int op, const long long first, const int firstMode,
			const long long second, const int secondMode, const long long result,
			const int resultMode, std::map<long long, long long>::iterator& pc,
			progResult_t& pRes);
public:
	MoonComputer() {}
	~MoonComputer() {}

	typedef std::shared_ptr<MoonComputer> classPtr_t;

	void mangleTheCode(const mangler_t& mangler);
	int runMoonProgram();
	int runMoonProgram(progResult_t& programResult);
	void uploadProgramToComputer(program_t& program) { _program = program; }
	void setVerbose(bool flag) { _verbose = flag; }
	void openProgramFile(program_t& program);
	void setAutoInsert(bool flag, std::vector<long long>* inputs = nullptr);
	void showOutput(bool flag) { _showOutput = flag; }
	void setTestMode(bool flag) { _testMode = flag; }
};

#endif // MOONCOMPUTER_H
