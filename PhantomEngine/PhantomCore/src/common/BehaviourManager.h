#pragma once
#include "interface/IRuntimeModule.h"
#include <iostream>
#include "scene/camera.h"

namespace Phantom {
	class BehaviourManager : implements IRuntimeModule
	{
	protected:
		std::weak_ptr<CameraNode> camera;
	public:
		virtual int Init() ;
		virtual void Shutdown() ;
		virtual void Tick() ;


		virtual void OnButton1Down() {};
		virtual void OnButton1Up() {};

		virtual void LeftMouseDrag(int deltaX, int deltaY);
	};

	extern BehaviourManager* g_pBehaviourManager;
}