#pragma once

class Time
{
public:
	inline static float time = 0;
	inline static float deltaTime = 0;
	inline static float clampedDeltaTime = 0;

	static void updateTime();
};
