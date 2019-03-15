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
}

int main(int , char** )
{

    string ogex_text = g_pAssetLoader->SyncOpenAndReadTextFileToString("Resources/Scene/Example.ogex");

	OpengexParser paser;
	std::unique_ptr<SceneBaseNode> root = paser.Parse(ogex_text);

	cout << "Dump of Geometries" << endl;
	cout << "---------------------------" << endl;
	cout << *root << endl;

    return 0;
}

