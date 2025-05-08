#pragma once

#include <cmath>

#include "forward.h"

namespace alder {

	inline mat4 translate(const mat4& matrix, const vec3& translation)
	{
		mat4 result = matrix;

		result.elements[0 + 3 * 4] += translation.x;
		result.elements[1 + 3 * 4] += translation.y;
		result.elements[2 + 3 * 4] += translation.z;

		return result;
	}

	inline static mat4 rotate(const mat4& matrix, float angleRadians, const vec3& axis)
	{
		vec3 normalizedAxis = axis.normalize();
		float c = cosf(angleRadians);
		float s = sinf(angleRadians);
		float oneMinusC = 1.0f - c;

		float x = normalizedAxis.x;
		float y = normalizedAxis.y;
		float z = normalizedAxis.z;

		mat4 rotation(1.0f);

		rotation.elements[0 + 0 * 4] = x * x * oneMinusC + c;
		rotation.elements[0 + 1 * 4] = x * y * oneMinusC - z * s;
		rotation.elements[0 + 2 * 4] = x * z * oneMinusC + y * s;

		rotation.elements[1 + 0 * 4] = y * x * oneMinusC + z * s;
		rotation.elements[1 + 1 * 4] = y * y * oneMinusC + c;
		rotation.elements[1 + 2 * 4] = y * z * oneMinusC - x * s;

		rotation.elements[2 + 0 * 4] = z * x * oneMinusC - y * s;
		rotation.elements[2 + 1 * 4] = z * y * oneMinusC + x * s;
		rotation.elements[2 + 2 * 4] = z * z * oneMinusC + c;

		return matrix * rotation;
	}

	inline mat4 scale(const mat4& matrix, const vec3& scale)
	{
		mat4 result = matrix;

		result.elements[0 + 0 * 4] *= scale.x;
		result.elements[1 + 1 * 4] *= scale.y;
		result.elements[2 + 2 * 4] *= scale.z;

		return result;
	}

	inline static mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up)
	{
		vec3 f = (center - eye).normalize();
		vec3 s = (f.cross(up)).normalize();
		vec3 u = s.cross(f);

		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = s.x;
		result.elements[1 + 0 * 4] = s.y;
		result.elements[2 + 0 * 4] = s.z;

		result.elements[0 + 1 * 4] = u.x;
		result.elements[1 + 1 * 4] = u.y;
		result.elements[2 + 1 * 4] = u.z;

		result.elements[0 + 2 * 4] = -f.x;
		result.elements[1 + 2 * 4] = -f.y;
		result.elements[2 + 2 * 4] = -f.z;

		result.elements[3 + 0 * 4] = -(s.dot(eye));
		result.elements[3 + 1 * 4] = -(u.dot(eye));
		result.elements[3 + 2 * 4] = (f.dot(eye));

		return result;
	}

	static void PrintMatrix(const mat4& mat)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int col = 0; col < 4; ++col)
			{
				float index = mat.elements[col * 4 + row];
				if (index == -0.0f)
					index = 0.0f;

				std::cout << index << " ";
			}
			std::cout << std::endl;
		}
	}

	inline static mat4 inverse(const mat4& m)
	{
		mat4 result;

		// Extract rotation part (upper-left 3x3)
		vec3 right	= vec3(m[0], m[1], m[2]);
		vec3 up		= vec3(m[4], m[5], m[6]);
		vec3 forward = vec3(m[8], m[9], m[10]);
		vec3 translation = vec3(m[12], m[13], m[14]);

		// Transpose rotation
		result[0] = right.x; result[1] = up.x; result[2] = forward.x; result[3] = 0.0f;
		result[4] = right.y; result[5] = up.y; result[6] = forward.y; result[7] = 0.0f;
		result[8] = right.z; result[9] = up.z; result[10] = forward.z; result[11] = 0.0f;

		// New translation = -R^T * translation
		result[12] = -(right.dot(translation));
		result[13] = -(up.dot(translation));
		result[14] = -(forward.dot(translation));
		result[15] = 1.0f;

		return result;
	}

	// Pointer functions
	inline static float* value_ptr(vec3& v)
	{
		return &v.x;
	}

	static const float* value_ptr(const vec3& v)
	{
		return &v.x;
	}

	inline static float* value_ptr(mat4& m)
	{
		return m.elements;
	}

	static const float* value_ptr(const mat4& m)
	{
		return m.elements;
	}

	// Rotation functions
	inline static float radians(float degrees)
	{
		return degrees * 0.01745329251994329576923690768489f; // pie / 180
	}

	inline static double radians(double degrees)
	{
		return degrees * 0.01745329251994329576923690768489f; // pie / 180
	}

	inline static float degrees(float radians)
	{
		return radians * 57.295779513082320876798154814105f;
	}

	inline static double degrees(double radians)
	{
		return radians * 57.295779513082320876798154814105f;
	}

	// Operator overloads
	inline vec4 operator*(const mat4& mat, const vec4& vec)
	{
		vec4 result;
		result.x =
			mat.elements[0 * 4 + 0] * vec.x +
			mat.elements[1 * 4 + 0] * vec.y +
			mat.elements[2 * 4 + 0] * vec.z +
			mat.elements[3 * 4 + 0] * vec.w;

		result.y =
			mat.elements[0 * 4 + 1] * vec.x +
			mat.elements[1 * 4 + 1] * vec.y +
			mat.elements[2 * 4 + 1] * vec.z +
			mat.elements[3 * 4 + 1] * vec.w;

		result.z =
			mat.elements[0 * 4 + 2] * vec.x +
			mat.elements[1 * 4 + 2] * vec.y +
			mat.elements[2 * 4 + 2] * vec.z +
			mat.elements[3 * 4 + 2] * vec.w;

		result.w =
			mat.elements[0 * 4 + 3] * vec.x +
			mat.elements[1 * 4 + 3] * vec.y +
			mat.elements[2 * 4 + 3] * vec.z +
			mat.elements[3 * 4 + 3] * vec.w;

		return result;
	}
	/*
	vec4 operator*(const vec4& vec, const mat4& mat)
	{
		vec4 result;
		result.x =
			vec.x * mat.elements[0 * 4 + 0] +
			vec.y * mat.elements[0 * 4 + 1] +
			vec.z * mat.elements[0 * 4 + 2] +
			vec.w * mat.elements[0 * 4 + 3];

		result.y =
			vec.x * mat.elements[1 * 4 + 0] +
			vec.y * mat.elements[1 * 4 + 1] +
			vec.z * mat.elements[1 * 4 + 2] +
			vec.w * mat.elements[1 * 4 + 3];

		result.z =
			vec.x * mat.elements[2 * 4 + 0] +
			vec.y * mat.elements[2 * 4 + 1] +
			vec.z * mat.elements[2 * 4 + 2] +
			vec.w * mat.elements[2 * 4 + 3];

		result.w =
			vec.x * mat.elements[3 * 4 + 0] +
			vec.y * mat.elements[3 * 4 + 1] +
			vec.z * mat.elements[3 * 4 + 2] +
			vec.w * mat.elements[3 * 4 + 3];

		return result;
	}
	*/
}