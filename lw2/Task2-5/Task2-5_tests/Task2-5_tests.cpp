#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Task2-5/HTMLDecoder.hpp"

SCENARIO("Decode empty string")
{
	string actual = HtmlDecode("");
	string expected = "";
	REQUIRE(actual == expected);
}

SCENARIO("Decode string without special chars")
{
	string actual = HtmlDecode("Hello");
	string expected = "Hello";
	REQUIRE(actual == expected);
}

SCENARIO("Decode string with special chars")
{
	string actual = HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	string expected = "Cat <says> \"Meow\". M&M's";
	REQUIRE(actual == expected);
}

SCENARIO("Decode string with special chars and single ';'")
{
	string actual = HtmlDecode("Cat; &lt;says&gt;; &quot;Meow&quot;. M&amp;M&apos;s");
	string expected = "Cat; <says>; \"Meow\". M&M's";
	REQUIRE(actual == expected);
}

SCENARIO("Decode string without special chars and single ';'")
{
	string actual = HtmlDecode("He;llo");
	string expected = "He;llo";
	REQUIRE(actual == expected);
}

SCENARIO("Decode string with unexpected special chars")
{
	string actual = HtmlDecode("Cat; &dty;says&gt;; &quot;Meow&quot;. M&amp;M&apos;s");
	string expected = "Cat; &dty;says>; \"Meow\". M&M's";
	REQUIRE(actual == expected);
}

