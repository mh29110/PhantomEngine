#pragma once 

#pragma region heap sort

//! Sinks an element into the heap.
template<class T>
inline void heapsink(T*array, int element, int max)
{
	while ((element << 1) < max) // there is a left child
	{
		int j = (element << 1);

		if (j + 1 < max && array[j] < array[j + 1])
			j = j + 1; // take right child

		if (array[element] < array[j])
		{
			T t = array[j]; // swap elements
			array[j] = array[element];
			array[element] = t;
			element = j;
		}
		else
			return;
	}
}


//* 堆排实际使用不如快排普及，因为虽然算法上时间复杂度低，
//* 但是堆排序比较的几乎都不是内存相邻元素，对cache极不友好，数据读取开销变大。
//! Sorts an array with size 'size' using heapsort.
template<class T>
inline void heapsort(T* array_, int size)
{
	// for heapsink we pretent this is not c++, where
	// arrays start with index 0. So we decrease the array pointer,
	// the maximum always +2 and the element always +1

	T* virtualArray = array_ - 1;
	int virtualSize = size + 2;
	int i;

	// build heap

	for (i = ((size - 1) / 2); i >= 0; --i)
		heapsink(virtualArray, i + 1, virtualSize - 1);

	// sort array, leave out the last element (0)
	for (i = size - 1; i > 0; --i)
	{
		T t = array_[0];
		array_[0] = array_[i];
		array_[i] = t;
		heapsink(virtualArray, 1, i + 1);
	}
}

#pragma endregion


#pragma region quick sort
//* 特点   比较和交换次数少，在许多情况下可以高速排序。
template	<typename T>
void QuickSort(T source[], int left, int right)
{
	if (left >= right) return;
	int i = left;
	int j = right;
	int pivot = source[left];

	while (true)
	{
		while (source[++i] < pivot)
		{
			if (i == right)
				break;
		}
		while (source[--j] > pivot)
		{
			if (j == left)
				break;
		}
		if (i >= j)
			break;
		int temp = source[i];//* swap  i , j 
		source[i] = source[j];
		source[j] = temp;
	}
	int temp = source[left];
	source[left] = source[j];
	source[j] = temp;
	QuickSort(source, left, j-1);
	QuickSort(source, j+1, right);
}

#pragma endregion


#pragma region bubble sort
// args  [0] DataType Array
// args  [1] start index of source array
// args  [2] end index of source array
// args  [3] 

template	<typename DataType>
void BubbleSort(DataType source[], int left, int right, bool up = true)
{
	int i, j;
	DataType data;
	if (up)
	{
		for (i = left; i < right;i++)
		{
			for (j = right; j>= i+1;j--)
			{
				if (source[j-1] > source[j])
				{
					data = source[j-1];
					source[j-1] = source[j];
					source[j] = data;
				}
			}
		}
	}
	else
	{
		for (i = left; i < right; i++)
		{
			for (j = right; j >= i + 1; j--)
			{
				if (source[j - 1] < source[j])
				{
					data = source[j - 1];
					source[j - 1] = source[j];
					source[j] = data;
				}
			}
		}
	}
}
#pragma endregion
