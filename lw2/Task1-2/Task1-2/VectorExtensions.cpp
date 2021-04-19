#include "VectorExtensions.h"
#include <vector>
#include <algorithm>

using namespace std;

float GetMin(vector<float> numbers, bool& wasFound)
{
	auto it = min_element(numbers.begin(), numbers.end());
	wasFound = it != numbers.end();
	if (!wasFound) return 0;
	return *it;
}

vector<float> Multiply(vector<float> numbers, float factor)
{
	transform(numbers.begin(), numbers.end(), numbers.begin(), [factor](float& number) { return number * factor; });
	return numbers;
}
