#pragma once
#include "Metal/Metal2GraphicsManager.h"

namespace Phantom {
    GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new Metal2GraphicsManager);
}
