#include <iostream>
#include "src/PhAllocator.h"
#include <windows.h>
#include "maths/sort.h"
#include "ft2build.h"
#include FT_FREETYPE_H

int main(int argc, char **argv)
{
	FT_Library	library;
	FT_Face		face;
	FT_Error	error;
	FT_UInt		charIdx;
	wchar_t		wch = 'a';
	char*		buffer;		// 用户申请的显示区域空间
	int			startX, startY;	// 字符图像开始装入的位置

	// 1. 初始化freetype2库
	error = FT_Init_FreeType(&library);

	// 2. 创建一个face
	error = FT_New_Face(library, "C:\\windows\\Fonts\\Arial.TTF", 0, &face);

	// 3. 设置字体尺寸
	error = FT_Set_Char_Size(face, 16 * 64, 16 * 64, 96, 96);

	// 4. 获取字符图像索引
	charIdx = FT_Get_Char_Index(face, wch);

	// 5. 加载字符图像
	FT_Load_Glyph(face, charIdx, FT_LOAD_DEFAULT);
	//if (face->glyph->format == FT_GLYPH_FORMAT_OUTLINE)
	//{
	//	FT_Outline_Embolden(&(face->glyph->outline), 16);	// 加粗轮廓线
	//}

	// 6. 获取字符位图
	if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
	{
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
	}

	// 7. 拷贝字符位图到用户的buffer中(用户私人函数)
	// 注意左边的计算方法
	/*ft2CopyBitmapToBuf(buffer, startX + face->glyph->bitmap_left,
		startY + face->size->metrics.ascender / 64 - face->glyph->bitmap_top,
		face->glyph->bitmap);
	startX += face->glyph->advance.x / 64
	*/

#if 0 //example0 
	SetThreadAffinityMask(GetCurrentThread(), 1);

	const DWORD busyTime = 10;
	int startTime = 0;
	while (true)
	{
		DWORD starTime = GetTickCount();
		while ((GetTickCount() - starTime) <= busyTime)
			;
		Sleep(busyTime);
	}
#endif
	
	int a[] = { 57, 68, 59, 52, 72, 28, 96, 33, 24 };

	QuickSort(a, 0, sizeof(a) / sizeof(a[0]) );/*这里原文第三个参数要减1否则内存越界*/

	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		std::cout << a[i] << " ";
	}

	printf("hello ");
	Phantom::Allocator alloc(sizeof(unsigned), 1024, 4);
	for (int i = 0; i < 2050; i++)
	{
		unsigned *k = reinterpret_cast<unsigned*>(alloc.Allocate());
		*k = 2;
	}


	alloc.FreeAll();
}