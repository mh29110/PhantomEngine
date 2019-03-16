#include "Scene.h"
#include "SceneObjectVertexArray.h"
#include "SceneOjbectTypeDef.h"
#include "SceneBaseNode.h"
#include "OpengexParser.h"

using namespace Phantom;
using namespace std;

Phantom::Scene::Scene()
{
	string ogex_text = g_pAssetLoader->SyncOpenAndReadTextFileToString("Resources/Scene/aili.ogex");

	OpengexParser paser;
	std::unique_ptr<SceneBaseNode> root = paser.Parse(ogex_text);

	camera = make_shared<CameraNode>();
}

Phantom::Scene::~Scene()
{
}
