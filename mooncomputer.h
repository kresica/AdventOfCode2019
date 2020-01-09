#ifndef MOONCOMPUTER_H
#define MOONCOMPUTER_H

#include <iostream>
#include <map>
#include <vector>

// mangler_t entry -> std::pair<int, int>
//                 -> first = position
//                 -> second = value
typedef std::map<int, int> mangler_t;
typedef std::vector<int> program_t;

class MoonComputer
{
	static program_t _program;
	static bool _verbose;
public:
	MoonComputer() {}
	~MoonComputer() {}
	static void printProgramSnapshot();
	static int doOperation(const int op, const int first,
			       const int second, const int result);
	static void mangleTheCode(const mangler_t &mangler);
	static int runMoonProgram();
	static int runMoonProgram(int &programResult);
	static void uploadProgramToComputer(program_t &program) { _program = program; }
	static void setVerbose(bool flag) { _verbose = flag; }
};

#endif // MOONCOMPUTER_H
