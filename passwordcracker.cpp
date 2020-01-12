#include "passwordcracker.h"

void PasswordCracker::populateRange(std::array<int,6>& rangeArray, std::string& password)
{
	for (const char& c : password) {
		char oneChar = c;
		rangeArray[static_cast<size_t>(&c - &password[0])] = std::atoi(&oneChar);
	}
}

void PasswordCracker::incrementNumber(std::array<int,6>& number)
{
	bool increaseNextLevel = true;
	for (auto it = number.rbegin(); it != number.rend(); ++it) {
		if (increaseNextLevel && (*it != 9)) {
			++(*it);
		}
		else {
			(*it) = 0;
			increaseNextLevel = true;
			continue;
		}
		increaseNextLevel = false;
		break;
	}
}

bool PasswordCracker::lowRangeEqualOrGreater(const std::array<int,6>& first, const std::array<int,6>& second)
{
	auto it1 = first.begin();
	auto it2 = second.begin();
	for ( ; ((it1 != first.end()) && (it2 != second.end())); ++it1, ++it2) {
		if (*it1 < *it2) {
			return false;
		}
		else if (*it1 == *it2) {
			continue;
		}
		else {
			return true;
		}
	}
	return true;
}

int PasswordCracker::getNextValidNumber(std::array<int,6>& lowRange, const std::array<int,6>& highRange)
{
	int lastDigit = -1;
	for (int& i : lowRange) {
		if (i < lastDigit) {
			i = lastDigit;
			if (lowRangeEqualOrGreater(lowRange, highRange)) {
				return false;
			}
		}
		lastDigit = i;
	}
	return true;
}

int PasswordCracker::checkForAdjacentNumbers(std::array<int, 6> &number,
					     const size_t minDigits,
					     const size_t maxDigits)
{
	std::list<std::list<int>> adjacentsList;
	std::list<int> digitList;
	for (const int& i : number) {
		if (digitList.empty()) {
			digitList.push_back(i);
			adjacentsList.push_back(digitList);
		}
		else if (*digitList.begin() == i) {
			adjacentsList.pop_back();
			digitList.push_back(i);
			adjacentsList.push_back(digitList);
		}
		else {
			digitList.clear();
			digitList.push_back(i);
			adjacentsList.push_back(digitList);
		}
		if (adjacentsList.empty()) {
			adjacentsList.push_back(digitList);
		}
	}
	for (const std::list<int>& list : adjacentsList) {
		if (list.size() >= minDigits && list.size() <= maxDigits) {
			return 1;
		}
	}
	return 0;
}
