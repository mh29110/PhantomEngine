#include "SceneObjectTrack.h"
#include <iostream>
using namespace Phantom;
using namespace std;
void SceneObjectTrack::Update(const float deltaValue)
{
	cout << "track update " << endl;
	m_pTransform->Update(deltaValue);//todo
}
