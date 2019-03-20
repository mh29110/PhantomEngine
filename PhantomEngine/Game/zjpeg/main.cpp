#include <stdio.h>
#include "jpeglib.h"
#include <setjmp.h>


/*
Allocate and initialize a JPEG decompression object    // 分配和初始化一个decompression结构体
Specify the source of the compressed data (eg, a file) // 指定源文件
Call jpeg_read_header() to obtain image info           // 用jpeg_read_header获得jpg信息
Set parameters for decompression                       // 设置解压参数,比如放大、缩小
jpeg_start_decompress(...);                            // 启动解压：jpeg_start_decompress
while (scan lines remain to be read)
	jpeg_read_scanlines(...);                           // 循环调用jpeg_read_scanlines
jpeg_finish_decompress(...);                           // jpeg_finish_decompress
Release the JPEG decompression object                   // 释放decompression结构体
*/

/* Uage: jpg2rgb <jpg_file>
 */

int main(int argc, char **argv)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE * infile;

	// 分配和初始化一个decompression结构体
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	// 指定源文件
	if ((infile = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", argv[1]);
		return -1;
	}
	jpeg_stdio_src(&cinfo, infile);

	// 用jpeg_read_header获得jpg信息
	jpeg_read_header(&cinfo, TRUE);
	/* 源信息 */
	printf("image_width    = %d\n", cinfo.image_width);
	printf("image_height   = %d\n", cinfo.image_height);
	printf("num_components = %d\n", cinfo.num_components);


	// 设置解压参数,比如放大、缩小

  // 启动解压：jpeg_start_decompress
	jpeg_start_decompress(&cinfo);

	/* 输出的图像信息 */
	printf("output_width   = %d\n", cinfo.output_width);
	printf("output_height  = %d\n", cinfo.output_height);
	printf("output_components = %d\n", cinfo.output_components);

	// 循环调用jpeg_read_scanlines一行一行的获得解压数据

	jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	return 0;
}