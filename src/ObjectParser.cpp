#include "ObjectParser.h"

#include <fstream>
#include <sstream>
#include <utility>


Model::Model(std::string path)
{
	this->path = std::move(path);
	parseObject();
}

void Model::parseObject()
{
	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string token;
		ss >> token;
		if (token == "v")
		{
			std::vector<float> vertex;
			while (ss >> token)
			{
				vertex.push_back(std::stof(token));
			}
			glm::vec3 p(vertex[0], vertex[1], vertex[2]);
			vertices.push_back(p);
		}
		else if (token == "f")
		{
			std::vector<int> triangle;
			while (ss >> token)
			{
				size_t pos = token.find('/');
				int index = std::stoi(token.substr(0, pos)) - 1; // OBJ indices are 1-based, so subtract 1
				triangle.push_back(index);
			}
			auto a = new Triangle(vertices[triangle[0]], vertices[triangle[1]], vertices[triangle[2]]);
			a->isTwoSided = true;
			triangles.emplace_back(a);
		}
	}
}
