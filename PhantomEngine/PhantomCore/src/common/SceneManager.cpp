#include "SceneManager.h"
#include <iostream>
#include <string>
#include "AssetLoadManager.h"
#include "parser/opengexparser.h"
#include "eventQueue/EventManager.h"
#include "AnimationManager.h"
using namespace std;
using namespace Phantom;

int Phantom::SceneManager::Init()
{
	int result = 0;
	m_pScene = make_shared<Scene>("init scene");
	return result;
}

void Phantom::SceneManager::Shutdown()
{
	cout << "Shutdown" << endl;
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

bool Phantom::SceneManager::LoadScene(const std::string&  sceneName)
{
	if (m_pScene->Name == sceneName)
	{
		return false;
	}
	string ogex_text = g_pAssetLoader->SyncOpenAndReadTextFileToString(sceneName.c_str());
	if (ogex_text.empty()) {
		return false;
	}
	OpengexParser paser;
	m_pScene = paser.Parse( ogex_text);
	m_pScene->Name = sceneName;
	m_pScene->camera->initViewMatrix();
	if (!m_pScene) {
		return false;
	}
	m_pScene->LoadTextures();

	AnimationManager::GetInstance().AttachCurScene();

	EventQueue::Event evt(EventQueue::EventId::EVT_LOADSCENE_COMPLETED);
	EventQueue::EventManager::Instance().DispatchEvent(&evt);
	return true;
}

void Phantom::SceneManager::SwitchScene(const std::string&  sceneName)
{
	LoadScene( sceneName);
}
