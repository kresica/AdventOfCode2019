#ifndef SIFDECODER_H
#define SIFDECODER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "taskexecutor.h"

#define IMAGE_WIDTH 25
#define IMAGE_HEIGHT 6

using imageLayer_t = std::array<std::array<int,IMAGE_WIDTH>,IMAGE_HEIGHT>;
using image_t = std::vector<imageLayer_t>;

class SifDecoder
{
	static std::map<std::string, image_t> _images;
	static std::map<std::string, imageLayer_t> _decodedImages;

	static void loadImageFromFile(const std::string& imageName);
	static void decodeImage(const std::string& imageName);
public:
	static const image_t& getImage(const std::string& imageName);
	static void deleteImage(const std::string& imageName);
	static const imageLayer_t& getDecodedImage(const std::string& imageName);
};

#endif // SIFDECODER_H
