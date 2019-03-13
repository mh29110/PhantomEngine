#include "Scene.h"

using namespace Phantom;
const float varr[] = {
		  1.0f,  1.0f,  1.0f ,
		  1.0f,  1.0f, -1.0f ,
		 -1.0f,  1.0f, -1.0f ,
		 -1.0f,  1.0f,  1.0f ,
		  1.0f, -1.0f,  1.0f ,
		  1.0f, -1.0f, -1.0f ,
		 -1.0f, -1.0f, -1.0f ,
		 -1.0f, -1.0f,  1.0f ,
		 //-- color
				/*  1.0f, 0.0f, 0.0f ,
				  0.0f, 1.0f, 0.0f ,
				  0.0f, 0.0f, 1.0f ,
				  1.0f, 1.0f, 0.0f ,
				  1.0f, 0.0f, 1.0f ,
				  0.0f, 1.0f, 1.0f ,
				  0.5f, 1.0f, 0.5f ,
				  1.0f, 0.5f, 1.0f*/
};
Phantom::Scene::Scene()
{
	m_pVertexArray = new SceneObjectVertexArray();
	
	m_pVertexArray->m_pData = (void*)(varr);
}
