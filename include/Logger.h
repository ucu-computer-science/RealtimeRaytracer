#pragma once

class Logger
{
	inline static int frameCount = 0;
	inline static int lastFrameTime = 0;
public:
	static void logStats();

	inline static int fps = 0;
	static void updateFPSCounter();
};