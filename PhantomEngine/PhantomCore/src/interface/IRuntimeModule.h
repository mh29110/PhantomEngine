#pragma once

#include "IInterface.h"

namespace Phantom {
	IInterface IRuntimeModule{
	public:
		virtual ~IRuntimeModule() {};

		virtual int Init() = 0;
		virtual void Shutdown() = 0;

		virtual void Tick() = 0;
	};

}
