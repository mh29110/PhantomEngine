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
	float factor = 1.0f;
	//todo remove to a reAttachCamera function when scene camera change.
	camera = g_pSceneManager->GetSceneForRendering().camera;

	if (g_pInputManager->GetUpKeyPressed()) {
		camera.lock()->ProcessKeyboard(FORWARD, factor);
	}
	if (g_pInputManager->GetDownKeyPressed()) {
		camera.lock()->ProcessKeyboard(BACKWARD, factor);
	}
	if (g_pInputManager->GetLeftKKeyPressed()) {
		camera.lock()->ProcessKeyboard(LEFT, factor);
	}
	if (g_pInputManager->GetRightKeyPressed()) {
		camera.lock()->ProcessKeyboard(RIGHT, factor);
	}
}

void Phantom::BehaviourManager::LeftMouseDrag(int deltaX, int deltaY)
{
	camera = g_pSceneManager->GetSceneForRendering().camera;

	camera.lock()->ProcessMouseMovement(deltaX, deltaY);
	
}
