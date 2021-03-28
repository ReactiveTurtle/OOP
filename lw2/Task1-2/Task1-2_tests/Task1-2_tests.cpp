#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Task1-2/VectorExtensions.h"

using namespace std;

SCENARIO("Check GetMin when vector is empty")
{
	vector<float> vec = { };
	bool wasFound;
	float min = GetMin(vec, wasFound);
	REQUIRE(!wasFound);
}

SCENARIO("Check GetMin when vector is not empty")
{
	vector<float> vec = { 5, 10, 3, 15 };
	bool wasFound;
	float min = GetMin(vec, wasFound);
	REQUIRE(wasFound);
	REQUIRE(min == 3);
}

SCENARIO("Check Multiply when vector is empty")
{
	vector<float> vec = {};
	vector<float> multiplied = Multiply(vec, 1);
	REQUIRE(multiplied.size() == 0);
}

SCENARIO("Check Multiply when vector is not empty")
{
	vector<float> vec = { 5, 10, 3, 15 };
	vector<float> multiplied = Multiply(vec, 5);
	vector<float> expected = { 25, 50, 15, 75 };
	REQUIRE(multiplied.size() == expected.size());
	for (size_t i = 0; i < multiplied.size(); i++) {
		REQUIRE(multiplied[i] == expected[i]);
	}
}

SCENARIO("Check Sort when vector is empty")
{
	vector<float> vec = { };
	vector<float> sorted = Sort(vec);
	REQUIRE(sorted.size() == 0);
}

SCENARIO("Check Sort when vector is not empty")
{
	vector<float> vec = { 5, 10, 3, 15 };
	vector<float> sorted = Sort(vec);
	vector<float> expected = { 3, 5, 10, 15 };
	REQUIRE(sorted.size() == expected.size());
	for (size_t i = 0; i < sorted.size(); i++) {
		REQUIRE(sorted[i] == expected[i]);
	}
}
