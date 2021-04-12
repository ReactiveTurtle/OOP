#include <iostream>
#include <string>
#include "URLExtensions.hpp"

using namespace std;

int main()
{
	string url;
	getline(cin, url);
	
	Protocol protocol;
	int port;
	string host;
	string document;

	bool wasParsed = ParseURL(url, protocol, port, host, document);
	if (wasParsed)
	{
		cout << "HOST: " << host << endl;;
		cout << "PORT: " << port << endl;;
		cout << "DOC: " << (document.empty() ? "<empty>" : document) << endl;;
		return 0;
	}
	else
	{
		cout << "Invalid url" << endl;
		return 1;
	}
}

