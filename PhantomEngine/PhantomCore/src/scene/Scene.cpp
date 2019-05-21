#include "Scene.h"
#include "SceneObjectVertexArray.h"
#include "SceneOjbectTypeDef.h"
#include "SceneBaseNode.h"
#include "BehaviourManager.h"

using namespace Phantom;
using namespace std;


Phantom::Scene::Scene(const char * name):SceneRootGraph(new SceneBaseNode(name))
{
	camera = make_shared<CameraNode>();
	m_pDefaultMat = std::make_shared<SceneObjectMaterial>("default");
}

Phantom::Scene::~Scene()
{
}

const shared_ptr<SceneObjectMaterial> Scene::GetFirstMaterial() const
{
	return (Materials.empty() ? nullptr : Materials.cbegin()->second);
}

//找不到就用默认材质。
const std::shared_ptr<SceneObjectMaterial> Phantom::Scene::GetMaterial(const std::string & matName) const
{
	unordered_map<string, shared_ptr<SceneObjectMaterial>> ::const_iterator  iter = Materials.find(matName);
	if (iter != Materials.end())
	{
		return iter->second;
	}
	else
	{
		return m_pDefaultMat;
	}
}

const std::shared_ptr<Phantom::SceneObjectLight> Phantom::Scene::GetLight(const std::string & lightName) const
{
	auto light = Lights.find(lightName);
	if (light != Lights.end())
	{
		return light->second;
	}
	return nullptr;
}

void Phantom::Scene::LoadTextures(void)
{
	for (auto mat : Materials)
	{
		if (auto ptr = mat.second)
		{
			ptr->LoadTextures();
		}
	}
}
