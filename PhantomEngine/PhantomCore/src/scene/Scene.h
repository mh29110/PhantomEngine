#pragma once 
#include "SceneBaseNode.h"
#include "SceneObjectMesh.h"
#include "SceneGeometryNode.h"
#include "SceneObjectGeometry.h"
#include "camera.h"
namespace Phantom{

class Scene
{
public:
	Scene(const char* name) ;
	Scene() = delete;
	virtual ~Scene();
	std::shared_ptr<SceneBaseNode> SceneGraph;
	std::unordered_multimap<std::string, std::weak_ptr<SceneGeometryNode>>      GeometryNodes;
	std::unordered_map<std::string, std::shared_ptr<SceneObjectGeometry>>       Geometries;
	std::shared_ptr<CameraNode>  camera;
protected:
};

}