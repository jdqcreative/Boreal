#pragma once

#include <cmath>
#include <algorithm>

namespace alder {

	struct vec4
	{
		union
		{
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { float s, t, p, q; };
			float data[4];
		};

		// Constructors
		vec4()
			: x(0), y(0), z(0), w(0) {}
		vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) {}

		// Operator math overloads
		vec4 operator+(const vec4& other) const
		{
			return { x + other.x, y + other.y, z + other.z, w + other.w };
		}

		vec4 operator-(const vec4& other) const
		{
			return { x - other.x, y - other.y, z - other.z, w - other.w };
		}

		vec4 operator*(float scalar) const
		{
			return { x * scalar, y * scalar, z * scalar, w * scalar };
		}

		vec4 operator/(float scalar) const
		{
			return { x / scalar, y / scalar, z / scalar, w / scalar };
		}

		// Operator comparison overloads
		bool operator==(const vec4& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool operator!=(const vec4& other) const
		{
			return !(*this == other);
		}

		// Algorithms
		float dot(const vec4& other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		float length() const
		{
			return std::sqrt(dot(*this));
		}

		vec4 normalized() const
		{
			float len = length();
			return len > 0.0f ? (*this) / len : vec4(0, 0, 0, 0);
		}

		// Utility functions
		inline vec4 lerp(const vec4& a, const vec4& b, float t)
		{
			return a + (b - a) * t;
		}

		inline vec4 clamp(const vec4& v, const vec4& min, const vec4& max)
		{
			return vec4(
			std::max(min.x, std::min(max.x, v.x)),
			std::max(min.y, std::min(max.y, v.y)),
			std::max(min.z, std::min(max.z, v.z)),
			std::max(min.w, std::min(max.w, v.w))
			);
		}

		inline bool nearlyEqual(const vec4& a, const vec4& b, float epsilon = 1e-5f)
		{
			return std::fabs(a.x - b.x) < epsilon && std::fabs(a.y - b.y) < epsilon && std::fabs(a.z - b.z) < epsilon && std::fabs(a.w - b.w) < epsilon;
		}

		float distance(const vec4& other) const
		{
			return (*this - other).length();
		}
	};

}