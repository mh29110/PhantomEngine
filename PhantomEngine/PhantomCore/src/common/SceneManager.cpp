#include "SceneManager.h"
#include <iostream>
using namespace std;
using namespace Phantom;

int Phantom::SceneManager::Initialize()
{
	int result = 0;

	m_pScene = make_shared<Scene>();
	return result;
}

void Phantom::SceneManager::Finalize()
{
	cout << "Finalize" << endl;
}

void Phantom::SceneManager::Tick()
{
#ifdef DEBUG
	cout << "Tick" << endl;
#endif
#ifdef _DEBUG
	//cout << "_Tick" << endl;
#endif
}

const Scene & SceneManager::GetSceneForRendering()
{
	return *m_pScene;
}
