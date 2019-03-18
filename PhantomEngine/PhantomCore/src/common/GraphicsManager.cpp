#include "GraphicsManager.h"
#include <iostream>
#include "InputManager.h"
#include "SceneManager.h"
using namespace std;
using namespace Phantom::maths;
float PI = 3.1415926f;

int Phantom::GraphicsManager::Initialize()
{
	Inited = true;
	return 0;
}

void Phantom::GraphicsManager::Finalize()
{
}

void Phantom::GraphicsManager::Tick()
{
	UpdateConstants();
	Draw();
}
void Phantom::GraphicsManager::CalculateCameraMatrix() {
	shared_ptr<CameraNode> camera = g_pSceneManager->GetSceneForRendering().camera;
	// Set the field of view and screen aspect ratio.
	//float fieldOfView = PI / 4.0f;
	/*GfxConfiguration& conf = g_pApp->GetConfiguration();

	float screenAspect = (float)conf.screenWidth / (float)conf.screenHeight;*/
	//在场景中应该有一个摄像机node，携带下列参数并被游戏逻辑驱动数据。
	//m_projectionMatrix.orthographic(-5.0f, 5.0f, -5.0f, 5.0f, 0.01f, 1000.0f);
	camera->m_projectionMatrix.perspective(90.0f, 16.0f/9.0f, 0.01f, 1000.0f);
	//摄像机位置；  LookAt位置， Up方向  
	camera->m_viewMatrix.LookAtMatrixBuild(vec3(camera->m_positionX, 0, camera->m_positionZ),
									vec3(0, 0, 0),
									vec3(0, 0, 1));
}

void Phantom::GraphicsManager::UpdateConstants() {
	bindShader();

	auto& frame = m_Frame;

	for (auto& pDbc : frame.batchContexts)
	{
		pDbc->modelMatrix = *pDbc->node->GetCalculatedTransform();
	}
	//计算世界坐标转换矩阵
	//#todo
	CalculateCameraMatrix();

	SetPerFrameConstants(frame.frameContext);
	SetPerBatchConstants(frame.batchContexts);
}
