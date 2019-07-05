#pragma once 

#include <iostream>
#include "vector.h"


namespace Phantom { namespace maths {
	struct  mat3x3 {
		mat3x3(float diagonal);
		mat3x3();
		mat3x3(float m00,float m01, float m02, // 1st column
			float m03, float m04,  float m05, // 2nd column
			 float m06, float m07, float m08); // 3rd column
		// union  is  better
		union
		{
			float elements[3 * 3];
			vec4 columns[3];
		};

		mat3x3 Transpose();

		mat3x3& operator=(const mat3x3& mat);
		bool mat3x3::operator!=(const mat3x3 &other);
		mat3x3 mat3x3::operator+(const mat3x3 &other);

		mat3x3 mat3x3::operator*(const mat3x3 &other) const;
		mat3x3 mat3x3::operator*(const float factor) const;
		int InverseMatrix();
	};
} }

