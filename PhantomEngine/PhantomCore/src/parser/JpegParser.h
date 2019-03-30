#pragma once
#include <iostream>
#include <setjmp.h>
#include "ImageParser.h"
#include "jpeglib.h"

namespace Phantom {

	class JpegParser : implements ImageParser
	{
	public:
		virtual Image Parse(Buffer& buf)
		{
			Image img;
			struct jpeg_decompress_struct cinfo;
			struct jpeg_error_mgr jerr;
			// 分配和初始化一个decompression结构体
			cinfo.err = jpeg_std_error(&jerr);
			jpeg_create_decompress(&cinfo);

			jpeg_mem_src(&cinfo, buf.GetData(),buf.GetDataSize());

			// 用jpeg_read_header获得jpg信息
			jpeg_read_header(&cinfo, TRUE);
			/* 源信息 */
			printf("image_width    = %d\n", cinfo.image_width);
			printf("image_height   = %d\n", cinfo.image_height);

			// 设置解压参数,比如放大、缩小
		  // 启动解压：jpeg_start_decompress
			jpeg_start_decompress(&cinfo);

			/* 输出的图像信息 */
			printf("output_width   = %d\n", cinfo.output_width);
			printf("output_height  = %d\n", cinfo.output_height);
			printf("output_components = %d\n", cinfo.output_components);

			//设置一行的数据buffer
			int row_stride = cinfo.output_width* cinfo.output_components;
			int buffer_height = 1;
			JSAMPARRAY buffer = (JSAMPARRAY)malloc(sizeof(JSAMPROW)*buffer_height);
			buffer[0] = (JSAMPROW)malloc(sizeof(JSAMPLE) * row_stride);
			img.bitcount = sizeof(JSAMPLE)* cinfo.output_components*8;
			img.pitch = row_stride;
			img.data_size = cinfo.output_width * cinfo.output_height * cinfo.output_components;
			img.data = new uint8_t[img.data_size];
			long counter = 0;
			// 循环调用jpeg_read_scanlines一行一行的获得解压数据
			while (cinfo.output_scanline < cinfo.output_height) {
				jpeg_read_scanlines(&cinfo, buffer, 1);
				memcpy(img.data + counter, buffer[0], row_stride);
				counter += row_stride;
			}
				//setting
			img.Width = cinfo.output_width;
			img.Height = cinfo.output_height;
		
			jpeg_finish_decompress(&cinfo);

			jpeg_destroy_decompress(&cinfo);

			img.mipmaps[0].Width = img.Width;
			img.mipmaps[0].Height = img.Height;
			img.mipmaps[0].pitch = img.pitch;
			img.mipmaps[0].offset = 0;
			img.mipmaps[0].data_size = img.data_size;
			return img;
		}
	};
}
