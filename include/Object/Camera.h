#pragma once

#include "Color.h"
#include "Object.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "thread_pool_light.hpp"
#include "Action.h"

struct Ray;

class Camera : public Object
{
public:
	inline static Camera* instance = nullptr;
	inline static Action onCameraMove{};
	inline static Action onCameraRotate{};

	float fov;
	glm::vec2 size;
	Color bgColor;
	float skip;
	BS::thread_pool_light pool;

	Camera(glm::vec3 pos, float fov, glm::vec2 size);

	void translate(const glm::vec3& v) override;
	void rotate(const glm::vec3& degrees) override;

	glm::vec3 getScreenCenter() const;
	glm::vec3 getLeftBotCorner() const;
	glm::vec3 getLeftTopCorner() const;
	glm::vec3 getRightTopCorner() const;
	glm::vec3 getRightBotCorner() const;

	void updatePixelMatrix(uint32_t* pixels, int width, int height);
	void setBackgroundColor(Color color) { bgColor = color; }
};
