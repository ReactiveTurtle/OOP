#include <iostream>
#include <string>
#include "URLExtensions.hpp"

using namespace std;

int main()
{
	string url;

	Protocol protocol;
	int port;
	string host;
	string document;

	while (!cin.eof())
	{
		cout << ">>> ";
		getline(cin, url);
		bool wasParsed = ParseURL(url, protocol, port, host, document);
		if (wasParsed)
		{
			cout << "HOST: " << host << endl;;
			cout << "PORT: " << port << endl;;
			cout << "DOC: " << (document.empty() ? "<empty>" : document) << endl;;
		}
		else
		{
			cout << "Invalid url" << endl;
		}
	}
	return 0;
}

