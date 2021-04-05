#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Task3-2/DictionaryExtensions.hpp"

SCENARIO("Parse valid translation")
{
	string str = "\"cat\":\"кошка, кот\"";
	Translation actualTranslation = ParseTranslation(str);
	Translation expectedTranslation;
	REQUIRE(actualTranslation.english == "cat");
	REQUIRE(actualTranslation.russians == vector<string>{"кошка", "кот"});
}

SCENARIO("Parse invalid translation")
{
	string str = "   \"\":\"кошка, кот\"    ";
	Translation actualTranslation = ParseTranslation(str);
	Translation expectedTranslation;
	REQUIRE(actualTranslation.english == "");
	REQUIRE(actualTranslation.russians == vector<string>{"кошка", "кот"});
}

SCENARIO("Split by ' *, *'")
{
	vector<string> splitted = Split("кошка   ,   кот", " *, *");
	REQUIRE(splitted == vector<string>{ "кошка", "кот" });
}

SCENARIO("To lower case")
{
	REQUIRE(ToLowerCase("CaT") == "cat");
}
