#pragma once
#include "IInterface.h"
#include "graphics/Image.h"
#include "common/buffer.h"

namespace Phantom {
	IInterface ImageParser
    {
    public:
        virtual ~ImageParser() = default;
        virtual Image Parse(Buffer& buf) = 0;
    };
}
