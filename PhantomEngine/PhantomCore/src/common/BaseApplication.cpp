#include "BaseApplication.h"
#include <iostream>

using namespace Phantom;

bool Phantom::BaseApplication::m_bQuit = false;

Phantom::BaseApplication::BaseApplication(GfxConfiguration& cfg)
    :m_Config(cfg)
{
}

// Parse command line, read configuration, initialize all sub modules
int Phantom::BaseApplication::Init()
{
    int result = 0;

    std::wcout << m_Config;

	return result;
}


// Shutdown all sub modules and clean up all runtime temporary files.
void Phantom::BaseApplication::Shutdown()
{
	m_bQuit = true;
}


// One cycle of the main loop
void Phantom::BaseApplication::Tick()
{
}

bool Phantom::BaseApplication::IsQuit()
{
	return m_bQuit;
}