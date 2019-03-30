#pragma once
#include <cstring>
#include <iostream>

namespace Phantom {

    struct Image {
        uint32_t Width;//纹理宽度
        uint32_t Height;//纹理高度
        uint8_t* data;

		//---与位图本身的质量、在内存上的压缩格式以及内存对齐方式有关
        uint32_t bitcount;//一个像素占用内存大小（bit数）
        uint32_t pitch; //图形的一行占用内存大小（byte数）

        size_t  data_size;
        bool    compressed;
        bool    is_float;
        uint32_t compress_format;
        uint32_t mipmap_count;
        struct Mipmap {
            uint32_t Width;
            uint32_t Height;
            uint32_t pitch;
            size_t offset;
            size_t data_size;
        } mipmaps[10];

        Image() : Width(0),
            Height(0),
            data(nullptr),
            bitcount(0),
            pitch(0),
            data_size(0),
            compressed(false),
            is_float(false),
            mipmap_count(1)
        {
            std::memset(mipmaps, 0x00, sizeof(mipmaps));
        };
    };

    std::ostream& operator<<(std::ostream& out, const Image& image);
}
