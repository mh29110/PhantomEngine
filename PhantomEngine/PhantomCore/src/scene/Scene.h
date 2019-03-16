#pragma once 
#include "SceneBaseObject.h"
#include "SceneObjectMesh.h"
#include "camera.h"
namespace Phantom{

class Scene
{
public:
	Scene() ;
	virtual ~Scene();
	std::shared_ptr<CameraNode>  camera;
protected:
};

}