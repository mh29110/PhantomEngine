#pragma once 

#include <iostream>
#include "vector.h"

// The elements of the matrix are stored as column major order.
// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |
///////////////////////////////////////////////////////////////////////////
// 4x4 matrix
///////////////////////////////////////////////////////////////////////////
namespace phantom {namespace maths {
	struct  mat4x4 {
		mat4x4();
		mat4x4(float diagonal);
		mat4x4 identity();
		//mat4x4(float m00, float m01, float m02, float m03, // 1st column
		//	float m04, float m05, float m06, float m07, // 2nd column
		//	float m08, float m09, float m10, float m11, // 3rd column
		//	float m12, float m13, float m14, float m15);// 4th column
		inline vec4 getColumn(int index)
		{
			index *= 4;
			return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
		}
		//‘ÀÀ„
		/*mat4x4& multiply(const & other);*/
		mat4x4 operator + (const mat4x4& other);

		//transform matrix
		mat4x4& translate(float x, float y, float z);// translation by (x,y,z)
		static mat4x4 translation(const vec3& translation);
		//mat4x4& translate(const vec3 & tv);
		//mat4x4& rotate(float angle, const vec3& axis);// rotate angle(degree) along the given axix
		//mat4x4& rotate(float angle, float x, float y, float z);
		//mat4x4&    rotateX(float angle);                   // rotate on X-axis with degree
		//mat4x4&    rotateY(float angle);                   // rotate on Y-axis with degree
		//mat4x4&    rotateZ(float angle);                   // rotate on Z-axis with degree
		//mat4x4&    scale(float scale);                     // uniform scale
		//mat4x4&    scale(float sx, float sy, float sz);    // scale by (sx, sy, sz) on each axis
		//mat4x4&    lookAt(float tx, float ty, float tz);   // face object to the target direction
		//mat4x4&    lookAt(const vec3& target);

		//friend std::ostream & operator <<(std::ostream &os, const mat4x4 & m);

		// union  is  better
		union
		{
			float elements[4 * 4];
			vec4 columns[4];
		};
	};
} }

