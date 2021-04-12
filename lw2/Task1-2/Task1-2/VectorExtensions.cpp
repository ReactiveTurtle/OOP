#include "VectorExtensions.h"
#include <vector>
#include <algorithm>

using namespace std;

float GetMin(vector<float> numbers, bool& wasFound)
{
	if (numbers.size() == 0) {
		wasFound = false;
		return 0;
	}
	wasFound = true;
	return *min_element(numbers.begin(), numbers.end());
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
