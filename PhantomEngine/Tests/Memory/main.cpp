#include <iostream>
#include "src/PhAllocator.h"
#include <windows.h>
#include "sort.h"

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