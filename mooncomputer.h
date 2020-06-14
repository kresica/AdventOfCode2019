#ifndef MOONCOMPUTER_H
#define MOONCOMPUTER_H

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <sstream>

// mangler_t entry -> std::pair<int, int>
//                 -> first = position
//                 -> second = value
typedef std::map<int, int> mangler_t;
typedef std::vector<int> program_t;

class MoonComputer
{
	static program_t _program;
	static bool _verbose;
	static bool _autoInsert;
	static std::vector<int> _inputs;

	static int getOpModes(bool& first, bool& second, const int op);
public:
	MoonComputer() {}
	~MoonComputer() {}
	MoonComputer(const MoonComputer& obj);

	static void printProgramSnapshot();
	static int doOperation(const int op, const int first, const bool firstMode,
			       const int second, const bool secondMode, const int result,
			       std::vector<int>::iterator& pc, int& var);
	static void mangleTheCode(const mangler_t& mangler);
	static int runMoonProgram();
	static int runMoonProgram(int& programResult);
	static void uploadProgramToComputer(program_t& program) { _program = program; }
	static void setVerbose(bool flag) { _verbose = flag; }
	static void openProgramFile(program_t &program);
	static void setAutoInsert(bool flag, std::vector<int>* inputs);
};

#endif // MOONCOMPUTER_H
