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
		mat4x4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	mat4x4 mat4x4::perspective(float fov, float aspectRatio, float near, float far)
	{
		mat4x4 result(1.0f);

		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}



	///////////////////////////////////////////////////////////////////////////////
	// translate this matrix by (x, y, z)  有点晕 # todo
	///////////////////////////////////////////////////////////////////////////////
	mat4x4& mat4x4::translate(const vec3 & v)
	{
	    return translate(v.x, v.y, v.z);
	}

	mat4x4& mat4x4::translate(float x, float y, float z)
	{
	    elements[0] += elements[3] * x;   elements[4] += elements[7] * x;   
	    elements[8] += elements[11]* x;   elements[12]+= elements[15]* x;

	    elements[1] += elements[3] * y;   elements[5] += elements[7] * y;   
	    elements[9] += elements[11]* y;   elements[13]+= elements[15]* y;

	    elements[2] += elements[3] * z;   elements[6] += elements[7] * z;   
	    elements[10]+= elements[11]* z;   elements[14]+= elements[15]* z;

	    return *this;
	}

	
	mat4x4& mat4x4::scale(float x, float y, float z)
	{
	    elements[0] *= x;   elements[4] *= x;   elements[8] *= x;   elements[12] *= x;
	    elements[1] *= y;   elements[5] *= y;   elements[9] *= y;   elements[13] *= y;
	    elements[2] *= z;   elements[6] *= z;   elements[10]*= z;   elements[14] *= z;
	    return *this;
	}

}}
