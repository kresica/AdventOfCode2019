#include "sifdecoder.h"

// -----------------------------------------------------------------
// Default static members definitions
// -----------------------------------------------------------------
std::map<std::string, image_t> SifDecoder::_images;
std::map<std::string, imageLayer_t> SifDecoder::_decodedImages;

// -----------------------------------------------------------------
// Private
// -----------------------------------------------------------------
void SifDecoder::loadImageFromFile(const std::string& imageName)
{
	std::ifstream iFile;
	char c;
	image_t image;
	imageLayer_t imageLayer = {0};

	TaskExecutor::openFile(iFile, imageName);
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
	_images.insert(std::make_pair(TaskCreator::getFilename(), image));
}

void SifDecoder::decodeImage(const std::string &imageName)
{
	imageLayer_t decodedImage;
	for (auto it = decodedImage.begin(); it != decodedImage.end(); ++it)
		it->fill(2);
	if (_images.find(imageName) == _images.end())
		getImage(imageName);

	image_t image = _images.find(imageName)->second;

	for (auto it = image.begin(); it != image.end(); ++it) {
		for (int row = 0; row < IMAGE_HEIGHT; ++row) {
			for (int col = 0; col < IMAGE_WIDTH; ++col) {
				if ((*it)[row][col] == 2)
					continue;
				if (decodedImage[row][col] == 2)
					decodedImage[row][col] = (*it)[row][col];
			}
		}
	}
	_decodedImages.insert(std::make_pair(imageName, decodedImage));
}

// -----------------------------------------------------------------
// Public
// -----------------------------------------------------------------
const image_t& SifDecoder::getImage(const std::string& imageName)
{
	if (_images.find(imageName) == _images.end())
		loadImageFromFile(imageName);
	return _images.at(imageName);
}

void SifDecoder::deleteImage(const std::string& imageName)
{
	_images.erase(imageName);
}

const imageLayer_t& SifDecoder::getDecodedImage(const std::string& imageName)
{
	if (_decodedImages.find(imageName) == _decodedImages.end())
		decodeImage(imageName);
	return _decodedImages.at(imageName);
}
