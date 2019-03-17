#include "Scene.h"
#include "SceneObjectVertexArray.h"
#include "SceneOjbectTypeDef.h"
#include "SceneBaseNode.h"
#include "OpengexParser.h"

using namespace Phantom;
using namespace std;


Phantom::Scene::Scene(const char * name):SceneGraph(new SceneBaseNode(name))
{
	camera = make_shared<CameraNode>();
}

Phantom::Scene::~Scene()
{
}
