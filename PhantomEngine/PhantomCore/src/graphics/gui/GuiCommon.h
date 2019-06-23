#pragma once
#include <iostream>

namespace Phantom {
	namespace GUI {
		struct GuiDisplayUnit {
			float posX;
			float posY;
			std::string content;
			maths::vec3	color;
		};

		enum GUIIndex
		{
			FrameGuiIdx,
			KeycodeGuiIdx,
		};
	}
}
