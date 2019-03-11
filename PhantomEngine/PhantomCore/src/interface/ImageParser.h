#pragma once
#include "IInterface.h"
#include "Image.h"
#include "Buffer.h"

namespace Phantom {
	IInterface ImageParser
    {
    public:
        virtual ~ImageParser() = default;
        virtual Image Parse(Buffer& buf) = 0;
    };
}
