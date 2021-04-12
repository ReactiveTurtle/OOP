#pragma once
#include <string>
#include <map>

using namespace std;

const map<string, char> DECLARED_ENCODES =
{
	{"quot", '"'},
	{"apos", '\''},
	{"lt", '<'},
	{"gt", '>'},
	{"amp", '&'}
};

string HtmlDecode(string const& html)
{
	bool isInEncoded = false;
	string result;
	string key;
	for (char ch : html)
	{
		if (ch == '&' || ch == ';' && isInEncoded)
		{
			if (ch == '&' && isInEncoded)
			{
				result += '&' + key;
				key = "";
			}
			isInEncoded = ch == '&';
			if (!isInEncoded)
			{
				auto position = DECLARED_ENCODES.find(key);
				if (position != DECLARED_ENCODES.end())
				{
					result += position->second;
				}
				else
				{
					result += '&' + key + ';';
				}
				key = "";
			}
		}
		else if (isInEncoded)
		{
			key += ch;
		}
		else
		{
			result += ch;
		}
	}
	if (isInEncoded)
	{
		result += '&' + key;
	}
	return result;
}
