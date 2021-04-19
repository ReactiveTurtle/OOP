#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Task5-1/URLExtensions.hpp"

const int DEFAULT_HTTP_PORT = 80;
const int DEFAULT_HTTPS_PORT = 443;
const int DEFAULT_FTP_PORT = 21;

SCENARIO("Check valid protocol 'http'")
{
	Protocol expectedProtocol = Protocol::HTTP;
	int expectedPort = DEFAULT_HTTP_PORT;
	string expectedHost = "vk.com";
	string expectedDocument = "feeds/post";

	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "http://vk.com/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(wasParsed);
	REQUIRE(actualProtocol == expectedProtocol);
	REQUIRE(actualPort == expectedPort);
	REQUIRE(actualHost == expectedHost);
	REQUIRE(actualDocument == expectedDocument);
}

SCENARIO("Check upper case protocol 'HttP'")
{
	Protocol expectedProtocol = Protocol::HTTP;
	int expectedPort = DEFAULT_HTTP_PORT;
	string expectedHost = "vk.com";
	string expectedDocument = "feeds/post";

	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "HttP://vk.com/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(wasParsed);
	REQUIRE(actualProtocol == expectedProtocol);
	REQUIRE(actualPort == expectedPort);
	REQUIRE(actualHost == expectedHost);
	REQUIRE(actualDocument == expectedDocument);
}


SCENARIO("Check valid protocol 'https'")
{
	Protocol expectedProtocol = Protocol::HTTPS;
	int expectedPort = DEFAULT_HTTPS_PORT;
	string expectedHost = "vk.com";
	string expectedDocument = "feeds/post";

	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "https://vk.com/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(wasParsed);
	REQUIRE(actualProtocol == expectedProtocol);
	REQUIRE(actualPort == expectedPort);
	REQUIRE(actualHost == expectedHost);
	REQUIRE(actualDocument == expectedDocument);
}

SCENARIO("Check valid protocol 'ftp'")
{
	Protocol expectedProtocol = Protocol::FTP;
	int expectedPort = DEFAULT_FTP_PORT;
	string expectedHost = "vk.com";
	string expectedDocument = "feeds/post";

	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "ftp://vk.com/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(wasParsed);
	REQUIRE(actualProtocol == expectedProtocol);
	REQUIRE(actualPort == expectedPort);
	REQUIRE(actualHost == expectedHost);
	REQUIRE(actualDocument == expectedDocument);
}

SCENARIO("Check invalid protocol")
{
	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "file://vk.com/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(!wasParsed);
}

SCENARIO("Check valid min port")
{
	Protocol expectedProtocol = Protocol::HTTP;
	int expectedPort = 1;
	string expectedHost = "vk.com";
	string expectedDocument = "feeds/post";

	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "http://vk.com:1/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(wasParsed);
	REQUIRE(actualProtocol == expectedProtocol);
	REQUIRE(actualPort == expectedPort);
	REQUIRE(actualHost == expectedHost);
	REQUIRE(actualDocument == expectedDocument);
}

SCENARIO("Check valid max port")
{
	Protocol expectedProtocol = Protocol::HTTP;
	int expectedPort = 65535;
	string expectedHost = "vk.com";
	string expectedDocument = "feeds/post";

	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "http://vk.com:65535/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(wasParsed);
	REQUIRE(actualProtocol == expectedProtocol);
	REQUIRE(actualPort == expectedPort);
	REQUIRE(actualHost == expectedHost);
	REQUIRE(actualDocument == expectedDocument);
}

SCENARIO("Check invalid min port")
{
	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "http://vk.com:0/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(!wasParsed);
}

SCENARIO("Check invalid max port")
{
	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "http://vk.com:65536/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(!wasParsed);
}

SCENARIO("Check empty port")
{
	Protocol actualProtocol;
	int actualPort;
	string actualHost;
	string actualDocument;
	string url = "http://vk.com:/feeds/post";
	bool wasParsed = ParseURL(url, actualProtocol, actualPort, actualHost, actualDocument);

	REQUIRE(!wasParsed);
}
