#pragma once
#include "IRuntimeModule.h"
#include <iostream>
#include "camera.h"

namespace Phantom {
	class BehaviourManager : implements IRuntimeModule
	{
	protected:
		std::weak_ptr<CameraNode> camera;
	public:
		virtual int Init() ;
		virtual void Shutdown() ;
		virtual void Tick() ;

		virtual void OnUpKeyDown() {
			std::cout << "on upkey down" << std::endl;
			//camera.lock()->m_positionZ += 1.1f;
		};
		virtual void OnUpKeyUp() {};
		virtual void OnUpKey() {};

		virtual void OnDownKeyDown() {
			//camera.lock()->m_positionZ -= 1.1f;
		};
		virtual void OnDownKeyUp() {};
		virtual void OnDownKey() {};

		virtual void OnLeftKeyDown() {
			//camera.lock()->m_positionX -= 1.1f;
		};
		virtual void OnLeftKeyUp() {};
		virtual void OnLeftKey() {};

		virtual void OnRightKeyDown() {
			//camera.lock()->m_positionX += 1.1f;
		};
		virtual void OnRightKeyUp() {};
		virtual void OnRightKey() {};

		virtual void OnButton1Down() {};
		virtual void OnButton1Up() {};

	};

	extern BehaviourManager* g_pBehaviourManager;
}