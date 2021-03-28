#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Task4-4/PrimeNumberGenerator.hpp"

SCENARIO("Generate prime numbers when limit is 0")
{
	set<int> actualPrimeNumbers = GeneratePrimeNumbersSet(0);
	REQUIRE(actualPrimeNumbers.size() == 0);
}

SCENARIO("Generate prime numbers when limit is 2")
{
	set<int> actualPrimeNumbers = GeneratePrimeNumbersSet(2);
	REQUIRE(actualPrimeNumbers.size() == 1);
	REQUIRE(*actualPrimeNumbers.begin() == 2);
}

SCENARIO("Generate prime numbers when limit is 100")
{
	set<int> actualPrimeNumbers = GeneratePrimeNumbersSet(100);
	set<int> expectedPrimeNumbers
	{
		2, 3, 5, 7, 11,
		13, 17, 19, 23, 29,
		31, 37, 41, 43, 47, 
		53, 59, 61, 67, 71,
		73, 79, 83, 89, 97
	};
	REQUIRE(actualPrimeNumbers.size() == expectedPrimeNumbers.size());
	set<int>::iterator expectedIterator = expectedPrimeNumbers.begin();
	for (set<int>::iterator i = actualPrimeNumbers.begin(); i != actualPrimeNumbers.end(); i++)
	{
		int actualNumber = *i;
		int expectedNumber = *expectedIterator;
		REQUIRE(actualNumber == expectedNumber);
		expectedIterator++;
	}
}

SCENARIO("Generate prime numbers when limit is 100 000 000")
{
	set<int> actualPrimeNumbers = GeneratePrimeNumbersSet(100000000);
	REQUIRE(actualPrimeNumbers.size() == 5761455);
}