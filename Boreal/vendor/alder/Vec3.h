#pragma once

#include <cmath>
#include <algorithm>

namespace alder {

	struct vec4;

	struct vec3
	{
		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			struct { float s, t, p; };
			float data[3];
		};

		// Constructors
		vec3()
			: x(0), y(0), z(0) {}
		vec3(float x, float y, float z)
			: x(x), y(y), z(z) {}
		vec3(const vec4& v4);

		// Operator math overloads
		vec3 operator+(const vec3& other) const
		{
			return { x + other.x, y + other.y, z + other.z };
		}

		vec3 operator-(const vec3& other) const
		{
			return { x - other.x, y - other.y, z - other.z };
		}

		vec3 operator*(float scalar) const
		{
			return { x * scalar, y * scalar, z * scalar };
		}

		vec3 operator/(float scalar) const
		{
			return { x / scalar, y / scalar, z / scalar };
		}

		vec3 operator-() const
		{
			return vec3{-x, -y, -z};
		}

		// Operator comparison overloads
		bool operator==(const vec3& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(const vec3& other) const
		{
			return !(*this == other);
		}

		// Algorithms
		float dot(const vec3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		vec3 cross(const vec3& other) const
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

		vec3 normalize() const
		{
			float len = length();
			return len > 0.0f ? (*this) / len : vec3(0, 0, 0);
		}

		static vec3 normalize(const vec3& v)
		{
			float len = v.length();
			return len > 0.0f ? (v) / len : vec3(0, 0, 0);
		}

		// Utility functions
		inline vec3 lerp(const vec3& a, const vec3& b, float t)
		{
			return a + (b - a) * t;
		}

		inline vec3 clamp(const vec3& v, const vec3& min, const vec3& max)
		{
			return vec3(
			std::max(min.x, std::min(max.x, v.x)),
			std::max(min.y, std::min(max.y, v.y)),
			std::max(min.z, std::min(max.z, v.z))
			);
		}

		inline bool nearlyEqual(const vec3& a, const vec3& b, float epsilon = 1e-5f)
		{
			return std::fabs(a.x - b.x) < epsilon && std::fabs(a.y - b.y) < epsilon && std::fabs(a.z - b.z) < epsilon;
		}

		float distance(const vec3& other) const
		{
			return (*this - other).length();
		}
	};

}