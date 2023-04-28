#include "ObjectParser.h"

#include <fstream>
#include <sstream>


Model::Model(const std::filesystem::path& path)
{
	parseObject(path);
}

void Model::parseObject(const std::filesystem::path& path)
{
	std::ifstream file(path);
	std::string line;

	std::vector<glm::vec3> vertexPositions;
	std::vector<glm::vec2> vertexUVs;
	std::vector<glm::vec3> vertexNormals;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string token;
		ss >> token;
		if (token == "v")
		{
			std::vector<float> pos;
			while (ss >> token)
			{
				pos.push_back(std::stof(token));
			}
			vertexPositions.emplace_back(pos[0], pos[1], pos[2]);
		}
		else if (token == "vt")
		{
			std::vector<float> uv;
			while (ss >> token)
			{
				uv.push_back(std::stof(token));
			}
			vertexUVs.emplace_back(uv[0], uv[1]);
		}
		else if (token == "vn")
		{
			std::vector<float> normal;
			while (ss >> token)
			{
				normal.push_back(std::stof(token));
			}
			vertexNormals.push_back(normalize(glm::vec3(normal[0], normal[1], normal[2])));
		}
		else if (token == "f")
		{
			std::vector<int> posIndexes;
			std::vector<int> uvIndexes;
			std::vector<int> normalIndexes;

			char delimiter;
			int num1, num2, num3;
			while (ss >> num1 >> delimiter >> num2 >> delimiter >> num3)
			{
				posIndexes.push_back(num1 - 1);
				uvIndexes.push_back(num2 - 1);
				normalIndexes.push_back(num3 - 1);
			}

			for (int i = 2; i < posIndexes.size(); i++)
			{
				auto v1 = Vertex(vertexPositions[posIndexes[0]], vertexUVs[uvIndexes[0]], vertexNormals[normalIndexes[0]]);
				auto v2 = Vertex(vertexPositions[posIndexes[i - 1]], vertexUVs[uvIndexes[i - 1]], vertexNormals[normalIndexes[i - 1]]);
				auto v3 = Vertex(vertexPositions[posIndexes[i]], vertexUVs[uvIndexes[i]], vertexNormals[normalIndexes[i]]);

				triangles.emplace_back(std::make_shared<Triangle>(nullptr, v1, v2, v3));
			}
		}
	}
}
