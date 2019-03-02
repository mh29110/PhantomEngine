#include "mat4.h"

namespace phantom {namespace maths {
	mat4x4::mat4x4()
	{
		for (int i = 0 ;i<4*4; i++)
		{
			elements[i] = 0.0f;
		}
	}

	mat4x4::mat4x4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}

		for (int i = 0;i < 4;i ++)
		{
			elements[i + i * 4] = diagonal;
		}
	}
	mat4x4 mat4x4::operator+(const mat4x4 &other)
	{
		mat4x4 result(1);
		result.elements[0];
		for (int column = 0;column < 4 ; column++)
		{
			for (int row = 0; row < 4 ; row++)
			{
				float sum = 0.0f;
				for (int i = 0;i < 4 ; i++ )
				{
				}
			}
		}
		return result;
	}
	// -------------translate -------------
	//矩阵按照某个向量平移
	mat4x4 & mat4x4::translate(float x, float y, float z)
	{
		elements[12] += elements[0] * x + elements[4] * y + elements[8] * z;
		elements[13] += elements[1] * x + elements[5] * y + elements[9] * z;
		elements[14] += elements[2] * x + elements[6] * y + elements[10] * z;
		elements[15] += elements[3] * x + elements[7] * y + elements[11] * z;
		return *this;
	}
	mat4x4 mat4x4::translation(const vec3& translation)
	{
		mat4x4 result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}
	mat4x4 mat4x4::identity()
	{
		return mat4x4(1.0f);
	}
}}
