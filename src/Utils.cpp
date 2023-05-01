#include "Utils.h"

#include <fstream>
#include <stdexcept>
#include <sstream>

std::string readFile(const std::string& path)
{
	std::ifstream ifs(path);
	if (!ifs)
		throw std::runtime_error("Failed to open file: " + path);

	std::stringstream buffer;
	buffer << ifs.rdbuf();
	ifs.close();
	return buffer.str();
}
