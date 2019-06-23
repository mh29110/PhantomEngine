#pragma once
#include "vector.h"
#include <map>

namespace Phantom {
	namespace TextCore {
		enum FontEngineState {
			FontEngine_Initialized = 0x1,
			FontEngine_Destoryed = 0x2,
			FontEngine_DelayedDestruction = 0x3
		};
		struct Character {
			unsigned char* buffer;
			maths::vec2 Size;    // Size of glyph
			maths::vec2  Bearing;  // Offset from baseline to left/top of glyph
			int Advance;    // Horizontal offset to advance to next glyph
		};
		class FontEngine
		{
		public:
			FontEngine();
			~FontEngine();
			int LoadFontFace(const char* path);
			int DestoryFontEngine();

			Character RenderGlyphToTextureData(char c);
		private:
			bool init();


		public:
			std::map<char, Character> m_Characters;
		};

	}
}