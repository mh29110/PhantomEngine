#include "Scene.h"
#include "SceneObjectVertexArray.h"
#include "SceneOjbectTypeDef.h"
#include "SceneBaseNode.h"
#include "OpengexParser.h"
#include "BehaviourManager.h"

using namespace Phantom;
using namespace std;


Phantom::Scene::Scene(const char * name):SceneRootGraph(new SceneBaseNode(name))
{
	//camera = make_shared<CameraNode>();
	m_pDefaultMaterial = std::make_shared<SceneObjectMaterial>("default");
}

Phantom::Scene::~Scene()
{
}

const shared_ptr<SceneObjectMaterial> Scene::GetFirstMaterial() const
{
	return (Materials.empty() ? nullptr : Materials.cbegin()->second);
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

const shared_ptr<SceneObjectMaterial> Phantom::Scene::GetMaterial(const std::string& key) const
{
	auto i = Materials.find(key);
	if (i == Materials.end())
		return m_pDefaultMaterial;
	else
	{
		return i->second;
	}
}