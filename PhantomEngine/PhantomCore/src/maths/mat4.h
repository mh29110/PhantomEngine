#pragma once 

#include <iostream>
#include <assert.h>
#include "vector.h"

#include "AngleUtils.h"
#include "mat3.h"

// The elements of the matrix are stored as column major order.
// | 0 2 |    | 0 3 6 |    |  0  4  8 12 |
// | 1 3 |    | 1 4 7 |    |  1  5  9 13 |
//            | 2 5 8 |    |  2  6 10 14 |
//                         |  3  7 11 15 |
///////////////////////////////////////////////////////////////////////////
// 4x4 matrix
///////////////////////////////////////////////////////////////////////////
namespace Phantom { namespace maths {
	static float invf4X4(int i, int j, const float matrix[16]);
	struct  mat4x4 {
		mat4x4(float diagonal);
		mat4x4();
		mat4x4(float m00, float m01, float m02, float m03, // 1st column
			float m04, float m05, float m06, float m07, // 2nd column
			float m08, float m09, float m10, float m11, // 3rd column
			float m12, float m13, float m14, float m15);// 4th column
		vec4 getColumn(int index)
		{
			index *= 4;
			return vec4(elements[index], elements[index + 1], elements[index + 2], elements[index + 3]);
		}
		//运算
		/*mat4x4& multiply(const & other);*/
		mat4x4 operator * (const mat4x4& other);
		mat4x4& operator=(const float* _data)
		{
			std::memcpy(elements, _data, sizeof(float) * 4 * 4);
			return *this;
		}
		//transform matrix
		mat4x4& translate(const vec3& v);
		mat4x4& translate(float x, float y, float z);
		static mat4x4 identity();
		static mat4x4 translation(const vec3& translation);
		static mat4x4 rotation(float angle, const vec3& axis);
		static mat4x4 scale(const vec3& scale);
		//project 
		//对于以下静态方法考虑重构，比如LookAt矩阵，它需要在update时不断变化自身，每次创建一个值效率不好。(done)
		mat4x4 orthographic(float left, float right, float bottom, float top, float near, float far);
		mat4x4 perspective(float fov, float aspectRatio, float near, float far);
		mat4x4 LookAtMatrixBuild(const vec3& pos, const vec3& focal, const vec3 & up);
		
		friend std::ostream & operator <<(std::ostream &os, const mat4x4 & m);
		mat4x4& scale(float x, float y, float z);

	

		// union  is  better
		union
		{
			float elements[4 * 4];
			vec4 columns[4];
		};

		//逆矩阵，主要用于视图矩阵逆变化 ； 如果是正交矩阵<三单位垂直>可简化为转置矩阵
		void InverseMatrix4X4f()
		{
			float inv[16];
			double D = 0;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					inv[j * 4 + i] = invf4X4(i, j, elements);
				}
			}
			for (int k = 0; k < 4; k++) {
				float s = elements[k] * inv[k * 4];
				D += s;
			}
			if (D == 0) D = 0.00001;//todo should return when 0; 
			D = 1.0 / D;
			for (int i = 0; i < 16; i++)
			{
				elements[i] = static_cast<float>(inv[i] * D);
			}
		}
	};
// -----静态方案
	static float invf4X4(int i, int j, const float matrix[16])
	{
		int pre_i = ((i == 0) ? 3 : i - 1);
		int next_i = ((i + 1 == 4) ? 0 : i + 1);
		int next_next_i = ((i + 2 >= 4) ? i - 2 : i + 2);
		int pre_j = ((j == 0) ? 3 : j - 1);
		int next_j = ((j + 1 == 4) ? 0 : j + 1);
		int next_next_j = ((j + 2 >= 4) ? j - 2 : j + 2);
		int o = i - j < 0 ? j - i : i - j;

#define e(a, b) matrix[(a)*4 + (b)]
		float inv =
			+e(next_i, next_j)*e(next_next_i, next_next_j)*e(pre_i, pre_j)
			+ e(next_i, next_next_j)*e(next_next_i, pre_j)*e(pre_i, next_j)
			+ e(next_i, pre_j)*e(next_next_i, next_j)*e(pre_i, next_next_j)
			- e(next_i, next_j)*e(next_next_i, pre_j)*e(pre_i, next_next_j)
			- e(next_i, next_next_j)*e(next_next_i, next_j)*e(pre_i, pre_j)
			- e(next_i, pre_j)*e(next_next_i, next_next_j)*e(pre_i, next_j);

		return (o & 0x1) ? -inv : inv;
#undef e
	}
	


	//Inline  calculate function
	inline void MatrixTranslation(mat4x4 & matrix, const float x, const float y, const float z)
	{
		matrix.elements[12] = x;
		matrix.elements[13] = y;
		matrix.elements[14] = z;
	}



	//template <typename T>
	inline void MatrixPolarDecompose(const  mat3x3& in_matrix,
		mat3x3& U,
		mat3x3& P)
	{
		U = in_matrix;
		mat3x3 U_inv;
		mat3x3 U_pre;

		do {
			U_pre = U;
			U_inv = U;
			if (0 !=U_inv.InverseMatrix()) assert(0);
			mat3x3 U_inv_trans;
			U_inv_trans =  U_inv.Transpose();
			U = (U + U_inv_trans) * /*(T)*/0.5f;
		} while (U != U_pre);

		U_inv = U;
		if (0 != U_inv.InverseMatrix()) assert(0);
		P = in_matrix * U_inv;
	}

	inline void Matrix4X4fCompose(mat4x4& matrix, const vec3& rotation, const vec3& scalar, const vec3& translation)
	{
		mat4x4 matrix_rotate_x, matrix_rotate_y, matrix_rotate_z, matrix_rotate;
		/*MatrixRotationX(matrix_rotate_x, rotation[0]);
		MatrixRotationY(matrix_rotate_y, rotation[1]);
		MatrixRotationZ(matrix_rotate_z, rotation[2]);*/
		matrix_rotate = matrix_rotate_x * matrix_rotate_y * matrix_rotate_z;
		mat4x4 matrix_scale;
		//MatrixScale(matrix_scale, scalar);
		mat4x4 matrix_translation;
		MatrixTranslation(matrix_translation, translation.x,translation.y,translation.z);
		matrix = matrix_scale * matrix_rotate * matrix_translation;
	}

	inline void Matrix4X4fDecompose(const mat4x4& matrix, vec3& rotation, vec3& scalar, vec3& translation)
	{
		translation.SetComponents(matrix.elements[12], matrix.elements[13], matrix.elements[14]);

		// QR decompose the top-left 3x3 matrix
		const mat3x3 bases (
			matrix.elements[0], matrix.elements[1], matrix.elements[2],
			matrix.elements[4], matrix.elements[5], matrix.elements[6],
			matrix.elements[8], matrix.elements[9], matrix.elements[10]);

		mat3x3 U, P;
		
		MatrixPolarDecompose/*<float>*/(bases, U, P);

		float scale_x = P.elements[0];
		float scale_y = P.elements[4];
		float scale_z = P.elements[8];

		// decompose the scale
		scalar.SetComponents( scale_x, scale_y, scale_z );

		// decompose the rotation matrix
		float theta_x = std::atan2(U.elements[5], U.elements[8]);
		float theta_y = -std::asin(U.elements[2]);
		float theta_z = std::atan2(U.elements[1], U.elements[0]);

		rotation.SetComponents( theta_x, theta_y, theta_z );
	}
} }

