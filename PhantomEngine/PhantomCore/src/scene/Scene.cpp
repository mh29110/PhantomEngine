#include "Scene.h"
#include "SceneObjectVertexArray.h"
#include "SceneOjbectTypeDef.h"
#include "SceneBaseNode.h"
#include "OpengexParser.h"

using namespace Phantom;
using namespace std;
const float varr[] = {
		  1.0f,  1.0f,  1.0f ,
		  1.0f,  1.0f, -1.0f ,
		 -1.0f,  1.0f, -1.0f ,
		 -1.0f,  1.0f,  1.0f ,
		  1.0f, -1.0f,  1.0f ,
		  1.0f, -1.0f, -1.0f ,
		 -1.0f, -1.0f, -1.0f ,
		 -1.0f, -1.0f,  1.0f };
const float carr[] = {
		 1.0f, 0.0f, 0.0f ,
		 0.0f, 1.0f, 0.0f ,
		 0.0f, 0.0f, 1.0f ,
		 1.0f, 1.0f, 0.0f ,
		 1.0f, 0.0f, 1.0f ,
		 0.0f, 1.0f, 1.0f ,
		 0.5f, 1.0f, 0.5f ,
		 1.0f, 0.5f, 1.0f };
Phantom::Scene::Scene()
{
	string ogex_text = g_pAssetLoader->SyncOpenAndReadTextFileToString("Resources/Scene/Example.ogex");

	OpengexParser paser;
	std::unique_ptr<SceneBaseNode> root = paser.Parse(ogex_text);

	m_pMesh = new SceneObjectMesh();
	SceneObjectVertexArray* sov = new SceneObjectVertexArray("", 0U, VertexDataType::kVertexDataTypeFloat3, (const char *)varr);
	m_pMesh->AddVertexArray(std::move(*sov));
	SceneObjectVertexArray* soc = new SceneObjectVertexArray("", 0U, VertexDataType::kVertexDataTypeFloat3, (const char *)carr);
	m_pMesh->AddVertexArray(std::move(*soc));
}
