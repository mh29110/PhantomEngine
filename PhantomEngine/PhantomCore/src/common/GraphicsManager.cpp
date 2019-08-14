#include "GraphicsManager.h"
#include <iostream>
#include "InputManager.h"
#include "SceneManager.h"
#include "interface/IApplication.h"
#include "GfxConfiguration.h"
#include "eventQueue/EventManager.h"


using namespace std;
using namespace Phantom::maths;

float PI = 3.1415926f;
#ifdef OS_WINDOWS
const char*  FONT_PATH = "C:\\windows\\Fonts\\arial.TTF";
#endif
#ifdef OS_MACOS
const char*  FONT_PATH = "/System/Library/Fonts/Symbol.ttf";
#endif


int Phantom::GraphicsManager::Init()
{
	Inited = true;
	fontEngine.LoadFontFace(FONT_PATH);
	
	evthandler = new EventQueue::ClassBasedEventHandler<GraphicsManager>(this,&GraphicsManager::OnLoadSceneCompleted);
	EventQueue::EventManager::Instance().AddEventHandler(EventQueue::EventId::EVT_LOADSCENE_COMPLETED, evthandler);
	return 0;
}

void Phantom::GraphicsManager::Shutdown()
{
	EventQueue::EventManager::Instance().RemoveEventHandler(EventQueue::EventId::EVT_LOADSCENE_COMPLETED, evthandler);
	delete evthandler;
	evthandler = nullptr;
	printf("shut down");
}

void Phantom::GraphicsManager::Tick()
{
	UpdateConstants();
	Draw();
	DrawGUI();
}


void Phantom::GraphicsManager::DrawString(GUI::GUIIndex idx, float posx, float posy, std::string content)
{
	GUI::GuiDisplayUnit unit = {
		posx,posy,content
	};
	m_GuiUnitMap[idx] = unit;
}

namespace Phantom {
	extern IApplication* g_pApp;
	void GraphicsManager::EnterScene(const Scene & scene)
	{
#ifdef _DEBUG
		printf("dd");
#endif
	}
	void GraphicsManager::PurgeCurScene()
	{
		m_Frame.batchContexts.clear();
	}
	//wtf !  namespace 
	void GraphicsManager::CalculateCameraMatrix() {
		const GfxConfiguration& conf = g_pApp->GetConfiguration();
		float aspect = (float)conf.screenWidth / (conf.screenHeight?conf.screenHeight:1);

		shared_ptr<CameraNode> camera = g_pSceneManager->GetSceneForRendering().camera;

		camera->CalculateVPMatrix(aspect);
		m_Frame.frameContext.viewMatrix = camera->m_viewMatrix;
		m_Frame.frameContext.projectionMatrix = camera->m_projectionMatrix;

	}
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
		mat4x4 viewMat;
		mat4x4 projectionMat;
#pragma region test_light_move
		float tempX = cos(factor);
		float tempY = sin(factor);
		factor += 0.003f;

		light.lightPos = vec4(0.0f, 0.0f, 0.0f, 1.0f);//µ±Ç°Æ½ÐÐ¹âÏÂÃ»ÓÐÓÃµ½
		light.lightDir = vec4(tempX, -1.0f, 0.0f, 0.0f);
		light.lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
#pragma endregion
#pragma region LightObject
		shared_ptr<SceneObjectLight> pLightObj = scene.GetLight(pLightNode->GetSceneObjectRef());
		
		float nearClipDistance = 1.0f;
		float farClipDistance = 10000.0f;

		if (pLightObj) {
			//light.lightColor;
		
			if (true) /*pLightObj type ==  kSceneObjectTypeLightInfi*///todo 先写平行光
			{
				float sm_half_dist = min(farClipDistance / 4.0f, 500.0f);
				projectionMat.orthographic(-sm_half_dist, sm_half_dist,
					-sm_half_dist, sm_half_dist,
					nearClipDistance, farClipDistance);
				viewMat.LookAtMatrixBuild(vec3(0.0f, 0.0f, 0.0f),
										vec3(tempX, -1.0f, 0.0f),
										vec3(0.0f, 0.0f, 1.0f));


				auto pCameraNode = scene.camera;
				light.lightPos.w = 0.0f;
			}
		}
#pragma endregion

		light.lightVP = projectionMat * viewMat;

		m_Frame.light = light;

		if (pLightNode)//只要第一个光
		{
			break;
		}
	}
}

void Phantom::GraphicsManager::CalculateSkeletonSkin()
{
	auto scene = g_pSceneManager->GetSceneForRendering();

	auto sceneBoneNodes = scene.BoneNodes;

	std::unordered_map<Guid, std::weak_ptr<SceneObjectGeometry>>      skeletonAnimationObjects = scene.SkeletonAnimationObjects;
	for (auto skeAnimObj : skeletonAnimationObjects)
	{
		shared_ptr<SceneObjectGeometry> pGeometry = skeAnimObj.second.lock();
		const auto& pMesh = pGeometry->GetMesh().lock();

		const auto pSkin = pMesh->GetSkin().lock();
		const auto skeleton = pSkin->GetSkeleton().lock();
		//bone ref arr
		const auto vBoneRefArr = skeleton->GetBoneRefArr().lock()->GetBoneNodeRefArr();
		//bindpose transforms array.
		auto binePoseTransform = skeleton->getTransform().lock();
		const std::vector< maths::mat4x4 >& bindPoseMatAll = binePoseTransform->GetMatrixAll();

		const int boneArrLen = vBoneRefArr.size();
		for (int i = 0; i < boneArrLen; i++)
		{
			auto boneRef = vBoneRefArr[i];
			const std::string &boneName = boneRef->GetName();
			auto boneNode = sceneBoneNodes.find(boneName)->second.lock();
			auto runtimeMat = boneNode->GetCalculatedTransform();

			mat4x4 bpMat = bindPoseMatAll[i];
			bpMat.InverseMatrix4X4f();

			*(boneNode->m_RuntimeWithBindPoseMat) =  (*runtimeMat) * bpMat;
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
	CalculateSkeletonSkin();

	SetPerFrameConstants(m_Frame.frameContext);
	SetPerFrameLight();
	SetPerBatchConstants(m_Frame.batchContexts);
}

int Phantom::GraphicsManager::OnLoadSceneCompleted(EventQueue::Event * evt)
{
	PurgeCurScene();
	auto scene = g_pSceneManager->GetSceneForRendering();
	EnterScene(scene);
	return 0;
}
