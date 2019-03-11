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
#ifdef DEBUG
	cout << "Tick" << endl;
#endif
#ifdef _DEBUG
	//cout << "_Tick" << endl;
#endif
}

void Phantom::GraphicsManager::DrawSingleMesh()
{
	cout << "DrawSingleMesh" << endl;
}
