#include <iostream>
#include <string>
#include "AssetLoadManager.h"
#include "OpenGEX.h"
#include "OpengexParser.h"

using namespace Phantom;
using namespace std;

using namespace ODDL;
using namespace OGEX;

namespace Phantom {
	AssetLoadManager*     g_pAssetLoader = static_cast<AssetLoadManager*>(new AssetLoadManager);
	std::unordered_map<std::string, std::shared_ptr<SceneBaseObject>> g_SceneObjects;
}

int main(int , char** )
{

    string ogex_text = g_pAssetLoader->SyncOpenAndReadTextFileToString("Resources/Scene/car.ogex");

	OpengexParser paser;
	std::unique_ptr<Scene> root = paser.Parse(ogex_text);

	cout << "Dump of Geometries" << endl;
	cout << "---------------------------" << endl;
	//cout << *root << endl;
    return 0;
}

