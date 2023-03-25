#pragma once

//#include <SDL_stdinc.h>
#include <stdexcept>
#include "Color.h"
#include "Object.h"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"


class Camera : public Object
{
public:
	static Camera* instance;

	float fov;
	glm::vec2 resolution;
	glm::vec2 size;
	uint32_t bgColor32;
    int skip;
	Camera(glm::vec3 pos, float fov, glm::vec2 resolution, glm::vec2 size) : Object(pos), fov(fov), resolution(resolution), size(size), bgColor32(Color::black().toColor32())
	{
		if (instance != nullptr)
			throw std::runtime_error("Camera object already exists.");
		instance = this;
		skip = 1;
	}

	void setBackgroundColor(Color color) { bgColor32 = color.toColor32(); }

	glm::vec3 getBotLeftCorner() const;
	glm::vec3 getFocalPoint() const;
	void updatePixelMatrix(uint32_t* pixels) const;
    void setSkip(int newskip)
    {
        skip = newskip;
    }
    int getSkip() const
    {
        return skip;
    }
};
