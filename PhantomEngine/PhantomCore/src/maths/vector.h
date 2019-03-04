#pragma once 
#include <iostream>
#include "vector.h"
#include "utils.h"
namespace phantom {namespace maths {

	struct vec2 {
		float x, y;
		vec2();
		vec2(const float& x,const float& y);
		vec2& add(const vec2 & other);
		vec2& subtract(const vec2 & other);
		float multiply(const vec2 & other);

		friend vec2 operator +(const vec2& left, const vec2&right);
		friend vec2 operator -(const vec2& left, const vec2&right);
		friend float operator *(const vec2& left, const vec2&right);

		bool operator==(const vec2& other);
		bool operator!=(const vec2& other);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		float operator*=(const vec2& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);

		float getAngle(const vec2& other);
	};

	struct vec3 {
		float x, y, z;
		vec3();
		vec3(const float& x, const float& y, const float& z);
		vec3& add(const vec3 & other);
		vec3& subtract(const vec3 & other);
		float multiply(const vec3 & other);

		vec3 crossProduct(const vec3 & other) const;
		vec3& normalize();

		friend vec3 operator +(const vec3& left, const vec3&right);
		friend vec3 operator -(const vec3& left, const vec3&right);
		friend float operator *(const vec3& left, const vec3&right);
		vec3 operator -( const vec3&right);

		bool operator==(const vec3& other);
		bool operator!=(const vec3& other);

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		float operator*=(const vec3& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
	};

	struct vec4 {
		float x, y, z, w;
		vec4();
		vec4(const float& x, const float& y, const float& z, const float& w);
		vec4& add(const vec4 & other);
		vec4& subtract(const vec4 & other);
		float multiply(const vec4 & other);

		friend vec4 operator +(const vec4& left, const vec4&right);
		friend vec4 operator -(const vec4& left, const vec4&right);
		friend float operator *(const vec4& left, const vec4&right);

		bool operator==(const vec4& other);
		bool operator!=(const vec4& other);

		vec4& operator+=(const vec4& other);
		vec4& operator-=(const vec4& other);
		float operator*=(const vec4& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
	};
}}