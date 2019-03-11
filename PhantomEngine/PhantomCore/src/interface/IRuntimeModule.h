#pragma once

#include "IInterface.h"

namespace Phantom {
	IInterface IRuntimeModule{
	public:
		virtual ~IRuntimeModule() {};

		virtual int Initialize() = 0;
		virtual void Finalize() = 0;

		virtual void Tick() = 0;
	};

}
