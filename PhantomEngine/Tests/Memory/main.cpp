#include <iostream>
#include "src/PhAllocator.h"

int main(int argc, char **argv)
{
	printf("hello ");
	Phantom::Allocator alloc(sizeof(unsigned), 1024, 4);
	for (int i = 0; i < 2050; i++)
	{
		unsigned *k = reinterpret_cast<unsigned*>(alloc.Allocate());
		*k = 2;
	}
	
	
	alloc.FreeAll();
}