#pragma once
#include <d2d1.h>
#include "common/GraphicsManager.h"
#include "graphics/Image.h"

namespace Phantom {
    class D2dGraphicsManager : public GraphicsManager
    {
    public:
        virtual int Init();
        virtual void Shutdown();

        virtual void Tick();

    protected:
        HRESULT CreateGraphicsResources();
    protected:
        ID2D1Factory            *m_pFactory = nullptr;
        ID2D1HwndRenderTarget   *m_pRenderTarget = nullptr;
    };
}

