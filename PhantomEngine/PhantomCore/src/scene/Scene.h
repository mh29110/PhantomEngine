#pragma once 
#include <unordered_map>
#include "SceneBaseNode.h"
#include "SceneObjectMesh.h"
#include "SceneGeometryNode.h"
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
	std::unordered_multimap<std::string, std::weak_ptr<SceneGeometryNode>>      GeometryNodes;
	std::unordered_map<std::string, std::shared_ptr<SceneObjectGeometry>>       GeometryOjbects;
	std::unordered_map<std::string, std::shared_ptr<SceneObjectMaterial>>       Materials;
	std::shared_ptr<CameraNode>  camera;

public:
	const std::shared_ptr<SceneObjectMaterial> GetFirstMaterial() const;
	void LoadTextures(void);
	const std::shared_ptr<SceneObjectMaterial> GetMaterial(const std::string& key) const;
protected:

private:
	std::shared_ptr<SceneObjectMaterial> m_pDefaultMaterial;
};

}
