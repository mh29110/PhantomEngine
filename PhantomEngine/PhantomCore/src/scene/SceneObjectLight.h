#pragma once
#include "SceneBaseObject.h"

namespace Phantom {
	class SceneObjectLight : public SceneBaseObject
	{
	protected:
		// can only be used as base class of delivered lighting objects
		SceneObjectLight(const SceneObjectType type) : SceneBaseObject(type){}
	};
	class SceneObjectDirectLight :public SceneObjectLight
	{
	public:
		SceneObjectDirectLight(void):SceneObjectLight(SceneObjectType::kSceneObjectTypeLightInfi) {};
	};
}