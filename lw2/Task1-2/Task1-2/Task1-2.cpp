#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "VectorExtensions.h"

using namespace std;

bool IsNumber(const string& s)
{
	string::const_iterator it = s.begin();
	if (*it != '-' && !isdigit(*it)) return false;
	while (it != s.end() && (isdigit(*it))) ++it;
	return !s.empty() && it == s.end();
}

vector<float> ReadNumbers(bool& wasError)
{
	wasError = false;
	vector<float> numbers(0);
	string line;
	getline(cin, line);

	stringstream ss(line);
	while (!ss.eof() && !wasError)
	{
		string number;
		ss >> number;
		wasError = !IsNumber(number);
		if (!wasError)
		{
			numbers.push_back(stoi(number));
		}
	}
	return numbers;
}

void PrintNumbers(vector<float> numbers)
{
	cout << fixed;
	size_t numbersCount = numbers.size();
	for (size_t i = 0; i < numbersCount; i++)
	{
		cout << setprecision(3) << numbers[i];
		if (i < numbersCount - 1)
		{
			cout << " ";
		}
	}
	cout << scientific;
	cout << endl;
}

int main()
{
	bool wasError;
	vector<float> numbers = ReadNumbers(wasError);
	if (wasError) {
		cout << "One of the numbers is entered incorrectly" << endl;
		return 1;
	}

	bool wasFound;
	float min = GetMin(numbers, wasFound);
	if (wasFound)
	{
		numbers = Multiply(numbers, min);
		sort(numbers.begin(), numbers.end());
	}
	PrintNumbers(numbers);
	return 0;
}
