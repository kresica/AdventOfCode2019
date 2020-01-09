#ifndef MOONCOMPUTER_H
#define MOONCOMPUTER_H

#include <iostream>
#include <map>
#include <vector>

// mangler_t entry -> std::pair<int, int>
//                 -> first = position
//                 -> second = value
typedef std::map<int, int> mangler_t;

class MoonComputer
{
	static std::vector<int> _program;
public:
	MoonComputer() {}
	~MoonComputer() {}
	static void printProgramSnapshot();
	static int doOperation(const int op, const int first,
			       const int second, const int result);
	static void mangleTheCode(const mangler_t &mangler);
	static int runMoonProgram();
	static void uploadProgramToComputer(const std::vector<int> &program);
};

#endif // MOONCOMPUTER_H
