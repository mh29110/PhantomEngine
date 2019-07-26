#include "mat3.h"
using namespace Phantom;
using namespace maths;
mat3x3::mat3x3(float diagonal)
{
	for (int i = 0; i < 3 * 3; i++) {
		elements[i] = 0.0f;
	}

	for (int i = 0; i < 3; i++)
	{
		elements[i + i * 3] = diagonal;
	}
}

mat3x3::mat3x3():mat3x3(1.0f)
{
	//todo wait for verification
}
mat3x3::mat3x3(float m00, float m01, float m02, // 1st column
	float m03, float m04, float m05, // 2nd column
	float m06, float m07, float m08) // 3rd column
{
	elements[0] = m00; elements[3] = m03; elements[6] = m06;
	elements[1] = m01; elements[4] = m04; elements[7] = m07;
	elements[2] = m02; elements[5] = m05; elements[8] = m08;
}

Phantom::maths::mat3x3& Phantom::maths::mat3x3::operator=(const mat3x3& mat)
{
	std::memcpy(elements, mat.elements, sizeof(float) * 3 * 3);
	return *this;
}

Phantom::maths::mat3x3 Phantom::maths::mat3x3::Transpose()
{
	return mat3x3(
		elements[0], elements[3], elements[6],
		elements[1], elements[4], elements[7],
		elements[2], elements[5], elements[8]
	);
}

//static float invf3X3(int i, int j, const float matrix[9])
//{
//	int pre_i = ((i == 0) ? 2 : i - 1);
//	int next_i = ((i + 1 == 3) ? 0 : i + 1);
//	int pre_j = ((j == 0) ? 2 : j - 1);
//	int next_j = ((j + 1 == 3) ? 0 : j + 1);
//
//#define e(a, b) matrix[(a)*3 + (b)]
//	float inv =
//		+e(next_i, next_j)*e(pre_i, pre_j)
//		- e(next_i, pre_j)*e(pre_i, next_j);
//
//	return inv;
//#undef e
//}
//
//int Phantom::maths::mat3x3::InverseMatrix()
//{
//	float inv[9];
//	double D = 0;
//
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			inv[j * 3 + i] = invf3X3(i, j, elements);
//		}
//	}
//
//	for (int k = 0; k < 3; k++) {
//		float s = elements[k] * inv[k * 3];
//		D += s;
//	}
//
//	if (D == 0) return 1;
//
//	D = 1.0 / D;
//
//	for (int i = 0; i < 9; i++)
//	{
//		elements[i] = static_cast<float>(inv[i] * D);
//	}
//
//	return 0;
//}

int Phantom::maths::mat3x3::InverseMatrix()
{
	//https://www.wikihow.com/Find-the-Inverse-of-a-3x3-Matrix
	// computes the inverse of a matrix m
	float det = elements[0] * (elements[4] * elements[8] - elements[7] * elements[5]) -
		elements[1] * (elements[3] * elements[8] - elements[5] * elements[6]) +
		elements[2] * (elements[3] * elements[7] - elements[4] * elements[6]);
	if (det == 0) return 1;
	float invdet = 1 / det;

	mat3x3 minv; // inverse of matrix m
	minv.elements[0] = (elements[4] * elements[8] - elements[7] * elements[5]) * invdet;
	minv.elements[1] = (elements[2] * elements[7] - elements[1] * elements[8]) * invdet;
	minv.elements[2] = (elements[1] * elements[5] - elements[2] * elements[4]) * invdet;
	minv.elements[3] = (elements[5] * elements[6] - elements[3] * elements[8]) * invdet;
	minv.elements[4] = (elements[0] * elements[8] - elements[2] * elements[6]) * invdet;
	minv.elements[5] = (elements[3] * elements[2] - elements[0] * elements[5]) * invdet;
	minv.elements[6] = (elements[3] * elements[7] - elements[6] * elements[4]) * invdet;
	minv.elements[7] = (elements[6] * elements[1] - elements[0] * elements[7]) * invdet;
	minv.elements[8] = (elements[0] * elements[4] - elements[3] * elements[1]) * invdet;
	*this = minv;
	return 0;
}

bool Phantom::maths::mat3x3::operator!=(const mat3x3 &other)
{
	for (int i = 0; i < 9; i++)
	{
		if (abs(elements[i] - other.elements[i]) > std::numeric_limits<float>::epsilon())
			return true;
	}
	return false;
}

Phantom::maths::mat3x3 Phantom::maths::mat3x3::operator+(const mat3x3 &other)
{
	mat3x3 result(0);
	for (int i = 0; i < 9; i++)
	{
		result.elements[i] = other.elements[i] + elements[i];
	}
	return result;
}

Phantom::maths::mat3x3 Phantom::maths::mat3x3::operator*(const float factor) const
{
	mat3x3 result(0);
	for (int i = 0; i < 9; i++)
	{
		result.elements[i] = elements[i] * factor;
	}
	return result;
}

Phantom::maths::mat3x3 Phantom::maths::mat3x3::operator*(const mat3x3 &other) const
{
	mat3x3 result(0);
	for (int column = 0; column < 3; column++)
	{
		for (int row = 0; row < 3; row++)  //column * cow 共计计算9个元素
		{
			float sum = 0.0f;
			for (int i = 0; i < 3; i++)
			{
				sum += elements[row +  i*3]   		//左矩阵行向量
					* other.elements[i + column*3];   //右矩阵列向量
			}
			result.elements[column*3  + row ] = sum;
		}
	}
	return result;
}
