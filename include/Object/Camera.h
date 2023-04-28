#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <thread_pool_light.hpp>

#include "Color.h"
#include "Object.h"
#include "Action.h"

struct PixelMatrix;
struct Ray;

class Camera : public Object
{
public:
	inline static Camera* instance = nullptr;
	inline static Action onCameraMove{};
	inline static Action onCameraRotate{};

	float fov, lensRadius;
	glm::vec2 size;
	Color bgColor;
	BS::thread_pool_light pool;

	Camera(glm::vec3 pos, float fov, float lensRadius, glm::vec2 size);

	void translate(const glm::vec3& v) override;
	void rotate(const glm::vec3& degrees) override;

	glm::vec3 getScreenCenter() const;
	glm::vec3 getLeftBotCorner() const;

	void updatePixelMatrix(const PixelMatrix& pixelMatrix);
	void setBackgroundColor(Color color) { bgColor = color; }

	nlohmann::basic_json<> toJson() override;
};