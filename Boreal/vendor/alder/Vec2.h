#pragma once

#include <cmath>
#include <algorithm>

namespace alder {

	struct Vec2
	{
		float x, y;

		// Constructors
		Vec2()
			: x(0), y(0) {}
		Vec2(float x, float y)
			: x(x), y(y) {}

		// Operator math overloads
		Vec2 operator+(const Vec2& other) const 
		{ 
			return { x + other.x, y + other.y }; 
		}

		Vec2 operator-(const Vec2& other) const
		{
			return { x - other.x, y - other.y };
		}

		Vec2 operator*(float scalar) const
		{
			return { x * scalar, y * scalar };
		}

		Vec2 operator/(float scalar) const
		{
			return { x / scalar, y / scalar };
		}

		// Operator comparison overloadds
		bool operator==(const Vec2& other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Vec2& other) const
		{
			return !(*this == other);
		}

		// Algorithms
		float dot(const Vec2& other) const 
		{
			return x * other.x + y * other.y; 
		}

		float length() const 
		{ 
			return std::sqrt(dot(*this)); 
		}

		Vec2 normalized() const
		{
			float len = length();
			return len > 0.0f ? (*this) / len : Vec2(0, 0);
		}

		// Utility functions
		inline Vec2 Lerp(const Vec2& a, const Vec2& b, float t)
		{
			return a + (b - a) * t;
		}

		inline Vec2 Clamp(const Vec2& v, const Vec2& minV, const Vec2& maxV)
		{
			return Vec2(
				std::max(minV.x, std::min(maxV.x, v.x)),
				std::max(minV.y, std::min(maxV.y, v.y))
			);
		}

		inline bool NearlyEqual(const Vec2& a, const Vec2& b, float epsilon = 1e-5f)
		{
			return std::fabs(a.x - b.x) < epsilon && std::fabs(a.y - b.y) < epsilon;
		}

		float distance(const Vec2& other) const
		{
			return (*this - other).length();
		}
	};

}