#ifndef TASK41_H
#define TASK41_H

#include "task40.h"
#include <functional>

class Task41 : public Task40
{
	static bool _creatorRegistered;
	static bool _executorRegistered;
public:
	Task41() {}
	~Task41() {}
	static std::shared_ptr<TaskCreator> create();
	static void execute();
	int checkValidity(std::array<int,6>& lowRange,
			  const std::array<int,6>& highRange,
			  int& validCombinationCounter);
};

#endif // TASK41_H
