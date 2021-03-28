#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "VectorExtensions.h"

using namespace std;

vector<float> ReadNumbers(bool& wasError);
void PrintNumbers(vector<float> numbers);

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
		numbers = Sort(numbers);
	}
	PrintNumbers(numbers);
	return 0;
}

bool IsNumber(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && (isdigit(*it) || *it == '-')) ++it;
	return !s.empty() && it == s.end();
}

vector<float> ReadNumbers(bool& wasError)
{
	wasError = false;
	vector<float> numbers(0);
	char previousCh;
	char ch = ' ';
	bool isFoundFirstNotSpace = false;

	string mayBeNumber;
	do {
		previousCh = ch;
		ch = getchar();
		if (ch == ' ' || ch == '\n')
		{
			if (isFoundFirstNotSpace)
			{
				cout << mayBeNumber << endl;
				if (!IsNumber(mayBeNumber)) {
					wasError = true;
					return numbers;
				}
				size_t errorPosition;
				float number = stof(mayBeNumber, &errorPosition);
				if (errorPosition != mayBeNumber.size())
				{
					wasError = true;
					return numbers;
				}
				numbers.push_back(number);
				mayBeNumber = "";
				isFoundFirstNotSpace = false;
			}
		}
		else
		{
			if (!isFoundFirstNotSpace)
			{
				isFoundFirstNotSpace = true;
			}
			mayBeNumber += ch;
		}
	} while (ch != '\n');
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
