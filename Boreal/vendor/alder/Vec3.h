#pragma once

#include <cmath>
#include <algorithm>

namespace alder {

	struct Vec3
	{
		float x, y, z;

		// Constructors
		Vec3()
			: x(0), y(0), z(0) {}
		Vec3(float x, float y, float z)
			: x(x), y(y), z(z) {}

		// Operator math overloads
		Vec3 operator+(const Vec3& other) const
		{
			return { x + other.x, y + other.y, z + other.z };
		}

		Vec3 operator-(const Vec3& other) const
		{
			return { x - other.x, y - other.y, z - other.z };
		}

		Vec3 operator*(float scalar) const
		{
			return { x * scalar, y * scalar, z * scalar };
		}

		Vec3 operator/(float scalar) const
		{
			return { x / scalar, y / scalar, z / scalar };
		}

		// Operator comparison overloads
		bool operator==(const Vec3& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(const Vec3& other) const
		{
			return !(*this == other);
		}

		// Algorithms
		float dot(const Vec3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		Vec3 cross(const Vec3& other) const
		{
			return {
			y * other.z - z *other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
			};
		}

		float length() const
		{
			return std::sqrt(dot(*this));
		}

		Vec3 normalized() const
		{
			float len = length();
			return len > 0.0f ? (*this) / len : Vec3(0, 0, 0);
		}

		// Utility functions
		inline Vec3 Lerp(const Vec3& a, const Vec3& b, float t)
		{
			return a + (b - a) * t;
		}

		inline Vec3 Clamp(const Vec3& v, const Vec3& min, const Vec3& max)
		{
			return Vec3(
			std::max(min.x, std::min(max.x, v.x)),
			std::max(min.y, std::min(max.y, v.y)),
			std::max(min.z, std::min(max.z, v.z))
			);
		}

		inline bool NearlyEqual(const Vec3& a, const Vec3& b, float epsilon = 1e-5f)
		{
			return std::fabs(a.x - b.x) < epsilon && std::fabs(a.y - b.y) < epsilon && std::fabs(a.z - b.z) < epsilon;
		}

		float distance(const Vec3& other) const
		{
			return (*this - other).length();
		}
	};

}