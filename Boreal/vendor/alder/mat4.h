#pragma once

#include <cmath>
#include <cstring>

namespace alder {

	struct Mat4
	{
		float m[16];

		// Constructor
		Mat4()
		{
			std::memset(m, 0, sizeof(m));
			m[0] = m[5] = m[10] = m[15] = 1.0f;
		}

		// Utility functions
		static Mat4 Identity()
		{
			return Mat4();
		}

		static Mat4 Translation(float x, float y, float z)
		{
			Mat4 result = Identity();
			result.m[12] = x;
			result.m[13] = y;
			result.m[14] = z;
			return result;
		}

		static Mat4 Scale(float x, float y, float z)
		{
			Mat4 result = Identity();
			result.m[0] = x;
			result.m[5] = y;
			result.m[10] = z;
			return result;
		}

		static Mat4 RotationZ(float angleRadians)
		{
			Mat4 result = Identity();
			float c = std::cos(angleRadians);
			float s = std::sin(angleRadians);
			result.m[0] = c;
			result.m[1] = s;
			result.m[4] = -s;
			result.m[5] = c;
			return result;
		}

		// Operator math overload
		Mat4 operator*(const Mat4& rhs) const
		{
			Mat4 result;
			for (int row = 0; row < 4; ++row)
			{
				for (int col = 0; col < 4; ++col)
				{
					result.m[col + row * 4] =
						m[0 + row * 4] * rhs.m[col + 0] +
						m[1 + row * 4] * rhs.m[col + 4] +
						m[2 + row * 4] * rhs.m[col + 8] +
						m[3 + row * 4] * rhs.m[col + 12];
				}
			}
			return result;
		}

		// Projection matrices
		static Mat4 Perspective(float fovRadians, float aspect, float nearZ, float farZ)
		{
			float f = 1.0f / std::tan(fovRadians / 2.0f);
			Mat4 result;
			result.m[0] = f / aspect;
			result.m[1] = 0.0f;
			result.m[2] = 0.0f;
			result.m[3] = 0.0f;

			result.m[4] = 0.0f;
			result.m[5] = f;
			result.m[6] = 0.0f;
			result.m[7] = 0.0f;

			result.m[8] = 0.0f;
			result.m[9] = 0.0f;
			result.m[10] = (farZ + nearZ) / (nearZ - farZ);
			result.m[11] = -1.0f;

			result.m[12] = 0.0f;
			result.m[13] = 0.0f;
			result.m[14] = (2.0f * farZ * nearZ) / (nearZ - farZ);
			result.m[15] = 0.0f;

			return result;
		}

		static Mat4 Orthographic(float left, float right, float bottom, float top, float nearZ, float farZ)
		{
			Mat4 result;
			result.m[0] = 2.0f / (right - left);
			result.m[1] = 0.0f;
			result.m[2] = 0.0f;
			result.m[3] = 0.0f;

			result.m[4] = 0.0f;
			result.m[5] = 2.0f / (top - bottom);
			result.m[6] = 0.0f;
			result.m[7] = 0.0f;

			result.m[8] = 0.0f;
			result.m[9] = 0.0f;
			result.m[10] = -2.0f / (farZ - nearZ);
			result.m[11] = 0.0f;

			result.m[12] = -(right + left) / (right - left);
			result.m[13] = -(top + bottom) / (top - bottom);
			result.m[14] = -(farZ + nearZ) / (farZ - nearZ);
			result.m[15] = 1.0f;

			return result;
		}
	};

}