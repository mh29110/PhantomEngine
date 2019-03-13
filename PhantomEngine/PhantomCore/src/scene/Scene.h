#pragma once 
#include "BaseSceneObject.h"
#include "SceneObjectVertexArray.h"
#include "SceneObjectIndexArray .h"
namespace Phantom{

class Scene
{
public:
	Scene() ;
	SceneObjectIndexArray*  m_pIndexArray;
	SceneObjectVertexArray* m_pVertexArray;
protected:
};

}