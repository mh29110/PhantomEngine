#pragma once 
#include "BaseSceneObject.h"
namespace Phantom {
	class SceneObjectVertexArray :BaseSceneObject
	{
	public:
		SceneObjectVertexArray();
		~SceneObjectVertexArray();

	public:
		const void* m_pData;
		const size_t     m_szData = 0;
	};


}
