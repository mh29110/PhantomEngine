#include "vector.h"

namespace Phantom {
	namespace maths {
		vec2::vec2()
		{
			x = 0.0f;
			y = 0.0f;
		}
		vec2::vec2(const float & $x, const float & $y) :x($x), y($y)
		{
			
		}
		vec2 & vec2::add(const vec2 & other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		vec2 & vec2::subtract(const vec2 & other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		float  vec2::multiply(const vec2 & other)
		{
			return x* other.x + y* other.y;
		}
		
		bool vec2::operator==(const vec2 & other)
		{
			return x == other.x && y == other.y;
		}
		bool vec2::operator!=(const vec2 & other)
		{
			return !(*this == other);
		}
		vec2 & vec2::operator+=(const vec2 & other)
		{
			return add(other);
		}
		vec2 & vec2::operator-=(const vec2 & other)
		{
			return subtract(other);
		}
		float vec2::operator*=(const vec2 & other)
		{
			return multiply(other);
		}

	

		float vec2::getAngle(const vec2 & other)
		{
			float dotsum = this->multiply(other);
			float thisMag = sqrt(x*x + y * y);
			float otherMag = sqrt(other.x*other.x + other.y*other.y);
			float cosValue = dotsum / (thisMag*otherMag);
			return  toDegrees(acos(cosValue));
		}
		
		vec2 operator+(const vec2 & left, const vec2 & right)
		{
			return vec2(left.x + right.x, left.y + right.y);
		}
		vec2 operator-(const vec2 & left, const vec2 & right)
		{
			return vec2(left.x - right.x , left.y - right.y);
		}
		float operator*(const vec2 & left, const vec2 & right)
		{
			return left.x*right.x + left.y*right.y;
		}
		
		std::ostream & operator<<(std::ostream & stream, const vec2 & vector)
		{
			stream << "vec2: (" << vector.x << ", " << vector.y << ")";
			return stream;
		}
		//-------------vector 3--------------
		vec3::vec3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		vec3::vec3(const float & $x, const float & $y, const float& $z) :x($x), y($y), z($z)
		{

		}
		vec3 & vec3::add(const vec3 & other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		vec3 & vec3::subtract(const vec3 & other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		float vec3::multiply(const vec3 & other)
		{
			return x * other.x + y*other.y + z * other.z;
		}

		vec3 vec3::crossProduct(const vec3 & other) const
		{
			return vec3( y* other.z -z*other.y , z*other.x - x* other.z, x*other.y - y*other.x);
		}

		vec3 & vec3::normalize()
		{
			float length = x * x + y * y + z * z;
			if (length == 0) // this check isn't an optimization but prevents getting NAN in the sqrt.
				return *this;
			length = 1.0f / sqrt(length);

			x *= length;
			y *= length;
			z *= length;
			return *this;
		}

		bool vec3::operator==(const vec3 & other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool vec3::operator!=(const vec3 & other)
		{
			return !(*this == other);
		}
		vec3 & vec3::operator+=(const vec3 & other)
		{
			return add(other);
		}
		vec3 & vec3::operator-=(const vec3 & other)
		{
			return subtract(other);
		}
		float vec3::operator*=(const vec3 & other)
		{
			return multiply(other);
		}

		vec3  vec3::operator*(const float & velocity)
		{
			return vec3(x*velocity, y*velocity, z*velocity);
		}

		vec3 operator+(const vec3 & left, const vec3 & right)
		{
			return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
		}
		vec3 operator-(const vec3 & left, const vec3 & right)
		{
			return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
		}
		float operator*(const vec3 & left, const vec3 & right)
		{
			return left.x*right.x + left.y*right.y + left.z * right.z;
		}


		vec3 vec3::operator-(const vec3 & right)
		{
			return vec3(right.x * -1, right.y *-1, right.z * -1);
		}

		std::ostream & operator<<(std::ostream & stream, const vec3 & vector)
		{
			stream << "vec3: (" << vector.x << ", " << vector.y << "," << vector.z << ")";
			return stream;
		}


		//-----vector 4 ---------------
		vec4::vec4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}
		vec4::vec4(const float & $x, const float & $y, const float& $z, const float & $w) :x($x), y($y), z($z), w($w)
		{

		}
		vec4 & vec4::add(const vec4 & other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		vec4 & vec4::subtract(const vec4 & other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}
		float vec4::multiply(const vec4 & other)
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		bool vec4::operator==(const vec4 & other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}
		bool vec4::operator!=(const vec4 & other)
		{
			return !(*this == other);
		}
		vec4 & vec4::operator+=(const vec4 & other)
		{
			return add(other);
		}
		vec4 & vec4::operator-=(const vec4 & other)
		{
			return subtract(other);
		}
		float  vec4::operator*=(const vec4 & other)
		{
			return multiply(other);
		}
		vec4 operator+(const vec4 & left, const vec4 & right)
		{
			return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
		}
		vec4 operator-(const vec4 & left, const vec4 & right)
		{
			return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
		}
		float operator*(const vec4 & left, const vec4 & right)
		{
			return left.x*right.x + left.y*right.y + left.z * right.z + left.w *right.w;
		}

		std::ostream & operator<<(std::ostream & stream, const vec4 & vector)
		{
			stream << "vec4: (" << vector.x << ", " << vector.y << "," << vector.z << "," << vector.w << ")";
			return stream;
		}
	}
}
