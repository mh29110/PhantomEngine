#include "vec2.h"
#include <math.h>

namespace phantom {
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
			return  acos(cosValue)*180/3.1415926;
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
	}
}