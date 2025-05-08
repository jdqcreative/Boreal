#pragma once

#include <cmath>
#include <algorithm>

namespace alder {

	struct vec2
	{
		float x, y;

		// Constructors
		vec2()
			: x(0), y(0) {}
		vec2(float x, float y)
			: x(x), y(y) {}

		// Operator math overloads
		vec2 operator+(const vec2& other) const 
		{ 
			return { x + other.x, y + other.y }; 
		}

		vec2 operator-(const vec2& other) const
		{
			return { x - other.x, y - other.y };
		}

		vec2 operator*(float scalar) const
		{
			return { x * scalar, y * scalar };
		}

		vec2 operator/(float scalar) const
		{
			return { x / scalar, y / scalar };
		}

		// Operator comparison overloadds
		bool operator==(const vec2& other) const
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const vec2& other) const
		{
			return !(*this == other);
		}

		// Algorithms
		float dot(const vec2& other) const 
		{
			return x * other.x + y * other.y; 
		}

		float length() const 
		{ 
			return std::sqrt(dot(*this)); 
		}

		vec2 normalized() const
		{
			float len = length();
			return len > 0.0f ? (*this) / len : vec2(0, 0);
		}

		// Utility functions
		inline vec2 lerp(const vec2& a, const vec2& b, float t)
		{
			return a + (b - a) * t;
		}

		inline vec2 clamp(const vec2& v, const vec2& minV, const vec2& maxV)
		{
			return vec2(
				std::max(minV.x, std::min(maxV.x, v.x)),
				std::max(minV.y, std::min(maxV.y, v.y))
			);
		}

		inline bool nearlyEqual(const vec2& a, const vec2& b, float epsilon = 1e-5f)
		{
			return std::fabs(a.x - b.x) < epsilon && std::fabs(a.y - b.y) < epsilon;
		}

		float distance(const vec2& other) const
		{
			return (*this - other).length();
		}
	};

}