#pragma once 
#include <unordered_map>
#include "SceneBaseNode.h"
#include "SceneObjectMesh.h"
#include "SceneObjectLight.h"
#include "SceneGeometryNode.h"
#include "SceneLightNode.h"
#include "SceneObjectGeometry.h"
#include "SceneObjectMaterial.h"
#include "camera.h"
namespace Phantom{

class Scene
{
public:
	Scene(const char* name) ;
	Scene() = delete;
	virtual ~Scene();
	std::shared_ptr<SceneBaseNode> SceneRootGraph;
	
	//所有Object在这里存储，等待被关联使用
	std::unordered_map<std::string, std::shared_ptr<SceneObjectGeometry>>       GeometryOjbects;
	std::unordered_map<std::string, std::shared_ptr<SceneObjectMaterial>>       Materials;
	std::unordered_map<std::string, std::shared_ptr<SceneObjectLight>>         Lights;
	
	//所有Node强关联Scene的Node树，所以weak_ptr
	std::unordered_multimap<std::string, std::weak_ptr<SceneGeometryNode>>      GeometryNodes;
	std::unordered_map<std::string, std::weak_ptr<SceneLightNode>>              LightNodes;

	//camera临时用
	std::shared_ptr<CameraNode>  camera;


public:
	const std::shared_ptr<SceneObjectMaterial> GetFirstMaterial() const;
	void LoadTextures(void);
protected:
};

}
