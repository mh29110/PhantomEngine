#pragma once
#include "Ability.h"

namespace Phantom {
	template <typename T>
	class IAnimatable
	{
	public:
		virtual ~IAnimatable() = default;
		typedef const T ParamType;
		virtual void Update(ParamType param) = 0;
	};
}