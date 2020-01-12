#ifndef PASSWORDCRACKER_H
#define PASSWORDCRACKER_H

#include <iostream>
#include <string>
#include <memory>
#include <list>

class PasswordCracker
{
	bool lowRangeEqualOrGreater(const std::array<int,6>& first,const std::array<int,6>& second);
public:
	PasswordCracker() {}
	~PasswordCracker() {}
	void populateRange(std::array<int,6>& rangeArray, std::string& password);
	void incrementNumber(std::array<int,6>& number);
	int getNextValidNumber(std::array<int,6>& lowRange, const std::array<int,6>& highRange);
	int checkForAdjacentNumbers(std::array<int,6>& number,
				    const size_t minDigits = 2,
				    const size_t maxDigits = 6);
};

#endif // PASSWORDCRACKER_H
