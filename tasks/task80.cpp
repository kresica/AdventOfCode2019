#include "task80.h"

REGISTER_TASK_TO_CREATOR(Task80, 8.0)
REGISTER_TASK_TO_EXECUTOR(Task80, 8.0)

std::shared_ptr<TaskCreator> Task80::create()
{
	return std::shared_ptr<TaskCreator>(new Task80());
}

void Task80::execute()
{
	std::ifstream iFile;
	char c;

	imageLayer_t imageLayer = {0};
	std::vector<imageLayer_t> image;

	openFile(iFile);
	while (!iFile.eof()) {
		bool eofReached = false;
		for (int row = 0; row < IMAGE_HEIGHT; ++row) {
			for (int col = 0; col < IMAGE_WIDTH; ++col) {
				if (!iFile.get(c)) {
					eofReached = true;
					break;
				}
				imageLayer[row][col] = std::atoi(&c);
			}
			if (eofReached)
				break;
		}
		if (!eofReached) {
			image.push_back(imageLayer);
			imageLayer = {0};
		}
	}

	int leastAmountOfZeros = -1;
	unsigned int imageLayerIndex = -1;
	for (unsigned int i = 0; i < image.size(); ++i) {
		int zeroCounter = 0;
		for (int row = 0; row < IMAGE_HEIGHT; ++row) {
			for (int col = 0; col < IMAGE_WIDTH; ++col) {
				if (image.at(i)[row][col] == 0) {
					++zeroCounter;
				}
			}
		}
		if (zeroCounter < leastAmountOfZeros || leastAmountOfZeros == -1) {
			leastAmountOfZeros = zeroCounter;
			imageLayerIndex = i;
		}
	}

	int numOfOnes = 0;
	int numOfTwos = 0;
	for (int row = 0; row < IMAGE_HEIGHT; ++row) {
		for (int col = 0; col < IMAGE_WIDTH; ++col) {
			if (image.at(imageLayerIndex)[row][col] == 1) {
				++numOfOnes;
			} else if (image.at(imageLayerIndex)[row][col] == 2) {
				++numOfTwos;
			}
		}
	}

	std::cout << "Multiplication result of number of 1's and 2's on layer with least zeros: ";
	std::cout << numOfOnes * numOfTwos << std::endl;
}
