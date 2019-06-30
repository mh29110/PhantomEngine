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

			maths::vec2 offset;//for textcoord uv mapping
		};
		const int K_TEXTURE_SIZE = 512;
		const int K_FONT_SIZE = 32;
		class FontEngine
		{
		public:
			FontEngine();
			~FontEngine();
			int LoadFontFace(const char* path);
			int DestoryFontEngine();

			void  RenderGlyphToTextureData(char c);
		private:
			bool init();


		public:
			std::map<char, Character> m_Characters;
		};

	}
}
