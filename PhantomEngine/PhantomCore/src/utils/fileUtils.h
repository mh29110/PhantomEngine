#pragma once

#include <fstream>
#include <stdlib.h>

char* read_file(const char* filename)
{
	FILE * file = fopen( filename , "rt");
	char* code ;
	size_t n = 0;
	int c ;

	if(file == NULL) {
		printf("open file failed!!!");
		return NULL;
	}
	fseek(file , 0 , SEEK_END);
	long file_size = ftell(file);//seek到文件尾并记录当前读写文字，即文件大小。
	fseek(file , 0 , SEEK_SET);
	code = (char * ) malloc ( file_size);

	while((c = fgetc(file)) != EOF)
	{
		code[n++] = (char) c;
	}

	fclose(file);

	code[n] = '\0';

	return code;
}
