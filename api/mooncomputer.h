#ifndef MOONCOMPUTER_H
#define MOONCOMPUTER_H

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <sstream>
#include <memory>

// mangler_t entry -> std::pair<int, int>
//                 -> first = position
//                 -> second = value
typedef std::map<int, int> mangler_t;
typedef std::vector<int> program_t;
// progResult_t -> [0] = return value of pc = 0
//              -> [1] = first program output (op code = 4)
//              -> [2] = second program output (op code = 4)
//              -> [n] = n-th program output (op code = 4)
typedef std::vector<int> progResult_t;

class MoonComputer
{
	program_t _program;
	bool _verbose = false;
	bool _autoInsert = false;
	std::vector<int> _inputs;
	bool _showOutput = true;

	int getOpModes(bool& first, bool& second, const int op);
public:
	MoonComputer() {}
	~MoonComputer() {}

	typedef std::shared_ptr<MoonComputer> classPtr_t;

	void printProgramSnapshot();
	int doOperation(const int op, const int first, const bool firstMode,
			const int second, const bool secondMode, const int result,
			std::vector<int>::iterator& pc, int& var, progResult_t &pRes);
	void mangleTheCode(const mangler_t& mangler);
	int runMoonProgram();
	int runMoonProgram(progResult_t& programResult);
	void uploadProgramToComputer(program_t& program) { _program = program; }
	void setVerbose(bool flag) { _verbose = flag; }
	void openProgramFile(program_t &program);
	void setAutoInsert(bool flag, std::vector<int>* inputs = nullptr);
	void showOutput(bool flag) { _showOutput = flag; }
};

#endif // MOONCOMPUTER_H
