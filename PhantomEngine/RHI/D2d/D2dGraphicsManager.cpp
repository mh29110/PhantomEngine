#include <objbase.h>
#include "D2dGraphicsManager.h"
#include "WindowsApplication.h"
#include "utility.hpp"

using namespace Phantom;


namespace Phantom {
    extern IApplication* g_pApp;
}

HRESULT Phantom::D2dGraphicsManager::CreateGraphicsResources()
{
    HRESULT hr = S_OK;

    HWND hWnd = (HWND)reinterpret_cast<WindowsApplication*>(g_pApp)->GetMainWindowHandler();

    if (m_pRenderTarget == nullptr)
    {
        RECT rc;
        GetClientRect(hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left,
                        rc.bottom - rc.top);

        hr = m_pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(hWnd, size),
            &m_pRenderTarget);
    }

    return hr;
}

int  Phantom::D2dGraphicsManager::Initialize()
{
    int result = 0;

    // initialize COM
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) return -1;

    if (FAILED(D2D1CreateFactory(
                    D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory)))
            return -1;

    result = static_cast<int>(CreateGraphicsResources());

    return result;
}

void Phantom::D2dGraphicsManager::Tick()
{
}

void Phantom::D2dGraphicsManager::Finalize()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pFactory);

    CoUninitialize();
}

void Phantom::D2dGraphicsManager::DrawBitmap(const Image image[],  int32_t index)
{
	HRESULT hr;

	// start build GPU draw command
	m_pRenderTarget->BeginDraw();

	D2D1_BITMAP_PROPERTIES props;
	props.pixelFormat.format = DXGI_FORMAT_R8G8B8A8_UNORM;
	props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	props.dpiX = 72.0f;
	props.dpiY = 72.0f;
	SafeRelease(&m_pBitmap);
	hr = m_pRenderTarget->CreateBitmap(D2D1::SizeU(image[index].Width, image[index].Height),
		image[index].data, image[index].pitch, props, &m_pBitmap);

	D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
	D2D1_SIZE_F bmpSize = m_pBitmap->GetSize();

	D2D1_RECT_F source_rect = D2D1::RectF(
		0,
		0,
		bmpSize.width,
		bmpSize.height
	);

	float aspect = bmpSize.width / bmpSize.height;
	float dest_height = rtSize.height;
	float dest_width = rtSize.height * aspect;

	D2D1_RECT_F dest_rect = D2D1::RectF(
		dest_width * index,
		0,
		dest_width * (index + 1),
		dest_height
	);

	m_pRenderTarget->DrawBitmap(m_pBitmap, dest_rect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, source_rect);

	// end GPU draw command building
	m_pRenderTarget->EndDraw();
}


