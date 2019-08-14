#include <iostream>
#include "DebugManager.h"
#include "GraphicsManager.h"
#include "maths/PhMaths.h"

using namespace Phantom;
using namespace std;
using namespace Phantom::maths;

#ifdef _DEBUG
int DebugManager::Init()
{
	DrawDebugInfo();//todo for test
    return 0;
}

void DebugManager::Shutdown()
{

}

void DebugManager::Tick()
{
#ifdef _DEBUG

#endif
}

void DebugManager::ToggleDebugInfo()
{
    m_bDrawDebugInfo = !m_bDrawDebugInfo;
	DrawDebugInfo();
}

void DebugManager::DrawDebugInfo()
{
//    DrawGrid();
    DrawAxis();
}

void DebugManager::DrawAxis()
{
    // x - axis
    vec3 from ({-10000.0f, 0.0f, 0.0f});
    vec3 to ({10000.0f, 0.0f, .0f});
    vec3 color({1.0f, 1.0f, 0.0f});
    g_pGraphicsManager->DrawLine(from, to, color);

    // y - axis
    from.SetComponents(0.0f, -10000.0f, 0.0f);
    to.SetComponents(0.0f, 10000.0f, 0.0f);
    color.SetComponents(0.0f, 1.0f, 0.0f);
    g_pGraphicsManager->DrawLine(from, to, color);

    // z - axis
    from.SetComponents(0.0f, 0.0f, -10000.0f);
    to.SetComponents(0.0f, 0.0f, 10000.0f);
    color.SetComponents(0.0f, 0.0f, 1.0f);
    g_pGraphicsManager->DrawLine(from, to, color);
}

#endif
