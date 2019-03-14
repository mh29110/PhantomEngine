#pragma once 
#include "SceneBaseObject.h"
#include "SceneObjectMesh.h"
namespace Phantom{

class Scene
{
public:
	Scene() ;
	SceneObjectMesh*  m_pMesh;
protected:
};

}