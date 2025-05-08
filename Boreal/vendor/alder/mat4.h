#pragma once

#include <cmath>
#include <cstring>

namespace alder {

	struct mat4
	{
		float elements[16];

		// Constructor
		mat4()
		{
			for (int i = 0; i < 16; i++)
				elements[i] = 0.0f;
		}

		mat4(float diagonal)
		{
			for (int i = 0; i < 16; i++)
				elements[i] = 0.0f;

			elements[0 + 0 * 4] = 1.0f;
			elements[1 + 1 * 4] = 1.0f;
			elements[2 + 2 * 4] = 1.0f;
			elements[3 + 3 * 4] = 1.0f;
		}

		// Operator math overload
		mat4 operator*(const mat4& rhs) const
		{
			mat4 result;
			for (int row = 0; row < 4; ++row)
			{
				for (int col = 0; col < 4; ++col)
				{
					result.elements[col + row * 4] =
						elements[0 + row * 4] * rhs.elements[col + 0] +
						elements[1 + row * 4] * rhs.elements[col + 4] +
						elements[2 + row * 4] * rhs.elements[col + 8] +
						elements[3 + row * 4] * rhs.elements[col + 12];
				}
			}
			return result;
		}

		// Operator Type overload
		float& operator[](size_t index)
		{
			return elements[index];
		}

		const float& operator[](size_t index) const
		{
			return elements[index];
		}

		// Projection matrices
		static mat4 perspective(float fovRadians, float aspect, float nearZ, float farZ)
		{
			float f = 1.0f / std::tan(fovRadians / 2.0f);
			mat4 result;
			result.elements[0] = f / aspect;
			result.elements[1] = 0.0f;
			result.elements[2] = 0.0f;
			result.elements[3] = 0.0f;

			result.elements[4] = 0.0f;
			result.elements[5] = f;
			result.elements[6] = 0.0f;
			result.elements[7] = 0.0f;

			result.elements[8] = 0.0f;
			result.elements[9] = 0.0f;
			result.elements[10] = (farZ + nearZ) / (nearZ - farZ);
			result.elements[11] = -1.0f;

			result.elements[12] = 0.0f;
			result.elements[13] = 0.0f;
			result.elements[14] = (2.0f * farZ * nearZ) / (nearZ - farZ);
			result.elements[15] = 0.0f;

			return result;
		}

	};

	// Utility functions
	static mat4 identity()
	{
		return mat4(1.0f);
	}

	static mat4 ortho(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		mat4 result(1.0f);

		result.elements[0] = 2.0f / (right - left);
		result.elements[1] = 0.0f;
		result.elements[2] = 0.0f;
		result.elements[3] = 0.0f;

		result.elements[4] = 0.0f;
		result.elements[5] = 2.0f / (top - bottom);
		result.elements[6] = 0.0f;
		result.elements[7] = 0.0f;

		result.elements[8] = 0.0f;
		result.elements[9] = 0.0f;
		result.elements[10] = -2.0f / (farZ - nearZ);
		result.elements[11] = 0.0f;

		result.elements[12] = -(right + left) / (right - left);
		result.elements[13] = -(top + bottom) / (top - bottom);
		result.elements[14] = -(farZ + nearZ) / (farZ - nearZ);
		result.elements[15] = 1.0f;

		return result;
	}

	static mat4 translate(float x, float y, float z)
	{
		mat4 result = identity();
		result.elements[12] = x;
		result.elements[13] = y;
		result.elements[14] = z;
		return result;
	}

	static mat4 scale(float x, float y, float z)
	{
		mat4 result = identity();
		result.elements[0] = x;
		result.elements[5] = y;
		result.elements[10] = z;
		return result;
	}

	static mat4 rotationZ(float angleRadians)
	{
		mat4 result = identity();
		float c = std::cos(angleRadians);
		float s = std::sin(angleRadians);
		result.elements[0] = c;
		result.elements[1] = s;
		result.elements[4] = -s;
		result.elements[5] = c;
		return result;
	}
}