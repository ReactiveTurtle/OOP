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
	string portRegex = "([1-9]|[1-5]?[0-9]{2,4}|6[1-4][0-9]{3}|65[1-4][0-9]{2}|655[1-2][0-9]|6553[1-5])";
	regex urlRegex("^(http|https|ftp):\\/\\/((\\w+\\.{0,1})+\\w+)(:" + portRegex + ")*(\\/.*)*$");
	smatch urlMatchResult;

	if (!regex_match(url, urlMatchResult, urlRegex))
	{
		return false;
	}
	protocol = DECLARED_PROTOCOLS.find(urlMatchResult[1])->second;

	string portStr = urlMatchResult[4];
	port = portStr.empty()
		? DEFAULT_PROTOCOL_PORTS.find(protocol)->second
		: stoi(portStr.substr(1));

	host = urlMatchResult[2];

	string documentStr = urlMatchResult[6];
	document = documentStr.empty() ? "" : documentStr.substr(1);

	return true;
}