#include "GraphicsManager.h"
#include <iostream>
using namespace std;


int Phantom::GraphicsManager::Initialize()
{
	cout << "Initialize" << endl;
	return 0;
}

void Phantom::GraphicsManager::Finalize()
{
	cout << "Finalize" << endl;
}

void Phantom::GraphicsManager::Tick()
{
#ifdef OS_MACOS
	cout << "Tick" << endl;
#endif
}

void Phantom::GraphicsManager::DrawSingleMesh()
{
	cout << "DrawSingleMesh" << endl;
}
