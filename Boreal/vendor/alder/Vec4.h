#pragma once

#include <cmath>
#include <algorithm>

namespace alder {

	struct Vec4
	{
		float x, y, z, w;

		// Constructors
		Vec4()
			: x(0), y(0), z(0), w(0) {}
		Vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w) {}

		// Operator math overloads
		Vec4 operator+(const Vec4& other) const
		{
			return { x + other.x, y + other.y, z + other.z, w + other.w };
		}

		Vec4 operator-(const Vec4& other) const
		{
			return { x - other.x, y - other.y, z - other.z, w - other.w };
		}

		Vec4 operator*(float scalar) const
		{
			return { x * scalar, y * scalar, z * scalar, w * scalar };
		}

		Vec4 operator/(float scalar) const
		{
			return { x / scalar, y / scalar, z / scalar, w / scalar };
		}

		// Operator comparison overloads
		bool operator==(const Vec4& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool operator!=(const Vec4& other) const
		{
			return !(*this == other);
		}

		// Algorithms
		float dot(const Vec4& other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		float length() const
		{
			return std::sqrt(dot(*this));
		}

		Vec4 normalized() const
		{
			float len = length();
			return len > 0.0f ? (*this) / len : Vec4(0, 0, 0, 0);
		}

		// Utility functions
		inline Vec4 Lerp(const Vec4& a, const Vec4& b, float t)
		{
			return a + (b - a) * t;
		}

		inline Vec4 Clamp(const Vec4& v, const Vec4& min, const Vec4& max)
		{
			return Vec4(
			std::max(min.x, std::min(max.x, v.x)),
			std::max(min.y, std::min(max.y, v.y)),
			std::max(min.z, std::min(max.z, v.z)),
			std::max(min.w, std::min(max.w, v.w))
			);
		}

		inline bool NearlyEqual(const Vec4& a, const Vec4& b, float epsilon = 1e-5f)
		{
			return std::fabs(a.x - b.x) < epsilon && std::fabs(a.y - b.y) < epsilon && std::fabs(a.z - b.z) < epsilon && std::fabs(a.w - b.w) < epsilon;
		}

		float distance(const Vec4& other) const
		{
			return (*this - other).length();
		}
	};

}