#include <string>
#include <regex>
#include <iostream>
#include <map>

using namespace std;

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

const map<string, Protocol> DECLARED_PROTOCOLS =
{
	{"http", Protocol::HTTP},
	{"https", Protocol::HTTPS},
	{"ftp", Protocol::FTP}
};

const map<Protocol, int> DEFAULT_PROTOCOL_PORTS =
{
	{Protocol::HTTP, 80},
	{Protocol::HTTPS, 443},
	{Protocol::FTP, 21}
};

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	regex urlRegex("^(\\w+):\\/\\/((\\w+\\.{0,1})+\\w+)(:\\d{1,5})*(\\/.*)*$");
	smatch urlMatchResult;

	if (!regex_match(url, urlMatchResult, urlRegex))
	{
		return false;
	}
	string mayBeProtocol = urlMatchResult[1];
	transform(mayBeProtocol.begin(), mayBeProtocol.end(), mayBeProtocol.begin(),
		[](unsigned char c) { return tolower(c); });
	auto it = DECLARED_PROTOCOLS.find(mayBeProtocol);
	if (it == DECLARED_PROTOCOLS.end())
	{
		return false;
	}
	protocol = it->second;

	string portStr = urlMatchResult[4];
	port = portStr.empty()
		? DEFAULT_PROTOCOL_PORTS.find(protocol)->second
		: stoi(portStr.substr(1));
	if (port < 1 || port > 65535)
	{
		return false;
	}

	host = urlMatchResult[2];

	string documentStr = urlMatchResult[5];
	document = documentStr.empty() ? "" : documentStr.substr(1);

	return true;
}