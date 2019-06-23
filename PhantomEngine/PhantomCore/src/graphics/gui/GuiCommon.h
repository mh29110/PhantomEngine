#pragma once
#include <iostream>

namespace Phantom {
	namespace GUI {
		struct GuiDisplayUnit {
			float posX;
			float posY;
			std::string content;
		};

		enum GUIIndex
		{
			FrameGuiIdx,
			KeycodeGuiIdx,
		};
	}
}
