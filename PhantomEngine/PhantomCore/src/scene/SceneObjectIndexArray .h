#pragma once 
#include "BaseSceneObject.h"
namespace Phantom{
class SceneObjectIndexArray :BaseSceneObject
{
public:
	SceneObjectIndexArray();
	~SceneObjectIndexArray();

public:
	const void* m_pData;
	const size_t     m_szData = 0;
};
}