#include "mat4.h"

namespace Phantom {namespace maths {

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
	mat4x4::mat4x4()
	{
		for (int i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}

		for (int i = 0; i < 4; i++)
		{
			elements[i + i * 4] = 1.0f;
		}
	}

	mat4x4::mat4x4(float m00, float m01, float m02, float m03, // 1st column
			float m04, float m05, float m06, float m07, // 2nd column
			float m08, float m09, float m10, float m11, // 3rd column
			float m12, float m13, float m14, float m15)// 4th column
	{
		elements[0] = m00;
		elements[1] = m01;
		elements[2] = m02;
		elements[3] = m03;
		elements[4] = m04;
		elements[5] = m05;
		elements[6] = m06;
		elements[7] = m07;
		elements[8] = m08;
		elements[9] = m09;
		elements[10] = m10;
		elements[11] = m11;
		elements[12] = m12;
		elements[13] = m13;
		elements[14] = m14;
		elements[15] = m15;
	}

	mat4x4 mat4x4::operator * (const mat4x4 &other)
	{
		mat4x4 result(0);
		for (int column = 0 ; column < 4 ; column++)
		{
			for (int row = 0; row < 4 ; row++)  //column * cow 共计计算16个元素
			{
				float sum = 0.0f;
				for (int i = 0;i < 4 ; i++ )
				{
					sum += elements[ row + 4 * i]   		//左矩阵行向量
						* other.elements[ i + column * 4];   //右矩阵列向量
				}
				result.elements[ column*4 + row] = sum;
			}
		}
		return result;
	}
	// -------------translate -------------
	mat4x4 mat4x4::translation(const vec3& translation)
	{
		mat4x4 result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}


	

	///////////////////////////////////////////////////////////////////////////////
	// rotate 
	///////////////////////////////////////////////////////////////////////////////
	mat4x4 mat4x4::rotation(float angle, const vec3& axis)
	{
		mat4x4 result(1.0f);

		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[1 + 0 * 4] = y * x * omc + z * s;
		result.elements[2 + 0 * 4] = x * z * omc - y * s;

		result.elements[0 + 1 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[2 + 1 * 4] = y * z * omc + x * s;

		result.elements[0 + 2 * 4] = x * z * omc + y * s;
		result.elements[1 + 2 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;

		return result;
	}

	mat4x4 mat4x4::scale(const vec3& scale)
	{
		mat4x4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

	mat4x4 mat4x4::identity()
	{
		return mat4x4(1.0f);
	}




	std::ostream & operator <<(std::ostream &os, const mat4x4 & m)
	{

		os << "mat4x4: (" << m.elements[0] << ", " << m.elements[4] << ","<< m.elements[8] << "," << m.elements[12]<< ")"<< std::endl
		   <<  "        (" << m.elements[1] << ", " << m.elements[5] << ","<< m.elements[9] << "," << m.elements[13]<< ")"<< std::endl
		   <<  "        (" << m.elements[2] << ", " << m.elements[6] << ","<< m.elements[10] << "," << m.elements[14]<< ")"<< std::endl
		   <<  "        (" << m.elements[3] << ", " << m.elements[7] << ","<< m.elements[11] << "," << m.elements[15]<< ")"<< std::endl;
		return os;
	}


	//project
	mat4x4 mat4x4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		elements[0 + 0 * 4] = 2.0f / (right - left);

		elements[1 + 1 * 4] = 2.0f / (top - bottom);

		elements[2 + 2 * 4] = 2.0f / (near - far);

		elements[0 + 3 * 4] = (left + right) / (left - right);
		elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		elements[2 + 3 * 4] = (far + near) / (near - far); //openGL 是near - far

		return *this;
	}

	mat4x4 mat4x4::perspective(float fov, float aspectRatio, float near, float far)
	{
		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (far - near);
		float c = (2.0f * near * far) / (near - far);

		elements[0 + 0 * 4] = a;
		elements[1 + 1 * 4] = q;
		elements[2 + 2 * 4] = b;
		elements[3 + 2 * 4] = -1.0f;
		elements[2 + 3 * 4] = c;

		return *this;
	}
	mat4x4 mat4x4::LookAtMatrixBuild(const vec3& pos, const vec3& focal, const vec3 & up) 
	{
		vec3 zaxis = pos - focal;//相机朝向
		zaxis.normalize();

		vec3 xaxis = (vec3)up.crossProduct(zaxis);
		xaxis.normalize();

		vec3 yaxis = zaxis.crossProduct(xaxis); //因为up大概率不与相机朝向垂直 
		//yaxis.normalize();  //没必要

		//逆矩阵 == 转置矩阵 so  设置行向量
		elements[0] = xaxis.x;
		elements[1] = yaxis.x;
		elements[2] = zaxis.x;
		elements[3] = 0;

		elements[4] = xaxis.y;
		elements[5] = yaxis.y;
		elements[6] = zaxis.y;
		elements[7] = 0;

		elements[8] = xaxis.z;
		elements[9] = yaxis.z;
		elements[10] = zaxis.z;
		elements[11] = 0;

		elements[12] = -(xaxis * pos);
		elements[13] = -(yaxis * pos);
		elements[14] = -(zaxis * pos);
		elements[15] = 1;
		return *this;

	}
}}
