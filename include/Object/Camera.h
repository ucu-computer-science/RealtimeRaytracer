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

	float focalDistance, lensRadius;
	glm::vec2 size;
	Color bgColor;
	BS::thread_pool_light pool;

	Camera(glm::vec3 pos, float focalDistance, float lensRadius, glm::vec2 size);

	void setBackgroundColor(Color color);

	void setRot(glm::quat rot) override;
	void setPos(glm::vec3 pos) override;

	glm::vec3 getScreenCenter() const;
	glm::vec3 getLeftBotCorner() const;

	void updatePixelMatrix(const PixelMatrix& pixelMatrix);

	nlohmann::basic_json<> toJson() override;
};
