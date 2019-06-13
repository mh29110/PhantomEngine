#include <iostream>
#include "src/PhAllocator.h"
#include <windows.h>

int main(int argc, char **argv)
{


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

	printf("hello ");
	Phantom::Allocator alloc(sizeof(unsigned), 1024, 4);
	for (int i = 0; i < 2050; i++)
	{
		unsigned *k = reinterpret_cast<unsigned*>(alloc.Allocate());
		*k = 2;
	}


	alloc.FreeAll();
}