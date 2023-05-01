#pragma once

#include <string>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class Shader
{
public:
	unsigned int id;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use() const;

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setFloat2(const std::string& name, glm::vec2 value) const;
	void setFloat3(const std::string& name, glm::vec3 value) const;
	void setFloat4(const std::string& name, glm::vec4 value) const;
	void setMatrix4X4(const std::string& name, glm::mat<4, 4, float> mat) const;

private:
	static void checkCompileErrors(unsigned int shader, const std::string& type);
};
