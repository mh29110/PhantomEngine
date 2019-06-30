#include <iostream>
#include "FontEngine.h"
#include "ft2build.h"
#include "Image.h"
#include FT_FREETYPE_H
namespace Phantom { namespace TextCore{
	FT_Library m_Library;
	FT_Error m_Error;
	FT_Face m_Face;
	FT_GlyphSlot m_GlyphSlot;

	std::string  m_PreviousPath;

	FontEngineState  fontEngineState;

	FontEngine::FontEngine() {}
	
	FontEngine::~FontEngine()
	{
		DestoryFontEngine();
	}
	int FontEngine::LoadFontFace(const char * path)
	{
		if (m_Library == NULL)
		{
			if (init() != 0) {
				return 0x21;
			}
		}
		if (path != m_PreviousPath)
		{
			if (m_Face != NULL)
			{
				FT_Done_Face(m_Face);
				m_Face = NULL;
			}
			m_Error = FT_New_Face(m_Library, path, 0, &m_Face);

			if (m_Error || m_Face == NULL) {
				return m_Error;
			}

			//m_Error = FT_Set_Pixel_Sizes(m_Face, 0, m_Face->units_per_EM);
			m_Error = FT_Set_Pixel_Sizes(m_Face, 0, K_FONT_SIZE);
			if (m_Error) return m_Error;
			m_PreviousPath = path;
		}

		//m_Error = FT_Set_Char_Size(m_Face, 16 * 64, 16 * 64, 96, 96);

		return 0;
	}
	int FontEngine::DestoryFontEngine()
	{
		if (m_Library == NULL)
		{
			return 0;
		}
		else
		{
			m_Error = FT_Done_FreeType(m_Library);
			m_Library = NULL;
			m_Face = NULL;
			fontEngineState = FontEngine_Destoryed;
			return m_Error;
		}
	}
	bool FontEngine::init()
	{
		m_Error = 0;
		if (m_Library == NULL) {
			m_Error = FT_Init_FreeType(&m_Library);
		}
		if (m_Error == 0)
		{
			fontEngineState = FontEngine_Initialized;
		}
		return m_Error;
	}
	
	void FontEngine::RenderGlyphToTextureData(char c)
	{
		if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		}

		Character character = {
			m_Face->glyph->bitmap.buffer,//注意结构体中指针的用法，如果没有上传又没有memcpy出去，会引用到无效数据。
			 maths::vec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
			maths::vec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
			(int)m_Face->glyph->advance.x
		};
		m_Characters.insert(std::pair<char, Character>(c, character));
	}
}}
