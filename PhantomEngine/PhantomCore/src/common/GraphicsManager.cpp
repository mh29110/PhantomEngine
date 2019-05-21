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
	m_Frame.frameContext.viewMatrix = camera->m_viewMatrix;
	m_Frame.frameContext.projectionMatrix = camera->m_projectionMatrix;

}
static float factor = 0.0f;
void Phantom::GraphicsManager::CalculateLights()
{
	auto scene = g_pSceneManager->GetSceneForRendering();
	std::unordered_map<std::string, std::weak_ptr<SceneLightNode>>  lightNodes = scene.LightNodes;
	for (auto lightNode : lightNodes)
	{
		shared_ptr<SceneLightNode> pLightNode = lightNode.second.lock();
		Light light;
		mat4x4 view;
		mat4x4 projection;
#pragma region test_light_move
		float tempX = cos(factor);
		float tempY = sin(factor);
		factor += 0.003f;

		light.lightPos = vec4(0.0f, 200.0f, 0.0f, 0.0f);//µ±Ç°Æ½ÐÐ¹âÏÂÃ»ÓÐÓÃµ½
		light.lightDir = vec4(tempX, tempY, tempY, 0.0f);
		light.lightColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
#pragma endregion
#pragma region LightObject
		shared_ptr<SceneObjectLight> pLightObj = scene.GetLight(pLightNode->GetSceneObjectRef());
		

		if (pLightObj) {
			//light.lightColor;
		
			if (true) /*pLightObj type ==  kSceneObjectTypeLightInfi*///todo 先写平行光
			{
				auto pCameraNode = scene.camera;
			}
		}
#pragma endregion

		light.lightVP = projection * view;
		m_Frame.light = light;

		if (pLightNode)//只要第一个光
		{
			break;
		}
	}
}

void Phantom::GraphicsManager::UpdateConstants() {

	for (auto& pDbc : m_Frame.batchContexts)
	{
		pDbc->modelMatrix = *pDbc->node->GetCalculatedTransform();
	}
	//计算世界坐标转换矩阵
	//#todo
	CalculateCameraMatrix();
	CalculateLights();


	SetPerFrameConstants(m_Frame.frameContext);
	SetPerFrameLight();
	SetPerBatchConstants(m_Frame.batchContexts);
}
