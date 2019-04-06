#include "BehaviourManager.h"
#include "SceneManager.h"
#include "InputManager.h"

int Phantom::BehaviourManager::Init()
{
	camera = g_pSceneManager->GetSceneForRendering().camera;
	return 0;
}

void Phantom::BehaviourManager::Shutdown()
{
}

void Phantom::BehaviourManager::Tick()
{
	float factor = 100.0f;
	//todo remove to a reAttachCamera function when scene camera change.
	camera = g_pSceneManager->GetSceneForRendering().camera;

	if (g_pInputManager->GetUpKeyPressed()) {
		camera.lock()->m_positionZ += 0.1f*factor;
	}
	if (g_pInputManager->GetDownKeyPressed()) {
		camera.lock()->m_positionZ -= 0.1f*factor;
	}
	if (g_pInputManager->GetLeftKKeyPressed()) {
		camera.lock()->m_positionX -= 0.1f*factor;
	}
	if (g_pInputManager->GetRightKeyPressed()) {
		camera.lock()->m_positionX += 0.1f*factor;
	}
}

void Phantom::BehaviourManager::LeftMouseDrag(int deltaX, int deltaY)
{
	camera = g_pSceneManager->GetSceneForRendering().camera;

	camera.lock()->m_positionY += deltaX*0.001f;
	
}
