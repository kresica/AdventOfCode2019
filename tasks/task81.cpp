#include "task81.h"

REGISTER_TASK_TO_CREATOR(Task81, 8.1)
REGISTER_TASK_TO_EXECUTOR(Task81, 8.1)

std::shared_ptr<TaskCreator> Task81::create()
{
	return std::shared_ptr<TaskCreator>(new Task81());
}

void Task81::execute()
{
	imageLayer_t decodedImage = SifDecoder::getDecodedImage(getFilename());

	for (int row = 0; row < IMAGE_HEIGHT; ++row) {
		for (int col = 0; col < IMAGE_WIDTH; ++col) {
			if (decodedImage[row][col] == 1)
				std::cout << "#";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}
