#include "BehaviourManager.h"
#include "SceneManager.h"
#include "InputManager.h"

int Phantom::BehaviourManager::Initialize()
{
	camera = g_pSceneManager->GetSceneForRendering().camera;
	return 0;
}

void Phantom::BehaviourManager::Finalize()
{
}

void Phantom::BehaviourManager::Tick()
{
	if (g_pInputManager->GetUpKeyPressed()) {
		camera.lock()->m_positionZ += 0.001f;
	}
	if (g_pInputManager->GetDownKeyPressed()) {
		camera.lock()->m_positionZ -= 0.001f;
	}
	if (g_pInputManager->GetLeftKKeyPressed()) {
		camera.lock()->m_positionX -= 0.01f;
	}
	if (g_pInputManager->GetRightKeyPressed()) {
		camera.lock()->m_positionX += 0.01f;
	}
}
