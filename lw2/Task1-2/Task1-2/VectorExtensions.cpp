#include "VectorExtensions.h"
#include <vector>

using namespace std;

float GetMin(vector<float> numbers, bool& wasFound)
{
	size_t numbersCount = numbers.size();
	wasFound = numbersCount != 0;
	float min = INT_MAX;
	if (!wasFound) 
	{
		return min;
	}
	bool isMinInitialized = false;
	for (size_t i = 0; i < numbersCount; i++)
	{
		if (!isMinInitialized || numbers[i] < min)
		{
			isMinInitialized = true;
			min = numbers[i];
		}
	}
	return min;
}

vector<float> Multiply(vector<float> numbers, float factor)
{
	size_t numbersCount = numbers.size();
	for (size_t i = 0; i < numbersCount; i++)
	{
		numbers[i] *= factor;
	}
	return numbers;
}

int Partition(vector<float>& array, int start, int end)
{
	float temp;
	int marker = start;
	for (int i = start; i < end; i++)
	{
		if (array[i] < array[end])
		{
			temp = array[marker];
			array[marker] = array[i];
			array[i] = temp;
			marker += 1;
		}
	}
	temp = array[marker];
	array[marker] = array[end];
	array[end] = temp;
	return marker;
}

void QuickSort(vector<float>& array, int start, int end)
{
	if (start >= end)
	{
		return;
	}
	int pivot = Partition(array, start, end);
	QuickSort(array, start, pivot - 1);
	QuickSort(array, pivot + 1, end);
}

vector<float> Sort(vector<float> array)
{
	QuickSort(array, 0, array.size() - 1);
	return array;
}