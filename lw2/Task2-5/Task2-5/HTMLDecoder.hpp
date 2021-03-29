#pragma once
#include <string>

using namespace std;

const string quot = "quot";
const string apos = "apos";
const string lt = "lt";
const string gt = "gt";
const string amp = "amp";

string HtmlDecode(string const& html)
{
	bool isInEncoded = false;
	string result;
	string code;
	for (string::const_iterator i = html.begin(); i != html.end(); i++) {
		char ch = *i;
		if (ch == '&' && !isInEncoded || ch == ';' && isInEncoded) {
			isInEncoded = ch == '&';
			if (!isInEncoded) {
				if (code == quot) {
					result += '"';
				}
				else if (code == apos) {
					result += '\'';
				}
				else if (code == lt) {
					result += '<';
				}
				else if (code == gt) {
					result += '>';
				}
				else if (code == amp) {
					result += '&';
				}
				else {
					result += '&' + code + ';';
				}
				code = "";
			}
		}
		else if (isInEncoded) {
			code += ch;
		}
		else {
			result += ch;
		}
	}
	return result;
}
