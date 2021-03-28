#include <iostream>
#include <fstream>
#include <string>
#include "PrimeNumberGenerator.hpp"

int ParseInt(const string& mayBeNumber, bool& wasError);
bool IsNumber(const string& s);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Enter the upper limit as second argument." << endl;
		return 1;
	}

	bool wasError;
	int number = ParseInt(argv[1], wasError);
	if (wasError)
	{
		cout << "Invalid second argument. Must be not negative number." << endl;
		return 1;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(number);
	int i = 0;
	for (set<int>::iterator j = primeNumbers.begin(); j != primeNumbers.end(); j++)
	{
		int number = *j;
		cout << number << endl;
		i++;
	}
	if (primeNumbers.size() == 0) {
		cout << "Prime numbers not found with current limit." << endl;
	}
	return 0;
}

int ParseInt(const string& mayBeNumber, bool& wasError)
{
	wasError = false;
	if (!IsNumber(mayBeNumber))
	{
		wasError = true;
		return 0;
	}
	size_t errorPosition;
	int number = stoi(mayBeNumber, &errorPosition);
	if (errorPosition != mayBeNumber.size() || number < 0)
	{
		wasError = true;
		return 0;
	}
	return number;
}

bool IsNumber(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && (isdigit(*it) || *it == '-')) ++it;
	return !s.empty() && it == s.end();
}
