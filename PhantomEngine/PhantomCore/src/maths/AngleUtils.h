#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
namespace Phantom {
	namespace maths {

		inline float toRadians(float degrees)
		{
			return float(degrees * (M_PI / 180.0f));
		}

		inline float toDegrees(float radians)
		{
			return float(radians * (180.f / M_PI));
		}

	}
}