#include "GraphicsManager.h"
#include <iostream>
#include "InputManager.h"
#include "SceneManager.h"
using namespace std;
using namespace Phantom::maths;
float PI = 3.1415926f;

int Phantom::GraphicsManager::Init()
{
	Inited = true;
	return 0;
}

void Phantom::GraphicsManager::Shutdown()
{
}

void Phantom::GraphicsManager::Tick()
{
	UpdateConstants();
	Draw();
	
}
void Phantom::GraphicsManager::CalculateCameraMatrix() {
	shared_ptr<CameraNode> camera = g_pSceneManager->GetSceneForRendering().camera;
	camera->CalculateVPMatrix();
}

void Phantom::GraphicsManager::UpdateConstants() {
	bindCommonShader();

	for (auto& pDbc : m_Frame.batchContexts)
	{
		pDbc->modelMatrix = *pDbc->node->GetCalculatedTransform();
	}
	//计算世界坐标转换矩阵
	//#todo
	CalculateCameraMatrix();


	SetPerFrameConstants(m_Frame.frameContext);
	SetPerFrameLight(m_Frame.light);
	SetPerBatchConstants(m_Frame.batchContexts);
}
