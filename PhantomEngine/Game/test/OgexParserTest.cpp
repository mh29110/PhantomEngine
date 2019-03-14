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
	paser.Parse(ogex_text);
	//OpenGexDataDescription	openGexDataDescription;
	//DataResult result = openGexDataDescription.ProcessText((char*)ogex_text.data());
	//if (result == kDataOkay)
	//{
	//	const Structure *structure = openGexDataDescription.GetRootStructure()->GetFirstSubnode();
	//	while (structure)
	//	{
	//		// This loops over all top-level structures in the file.

	//		// Do something with the data...
	//		std::cout << structure->GetStructureType();
	//		structure = structure->Next();
	//	}
	//}
    return 0;
}

