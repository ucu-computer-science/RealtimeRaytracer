#pragma once

namespace Vector
{
	class Color :public Vec3
	{
	public:
		Color() { val[0] = 0; val[1] = 0; val[2] = 0; }
		Color(const float r, const float g, const float b) { val[0] = r; val[1] = g; val[2] = b; }

		static Color white() { return { 1, 1, 1 }; }
		static Color black() { return { 0, 0, 0 }; }

		float r() const { return val[0]; }
		float g() const { return val[1]; }
		float b() const { return val[2]; }
	};
}
